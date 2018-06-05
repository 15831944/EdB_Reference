#include "EdBApi.h"
#include "EdBApiCore.h"

int EdB_Login(const char* IP, int Port, const char* Version, const char* User, const char* Password, const char* TXPass, const char* Yyb)
{
	return EdBApiCore::GetInstance()->login(IP, Port, Version, User, Password, TXPass, Yyb);
}

const char*  EdB_QueryData(const char* User, int ClientID, int Category)
{
	return EdBApiCore::GetInstance()->queryData(User, ClientID, Category);
}

const char* EdB_SendOrder(int ClientID, int Fx, const char *User, const char *Gddm, const char* Gpdm, int Quantity, float Price)
{
	return EdBApiCore::GetInstance()->sendOrder(ClientID, Fx, User, Gddm, Gpdm, Quantity, Price);
}

const char* EdB_GetPrice(int ClientID, const char * Gpdm)
{
	return EdBApiCore::GetInstance()->getPrice(ClientID, Gpdm);
}

const char* EdB_CancelOrder(int ClientID, const char * User, const char * Bho, int Jys)
{
	return EdBApiCore::GetInstance()->cancelOrder(ClientID, User, Bho, Jys);
}
