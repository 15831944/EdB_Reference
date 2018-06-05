package EdBDemo_Java;

public class Demo {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int clientID = EdBApi.EdB_Login("116.228.149.86", 7708, "10.11", "280079160", "830406", "", "16");
		System.out.println("ClientID: " + clientID);
		String queryData = EdBApi.EdB_QueryData("280079160", clientID, 2014);
		System.out.println("QueryData:" + queryData);
		String sendOrder = EdBApi.EdB_SendOrder(clientID, 15, "280079160", "70000", "70000", 1, (float)1.0);
		System.out.println("SendOrder:" + sendOrder);
		String getPrice = EdBApi.EdB_GetPrice(clientID, "70000");
		System.out.println("GetPrice:" + getPrice);
		String cancelOrder = EdBApi.EdB_CancelOrder(clientID, "280079160", queryData, 1) ;
		System.out.println("CancelOrder:" + cancelOrder);
	}

}
