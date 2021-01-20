#include <conio.h>
#include <stdio.h>
#include "Interface.h"
#include<bits/stdc++.h>
#define Max_Countries 100
#include <cstdlib>
#include <unistd.h>
#include "CoronaIndicator.cpp"
using namespace std;

int main()
{
	system("color 4F");	
	interface();
	CovidTravelIndicator CVI;
	CVI.Filing();
	getch();
	while(1)
	{
		system("cls");
		string Country;
		int Option;
		cout<<"\n**********************************COVID 19 PORTAL MENU****************************************\n=====================================================\n";
		cout<<"\n1)Search World Wide Statistics\n\n";
		cout<<"2)Search Stats By Country\n\n";
		cout<<"3)Search Stats By Largest Number Of Cases\n\n";
		cout<<"4)Search Stats By Largest Number Of Deaths\n\n";
		cout<<"5)Travel Indicator\n\n";
		cout<<"6)Check If You Have Covid19 Symptoms\n\n";
		cout<<"7)Safety Precautions\n\n";
		cout<<"8)Show Decision Tree\n\n";
		cout<<"0)Exit\n\n";
		cout<<"\n======================================================";
		cout<<"\nChoose Option: ";
		cin >> Option;
		system("cls");
		switch(Option)
		{
			case 1:{
				CVI.DisplayWorldStats();												
				getch();
				break;
			}
			case 2:{
				cout << "\nEnter Country to Search For: ";
				cin >> Country;
				CVI.SearchByCountry(Country);
				getch();
				break;
			}
			case 3:{
				CVI.CountryByMostNumberOfCases();
				getch();
				break;
			}
			case 4:{
				CVI.CountryByMostNumberOfDeaths();
				getch();
				break;
			}
			case 5:{
				int Option2;
				cout << "\n1.Test Data." << endl;
				cout << "\n2.Search Safety Of A Specific Country." << endl;
				cout << "\n3.Search All Safe Countries for Toursim." << endl;
				cout << "\n4.Search All Safe Countries for Travelling." << endl;
				cout << "\n0.Back" << endl;
				cout << "\nOption: ";
				cin >> Option2;
				switch(Option2)
				{
					case 1:{
						CVI.Build_Tree();
						CVI.Test_Data();
						cout << "\nYour Testing Data Has Been Updated in the File Named: TestingDataWithOutput.csv" << endl;
						getch();
						break;
					}
					case 2:{
						cout << "\nEnter Country Name: ";
						cin >> Country;
						CVI.SearchSpecificCountry(Country);
						getch();
						break;
					}
					case 3:{
						CVI.Search_Safe_Toursim_Countries();
						getch();
						break;
					}
					case 4:{
						CVI.Search_Safe_Travelling_Countries();
						getch();
						break;
					}
					default: {
						break;
					}
				}
				break;
			}
			case 6:{
				int maxsymptom=4;
				int symptoms=0;
				NaiveBayes NB;
				NB.Filing();
				NB.Calculate_Probability();
				while(1)
				{
				    system("cls");
					cout<<"\nEnter Number Of Symptoms: ";
					cin>>symptoms;
					if (symptoms>maxsymptom)
					{
						cout<<"Kindly Stay in the Limit of 4 Symptoms.Press Any Key To Retry";
						getch();
					}
					else
					break;
				}
				char *arr=new char[symptoms];
				cout<<"Choose Symptoms From The List Below\n=====================================\n";
				cout<<"1)Fever(F)\n2)Cough(C)\n3)Tiredness(T)\n4)Shortness Of Breath (S)\n";
				for (int i=0;i<symptoms;i++)
				{
					cout<<"\nPress Letter Indicated in Bracket For Option "<<i+1<<": ";
					cin>>arr[i];
				}
				cout<<"\n====================================================================\n";
				NB.Predict_Covid(symptoms,arr);
				cout<<"\n====================================================================\n";
				getch();
				break;
			}
			case 7:{
				CVI.SARSPrecaution();
				getch();
				break;
			}
			case 8:{
				CVI.PrintBinaryTree();
				getch();
				break;
			}
			case 0:{
				cout<<"\t\t\t\t\tSAFE TRAVELS!"<<endl;
				exit(1);
				break;
			}
			default:{
				break;
			}		
		}
	}
	return 0;	
}
