using System;
using System.Runtime.InteropServices;

namespace EdBApi_CSharp
{
    public class EdBApi
    {
        [DllImport("EdBApi.dll", EntryPoint = "EdB_Login", CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 EdB_Login(string IP, Int32 Port, string Version, string User, string Password, string TXPass, string Yyb);

        [DllImport("EdBApi.dll", EntryPoint = "EdB_QueryData", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr EdB_QueryData(string User, Int32 ClientID, Int32 Category);

        [DllImport("EdBApi.dll", EntryPoint = "EdB_SendOrder", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr EdB_SendOrder(Int32 ClientID, Int32 Fx, string User, string Gddm, string Gpdm, Int32 Quantity, float Price);

        [DllImport("EdBApi.dll", EntryPoint = "EdB_GetPrice", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr EdB_GetPrice(Int32 ClientID, string Gpdm);

        [DllImport("EdBApi.dll", EntryPoint = "EdB_CancelOrder", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr EdB_CancelOrder(Int32 ClientID, string User, string Bho, Int32 jYs);
    }
}
