using System;
using System.Runtime.InteropServices;

namespace EdBApi_COM
{
    [ComVisible(true)]
    [Guid("3ED112B2-122E-4568-A42F-8A3050045534")]
    public class EdBApi
    {
        [DllImport("EdBApi.dll", EntryPoint = "EdB_Login", CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _EdB_Login(string IP, Int32 Port, string Version, string User, string Password, string TXPass, string Yyb);

        [DllImport("EdBApi.dll", EntryPoint = "EdB_QueryData", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr _EdB_QueryData(string User, Int32 ClientID, Int32 Category);

        [DllImport("EdBApi.dll", EntryPoint = "EdB_SendOrder", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr _EdB_SendOrder(int ClientID, Int32 Fx, string User, string Gddm, string Gpdm, Int32 Quantity, float Price);

        [DllImport("EdBApi.dll", EntryPoint = "EdB_GetPrice", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr _EdB_GetPrice(Int32 ClientID, string Gpdm);

        [DllImport("EdBApi.dll", EntryPoint = "EdB_CancelOrder", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr _EdB_CancelOrder(Int32 ClientID, string User, string Bho, Int32 jYs);

        public Int32 EdB_Login(string IP, Int32 Port, string Version, string User, string Password, string TXPass, string Yyb)
        {
            return _EdB_Login(IP, Port, Version, User, Password, TXPass, Yyb);
        }

        public string EdB_QueryData(string User, Int32 ClientID, Int32 Category)
        {
            return Marshal.PtrToStringAnsi(_EdB_QueryData(User, ClientID, Category));
        }

        public string EdB_SendOrder(int ClientID, Int32 Fx, string User, string Gddm, string Gpdm, Int32 Quantity, float Price)
        {
            return Marshal.PtrToStringAnsi(_EdB_SendOrder(ClientID, Fx, User, Gddm, Gpdm, Quantity, Price));
        }

        public string EdB_GetPrice(Int32 ClientID, string Gpdm)
        {
            return Marshal.PtrToStringAnsi(_EdB_GetPrice(ClientID, Gpdm));
        }

        public string EdB_CancelOrder(Int32 ClientID, string User, string Bho, Int32 jYs)
        {
            return Marshal.PtrToStringAnsi(_EdB_CancelOrder(ClientID, User, Bho, jYs));
        }
    }
}
