using System;
using System.Collections.Generic;
using System.Linq;
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
           // string queryDataResult = EdBApi.EdB_QueryData("280079160", clientID, 1102);
            string priceResult = EdBApi.EdB_GetPrice(clientID, "1231");
            Console.WriteLine(priceResult);
        }
    }
}
