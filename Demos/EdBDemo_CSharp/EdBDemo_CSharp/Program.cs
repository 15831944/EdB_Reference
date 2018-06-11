using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using EdBApi_CSharp;

namespace EdBDemo_CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            Int32 clientID =  EdBApi.EdB_Login("116.228.149.86", 7708, "10.11", "280079160", "830406", "", "0");
            Console.WriteLine("Login: " + clientID);
            string queryData = Marshal.PtrToStringAnsi(EdBApi.EdB_QueryData("280079160", clientID, 1116));
            Console.WriteLine("QueryData: " + queryData);
            string sendOrder = Marshal.PtrToStringAnsi(EdBApi.EdB_SendOrder(clientID, 15, "280079160", "70000", "70000", 1, (float)1.0));
            Console.WriteLine("SendOrder:" + sendOrder);
            string getPrice = Marshal.PtrToStringAnsi(EdBApi.EdB_GetPrice(clientID, "600802"));
            Console.WriteLine("GetPrice: " + getPrice);
            string cancelOrder = Marshal.PtrToStringAnsi(EdBApi.EdB_CancelOrder(clientID, "280079160", queryData, 1));
            Console.WriteLine("CancelOrder: " + cancelOrder);
        }
    }
}
