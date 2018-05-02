//a class which hold a size
class FreshJuice
{
	enum FreshJuiceSize{SMALL,MEDIUM,LARGE}

	FreshJuiceSize size;
}

//main class
public class FreshJuiceTest
{
	public static void main(String args[])
	{
		//init juice
		FreshJuice juice=new FreshJuice();
		//sets the size
		juice.size=FreshJuice.FreshJuiceSize.MEDIUM;

		System.out.println("Size: "+juice.size);
	}
}
