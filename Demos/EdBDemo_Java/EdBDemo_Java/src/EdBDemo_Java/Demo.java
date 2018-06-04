package EdBDemo_Java;

public class Demo {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int ret = EdBApi.EdB_Login("116.228.149.86", 7708, "10.11", "280079160", "830406", "", "16");
		System.out.println(ret);
	}

}
