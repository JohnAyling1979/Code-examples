import java.io.*;

public class EmployeeTest
{
	public static void main(String args[])
	{
		Employee empOne=new Employee("John",26,"Senior Eng",1000);
		Employee empTwo=new Employee("Bob",32,"Janitor",20);

		empOne.printInfo();
		System.out.println();
		empTwo.printInfo();
	}
}
