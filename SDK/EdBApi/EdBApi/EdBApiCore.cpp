#include "EdBApiCore.h"
#include "qt_windows.h"
#include "MemoryModule.h"
#include "resource.h"
#include <QFile>
#include "edbcrypt.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QTemporaryDir>
#include <QUuid>

EdBApiCore* EdBApiCore::g_pInsatnce = NULL;

EdBApiCore* EdBApiCore::GetInstance()
{
	if (g_pInsatnce == NULL)
		g_pInsatnce = new EdBApiCore();
	return g_pInsatnce;
}

EdBApiCore::EdBApiCore()
{

	//LoadLibraryW((getCurDllPath() + "/TcApi.dll").toStdWString().c_str());

	HMODULE hInstance = GetModuleHandleW(L"EdBApi.dll");
	HRSRC hResID0 = ::FindResourceW(hInstance, MAKEINTRESOURCEW(IDR_DLL2), L"Dll");
	HGLOBAL hGlobalSys0 = LoadResource(hInstance, hResID0);
	LPVOID lpGlobalSys0 = LockResource(hGlobalSys0);
	QTemporaryDir tmpDir;
	tmpDir.setAutoRemove(false);
	QString tmpFilePath = tmpDir.path() + "/TcApi.dll";
	QFile tmpFile(tmpFilePath);
	tmpFile.open(QIODevice::WriteOnly);
	tmpFile.write((char *)lpGlobalSys0, SizeofResource(hInstance, hResID0));
	tmpFile.close();
	//wchar_t chCurDir[MAX_PATH] = { 0 };
	//GetCurrentDirectoryW(MAX_PATH, chCurDir);
	SetCurrentDirectoryW(tmpFilePath.toStdWString().c_str());
	HMODULE moudle0 = LoadLibraryW(tmpFilePath.toStdWString().c_str());
	SetCurrentDirectoryW(getCurDllPath().toStdWString().c_str());
	DWORD hh = GetLastError();

	HRSRC hResID = ::FindResourceW(hInstance, MAKEINTRESOURCEW(IDR_DLL1), L"Dll");
	HGLOBAL hGlobalSys = LoadResource(hInstance, hResID);
	LPVOID lpGlobalSys = LockResource(hGlobalSys);

	//QFile file(":/JLAPI.dll");
	//QByteArray byteArr = file.readAll();
	

	HMEMORYMODULE module = MemoryLoadLibrary(lpGlobalSys);
	m_pLoginProc = (LoginProc)MemoryGetProcAddress(module, "JL_Login");
	m_pQueryDataProc = (QueryDataProc)MemoryGetProcAddress(module, "JL_QueryData");
	m_pSendOrderProc = (SendOrderProc)MemoryGetProcAddress(module, "JL_SendOrder");
	m_pGetPriceProc = (GetPriceProc)MemoryGetProcAddress(module, "JL_GetPrice");
	m_pCancelOrderProc = (CancelOrderProc)MemoryGetProcAddress(module, "JL_CancelOrder");

	m_isParseLicSuccess = parseLic();
}


EdBApiCore::~EdBApiCore()
{
}

QString EdBApiCore::getCurDllPath()
{
	wchar_t path[1024] = { 0 };
	HMODULE hInstance = GetModuleHandleW(L"EdBApi.dll");
	GetModuleFileNameW(hInstance, path, 1023);
	return  QFileInfo(QString::fromWCharArray(path)).absolutePath();
}

