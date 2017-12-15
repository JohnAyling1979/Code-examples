#include<iostream>
#include<vector>

using namespace std;

int main()
{
	int decimal,base,place=0;
	char invalue;
	vector<char> number;

	cout<<"Enter decimal number"<<endl;
	cin>>decimal;
	cout<<"Enter new base"<<endl;
	cin>>base;

	while(decimal!=0)
	{
		switch(decimal%base)
		{
			case 0:
				invalue='0';
				break;
			case 1:
				invalue='1';
				break;
                        case 2:
                                invalue='2';
                                break;
                        case 3:
                                invalue='3';
                                break;
                        case 4:
                                invalue='4';
                                break;
                        case 5:
                                invalue='5';
                                break;
                        case 6:
                                invalue='6';
                                break;
                        case 7:
                                invalue='7';
                                break;
                        case 8:
                                invalue='8';
                                break;
                        case 9:
                                invalue='9';
                                break;
                        case 10:
                                invalue='A';
                                break;
                        case 11:
                                invalue='B';
                                break;
                        case 12:
                                invalue='C';
                                break;
                        case 13:
                                invalue='D';
                                break;
                        case 14:
                                invalue='E';
                                break;
                        case 15:
                                invalue='F';
                                break;
		}
		number.push_back(invalue);
		place++;
		decimal/=base;
		if(place%4==0 && decimal!=0)
			number.push_back(' ');
	}

	for(vector<char>::reverse_iterator i=number.rbegin();i!=number.rend();i++)
		cout<<*i;
	cout<<endl;
}
