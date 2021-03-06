package EdBDemo_Java;

import com.sun.jna.Library;
import com.sun.jna.Native;

public class EdBApi {
	public interface CLibrary extends Library
    {
		int EdB_Login(String IP, int Port, String Version, String User, String Password, String TXPass, String Yyb);
		String EdB_QueryData(String User, int ClientID, int Category);
		String EdB_SendOrder(int ClientID, int Fx, String User, String Gddm, String Gpdm, int Quantity, float Price);
		String EdB_GetPrice(int ClientID, String Gpdm);
		String EdB_CancelOrder(int ClientID, String User, String Bho, int jYs);
    }
	
	private static CLibrary lib = (CLibrary)Native.loadLibrary("EdBApi.dll",CLibrary.class); 
	
	public static int EdB_Login(String IP, int Port, String Version, String User, String Password, String TXPass, String Yyb)
	{
		return lib.EdB_Login(IP, Port, Version, User, Password, TXPass, Yyb);
	}
	
	public static String EdB_QueryData(String User, int ClientID, int Category)
	{
		return lib.EdB_QueryData(User, ClientID, Category);
	}
	
	public static String EdB_SendOrder(int ClientID, int Fx, String User, String Gddm, String Gpdm, int Quantity, float Price)
	{
		return lib.EdB_SendOrder(ClientID, Fx, User, Gddm, Gpdm, Quantity, Price);
	}
	
	public static String EdB_GetPrice(int ClientID, String Gpdm)
	{
		return lib.EdB_GetPrice(ClientID, Gpdm);
	}
	
	public static String EdB_CancelOrder(int ClientID, String User, String Bho, int jYs)
	{
		return lib.EdB_CancelOrder(ClientID, User, Bho, jYs);
	}
	
}