bool EdBApiCore::parseLic()
{
	QFile licFile(getCurDllPath() + "/EdB.lic");
	if (!licFile.exists())
		return false;
	bool isOpen = licFile.open(QIODevice::ReadOnly);
	if (!isOpen)
		return false;
	QByteArray byteArrCrypted = licFile.readAll();
	licFile.close();

	QFile datFile(getCurDllPath() + "/EdB.lic.dat");
	if (!datFile.exists())
		return false;
	isOpen = datFile.open(QIODevice::ReadOnly);
	if (!isOpen)
		return false;
	QByteArray keySha3_512 = datFile.readAll();
	datFile.close();

	EdbCrypt edbCryPt(keySha3_512);
	QByteArray byteArr = edbCryPt.Decrypt(byteArrCrypted);
	byteArr = QByteArray::fromBase64(byteArr);
	QJsonDocument jsonDoc = QJsonDocument::fromBinaryData(byteArr);
	if (!jsonDoc.isObject())
		return false;
	QJsonObject jsonObj = jsonDoc.object();
	if (!jsonObj.contains("LimitAccount"))
		return false;
	m_licInfo.LimitAccount = jsonObj["LimitAccount"].toBool();
	if (!jsonObj.contains("AccountList"))
		return false;
	QJsonArray accountListJsonArr = jsonObj["AccountList"].toArray();
	for (auto iter = accountListJsonArr.begin(); iter != accountListJsonArr.end(); ++iter)
	{
		QJsonObject tmp = iter->toObject();
		LicInfo::AcountInfo accountInfo;
		accountInfo.Name = tmp["Name"].toString();
		accountInfo.LimitIP = tmp["LimitIP"].toBool();
		accountInfo.IPList = tmp["IPList"].toVariant().toStringList();
		accountInfo.Deadline = tmp["Deadline"].toVariant().toDateTime();
		m_licInfo.AccountMap[accountInfo.Name] = accountInfo;
	}
	if (!jsonObj.contains("LimitIP_General"))
		return false;
	m_licInfo.LimitIP_General = jsonObj["LimitIP_General"].toBool();
	if (!jsonObj.contains("IPList_General"))
		return false;
	m_licInfo.IPList_General = jsonObj["IPList_General"].toVariant().toStringList();
	if (!jsonObj.contains("LimitTime_General"))
		return false;
	m_licInfo.LimitTime_General = jsonObj["LimitTime_General"].toBool();
	if (!jsonObj.contains("Deadline_General"))
		return false;
	m_licInfo.Deadline_General = jsonObj["DeadLine_General"].toVariant().toDateTime();
	return true;
}

bool EdBApiCore::verifyLogin(const char* ip, const char* user)
{
	if (!m_isParseLicSuccess)
		return false;
	if (m_licInfo.LimitTime_General)
	{
		if (QDateTime::currentDateTime() > m_licInfo.Deadline_General)
			return false;
	}
	if (m_licInfo.LimitIP_General)
	{
		if (!m_licInfo.IPList_General.contains(QString(ip)))
			return false;
	}
	if (m_licInfo.LimitAccount)
	{
		if (!m_licInfo.AccountMap.contains(user))
			return false;
		LicInfo::AcountInfo accountInfo = m_licInfo.AccountMap[user];
		if (accountInfo.LimitIP)
		{
			if (!accountInfo.IPList.contains(ip))
				return false;
		}
		if (QDateTime::currentDateTime() > accountInfo.Deadline)
			return false;
	}
	return true;
}


int EdBApiCore::login(const char* ip, int port, const char* version, const char* user, const char* password, const char* TXPass, const char* yyb)
{
	if (!m_isParseLicSuccess)
	{
		qDebug() << QString::fromWCharArray(L"µÇÂ¼Ê§°Ü£¬ÊÚÈ¨ÎÄ¼þ½âÎö´íÎó");
		return 0;
	}


	if (verifyLogin(ip, user) == false)
	{
		qDebug() << QString::fromWCharArray(L"µÇÂ¼Ê§°Ü£¬Î´±»ÊÚÈ¨µÇÂ¼");
		return 0;
	}

	if (m_pLoginProc != NULL)
	{
		int ret = m_pLoginProc(ip, port, version, user, password, TXPass, yyb);
		return ret;
	}
	else
	{
		qDebug() << QString::fromWCharArray(L"µÇÂ¼Ê§°Ü£¬Èí¼þÄÚ²¿·¢Éú´íÎó");
		return 0;
	}
}


const char * EdBApiCore::queryData(const char* user, int clientID, int category)
{
	if (m_pQueryDataProc != NULL)
		return m_pQueryDataProc(user, clientID, category);
	else
		return "";
}
const char * EdBApiCore::sendOrder(int clientID, int fx, const char *user, const char *gddm, const char* gpdm, int quantity, float price)
{
	if (m_pSendOrderProc != NULL)
		return m_pSendOrderProc(clientID, fx, user, gddm, gpdm, quantity, price);
	else
		return "";
}
const char * EdBApiCore::getPrice(int clientID, const char * gpdm)
{
	if (m_pGetPriceProc != NULL)
		return m_pGetPriceProc(clientID, gpdm);
	else
		return "";
}

const char * EdBApiCore::cancelOrder(int clientID, const char * user, const char * bho, int jys)
{
	if (m_pCancelOrderProc != NULL)
		return m_pCancelOrderProc(clientID, user, bho, jys);
	else
		return "";
}
