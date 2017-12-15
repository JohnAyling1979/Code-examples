import java.io.*;

public class Employee
{
	//private variables
	private String name;
	private int age;
	private String designation;
	private double salary;

	//overloaded constructors
	public Employee(String name)
	{
		this.name=name;
	}

	public Employee(String name,int age)
	{
		this.name=name;
		this.age=age;
	}

	public Employee(String name,int age,String design)
	{
		this.name=name;
		this.age=age;
		this.designation=design;
	}

	public Employee(String name,int age,String design,double salary)
	{
		this.name=name;
		this.age=age;
		this.designation=design;
		this.salary=salary;
	}

	public void setAge(int age)
	{
		this.age=age;
	}

	public void setDes(String design)
	{
		this.designation=design;
	}

	public void setSalary(double salary)
	{
		this.salary=salary;
	}

	public void printInfo()
	{
		System.out.println("Name       : "+name);
		System.out.println("Age        : "+age);
		System.out.println("Designation: "+designation);
		System.out.println("Salary     : $"+salary);
	}
}
