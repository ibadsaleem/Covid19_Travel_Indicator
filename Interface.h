#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctime>
#include<dos.h>
using namespace std;

void time(){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	if (ltm->tm_min>9)
	cout<<"****\tTime: "<<ltm->tm_hour<<":"<<ltm->tm_min<<"\t\t\t\t\t\tDate: "<<ltm->tm_mday<<"/"<<1+ltm->tm_mon<<"/"<<1900+ltm->tm_year<< "\t ****"<< endl;
	else
	
	cout<<"****\tTime: "<<ltm->tm_hour<<":0"<<ltm->tm_min<<"\t\t\t\t\t\tDate: "<<ltm->tm_mday<<"/"<<1+ltm->tm_mon<<"/"<<1900+ltm->tm_year<< "\t ****"<< endl;
	
}

void interface(){
	for(int i=0;i<3;i++)
		cout<<"*************************************************************************************"<< endl;
		
	for (int i = 0; i<20; i++){
		if (i == 2){
	   		time();
		}
	 	if (i == 6)  
	 		{
			 cout<< "****\t\t\t      \"WELCOME TO COVID-19 PORTAL\" \t\t\t ****"<< endl;
	 		cout<< "****\n\t\t      PRESS ANY KEY TO CONTINUE (E TO EXIT)... \t\t\t ****"<< endl;

		}else if(i == 15){
	 	 	cout<<"**** By:\t\t\t\t\t\t\t\t\t ****"<< endl;
		}
		else if(i == 16){	
	 	 	cout<<"**** 1)Muhammad Ibad Saleem (19K-0220)\t\t\t\t\t\t ****"<< endl;
		}
	 	else if(i == 17){
	 	 	cout<<"**** 2)Syed Ahsan Akhtar Naqvi (19K-1475)\t\t\t\t\t ****"<< endl;
		}
		else if(i == 18){
	 	 	cout<<"**** 3)Muhammad Mustafa Bawany (19K-1273)\t\t\t\t\t ****"<< endl;
		}
	 	else
	 		cout<<"****\t\t\t\t\t\t\t\t\t\t ****"<< endl;
	}
	
	for(int i=0; i<3; i++)
		cout<<"*************************************************************************************"<< endl;
   
}
