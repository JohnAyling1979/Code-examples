/***************************************************************
Name:		John Ayling
Instructor:	Georgia Brown
	TA: 	Kartheek Chintalapati
Semester:	Spring 2017
Assignment:	11
Due:		4/28/2017
***************************************************************/

//needed includes
#include<iostream>
#include<iomanip>
#include<mysql.h>
#include<string>

using namespace std;

int main()
{
	char *pId,*pPass;
	string id,pass;

	//initialize MYSQL object
	MYSQL *db;
	db=mysql_init(NULL);

	//connect to database and check if ok
	cout<<"ID: ";
	cin>>id;
	cout<<"Password: ";
	cin>>pass;

	pId=&id[0];
	pPass=&pass[0];

	cout<<pId<<" "<<pPass<<endl;

	if(mysql_real_connect(db, "courses", pId, pPass, pId, 0, NULL, 0))
	{
		//column sizes
		const int col1=8;
		const int col2=18;

		//count,passenger query,pointer for the query
		unsigned int count;
		string query;
		char *q;

		//varablies to store the query's return and
		//current row
		MYSQL_RES *flight_set,*pass_set;
		MYSQL_ROW flightrow,passrow;

		//query the flight table and store the data
		mysql_query(db,"select * from flight order by flightnum");
		flight_set=mysql_store_result(db);

		//while loop for flights
		while(flightrow=mysql_fetch_row(flight_set))
		{
			//display flight header
			cout<<setw(col1)<<"Flight #"<<setw(col2)<<"Origination"<<setw(col2)<<"Destination"<<setw(col2)<<"Miles"<<endl;
			for(int i=0;i<col1+col2*3;i++)
				cout<<"-";
			cout<<endl;

			//display flight info
			cout<<setw(col1)<<flightrow[0]<<setw(col2)<<flightrow[1]<<setw(col2)<<flightrow[2]<<setw(col2)<<flightrow[3]<<endl<<endl;

			//create query and the pointer to it
			query="select p.firstName,p.lastName from passenger p,manifest m where m.passnum=p.passnum and m.flightnum="+(string)flightrow[0]+";";
			q=&query[0];

			//query the manifest and passenger table and store the value
			mysql_query(db,q);
			pass_set=mysql_store_result(db);

			//passenger header
			cout<<"Passengers"<<endl;
			cout<<"----------"<<endl;

			//passenger loop
			while(passrow=mysql_fetch_row(pass_set))
				//display passengers on the flight
				cout<<passrow[0]<<" "<<passrow[1]<<endl;
			count=mysql_num_rows(pass_set);

			//dispay summary of total passengers
			cout<<"There ";
			if(count==1)
				cout<<"is ";
			else
				cout<<"are ";
			cout<<count<<" passengers on flight #"<<flightrow[0]<<endl<<endl<<endl;

			//freeing the memory
			mysql_free_result(pass_set);

		//end fligt loop
		}

		//close connection and free the memory
		mysql_close(db);
		mysql_free_result(flight_set);
	}else
	{
		//connection failed
		cout<<"I'm sorry Dave"<<endl;
		cout<<"I can not do that"<<endl;
	}
	return 0;
}
