public class loop
{
    public static void main(String arg[])
    {
        int numbers[]={10,20,30,40,50};
        String names[]={"John","Lynne","Katelyn"};

        //Enhanced loop
        for(int x: numbers)
            System.out.print(x+" ");
        System.out.println();

        for(String name:names)
            System.out.print(name+" ");
        System.out.println();
    }
}
