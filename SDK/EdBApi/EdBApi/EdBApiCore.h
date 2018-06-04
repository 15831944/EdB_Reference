#pragma once
#include <QList>
#include <QMap>
#include <QStringList>
#include <QDateTime>

class EdBApiCore
{
private:
	typedef int(__stdcall * LoginProc)(const char* ip, int port, const char* version, const char* user, const char* password, const char* TXPass, const char* yyb);
	typedef const char*(__stdcall * QueryDataProc)(const char* user, int clientID, int category);
	typedef const char*(__stdcall * SendOrderProc)(int clientID, int fx, const char *user, const char *gddm, const char* gpdm, int quantity, float price);
	typedef const char*(__stdcall * GetPriceProc)(int clientID, const char * gpdm);
	typedef const char*(__stdcall * CancelOrderProc)(int clientID, const char * user, const char * bho, int jys);

	LoginProc m_pLoginProc;
	QueryDataProc m_pQueryDataProc;
	SendOrderProc m_pSendOrderProc;
	GetPriceProc m_pGetPriceProc;
	CancelOrderProc m_pCancelOrderProc;

	static EdBApiCore* g_pInsatnce;
	bool m_isParseLicSuccess;

	typedef struct LicInfo
	{
		typedef struct AcountInfo
		{
			QString Name;
			bool LimitIP;
			QStringList IPList;
			QDateTime Deadline;
		}AcountInfo;

		bool LimitAccount;
		QMap<QString, AcountInfo> AccountMap;
		bool LimitIP_General;
		QStringList IPList_General;
		bool LimitTime_General;
		QDateTime Deadline_General;
	} LicInfo;
	LicInfo m_licInfo;

	static QString getCurDllPath();
	bool parseLic();
	bool verifyLogin(const char* ip, const char* user);

public:
	EdBApiCore();
	~EdBApiCore();

	static EdBApiCore* GetInstance();

	int login(const char* ip, int port, const char* version, const char* user, const char* password, const char* TXPass, const char* yyb);
	const char * queryData(const char* user, int clientID, int category);
	const char * sendOrder(int clientID, int fx, const char *user, const char *gddm, const char* gpdm, int quantity, float price);
	const char * getPrice(int clientID, const char * gpdm);
	const char * cancelOrder(int clientID, const char * user, const char * bho, int jys);


};

