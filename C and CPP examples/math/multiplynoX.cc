#include<iostream>

//multiplication without *

int two(int x)
{
	return x<<1;
}

int three(int x)
{
	return (x<<1)+x;
}

int five(int x)
{
	return (x<<2)+x;
}

int seven(int x)
{
	return three(two(x))+x;
}

int main()
{
	for (int x=0;x<11;x++)
	{
		std::cout<<x<<"*2="<<two(x)<<std::endl;
		std::cout<<x<<"*3="<<three(x)<<std::endl;
		std::cout<<x<<"*4="<<two(two(x))<<std::endl;
		std::cout<<x<<"*5="<<five(x)<<std::endl;
		std::cout<<x<<"*6="<<two(three(x))<<std::endl;
		std::cout<<x<<"*7="<<seven(x)<<std::endl;
		std::cout<<x<<"*8="<<two(two(two(x)))<<std::endl;
		std::cout<<x<<"*9="<<three(three(x))<<std::endl;
		std::cout<<x<<"*10="<<five(two(x))<<std::endl<<std::endl;
	}

	return 0;
}
