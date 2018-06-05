# -*- coding: utf-8 -*-

from ctypes import *
from os import path

cLib = cdll.LoadLibrary(path.dirname(__file__) + "/EdBApi.dll")

class EdBApi:
    @classmethod
    def EdB_Login(Obj, IP, Port, Version, User, Password, TXPass, Yyb):
        return cLib.EdB_Login(IP, Port, Version, User, Password, TXPass, Yyb)
    
    @classmethod
    def EdB_QueryData(Obj, User, ClientID, Category):
        return cLib.EdB_QueryData(User, ClientID, Category)

    @classmethod
    def EdB_SendOrder(Obj, ClientID, Fx, User, Gddm, Gpdm, Quantity, Price):
        return cLib.EdB_SendOrder(ClientID, Fx, User, Gddm, Gpdm, Quantity, Price)

    @classmethod
    def EdB_GetPrice(Obj, ClientID, Gpdm):
        return cLib.EdB_GetPrice(ClientID, Gpdm)

    @classmethod
    def EdB_CancelOrder(Obj, ClientID, User, Bho, Jys):
        return cLib.EdB_CancelOrder(ClientID, User, Bho, Jys)


if __name__ == '__main__':
    clientID = EdBApi.EdB_Login(b"116.228.149.86", 7708, b"10.11", b"280079160", b"830406", b"", b"0")
    print ("Login: " + str(clientID))
    queryData = string_at(EdBApi.EdB_QueryData(b"280079160", clientID, 2014))
    print ("QueryData: " + queryData.decode("gb2312"))
    sendOrder = string_at(EdBApi.EdB_SendOrder(clientID, 15, b"280079160", b"70000", b"70000", 1, c_float(1.0)))
    print ("SendOrder: " + sendOrder.decode("gb2312"))
    getprice = string_at(EdBApi.EdB_GetPrice(clientID, b"70000"))
    print ("GetPrice: " + getprice.decode("gb2312"))
    cancelOrder = string_at(EdBApi.EdB_CancelOrder(clientID, b"280079160", queryData, 1))
    print ("CancelOrder: " + cancelOrder.decode("gb2312"))
