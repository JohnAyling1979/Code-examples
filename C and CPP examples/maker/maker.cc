/*
	used to create a simple make file
*/

#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

int main()
{
	string progname;
	ofstream makefile;

	makefile.open("makefile");

	cout<<"Enter program name: ";
	cin>>progname;
	makefile<<"CC = g++\n";
	makefile<<"CCFLAGS = -Wall -g\n";
	makefile<<"\n";
	makefile<<progname<<".exe"<<":"<<progname<<".o\n";
	makefile<<"\t$(CC) $(CCFLAGS) -o "<<progname<<".exe"<<" "<<progname<<".o\n";
	makefile<<"\n";
	makefile<<progname<<".o: "<<progname<<".cc\n";
	makefile<<"\t$(CC) $(CCFLAGS) -c "<<progname<<".cc\n";
	makefile<<"\n";
	makefile<<"clean:\n";
	makefile<<"\t-rm *.o "<<progname<<".exe"<<"\n";
	makefile<<"\n";
	makefile<<"run:\n";
	makefile<<"\t./"<<progname<<".exe\n";
	makefile<<"link:\n";
	makefile<<"\tln -s /home/turing/mhou/public/csci340spring2017/"<<progname<<".out sampleout.out\n";
	makefile<<"compare:\n";
	makefile<<"\t./"<<progname<<".exe > myout.out\n";
	makefile<<"\tdiff -w myout.out sampleout.out\n";
	makefile.close();


	cout<<"Makefile  is ready for program "<<progname<<endl;
}

