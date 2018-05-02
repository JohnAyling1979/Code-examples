public class Puppy
{
	private String name;
	private int age;

	//constructor
	public Puppy(String n)
	{
		name=n;
		System.out.println("My name is "+name);
	}

	public void setAge(int age)
	{
		this.age=age;
	}

	public int getAge()
	{
		return age;
	}

	public String getName()
	{
		return name;
	}

	public static void main(String args[])
	{
		Puppy myPup=new Puppy("John");

		myPup.setAge(2);

		System.out.println(myPup.getName()+" is "+myPup.getAge());
	}
}
