#include "CoronaIndicator.h"
using namespace std;
#include <conio.h>
#include <stdio.h>
#include<bits/stdc++.h>
#define Max_Countries 100
#include <cstdlib>
#include <unistd.h>

Node::Node()
{
	Next = NULL;
	AData = 0;																//Type FLOAT to store the ActiveCases, New Deaths & New Cases of Countries
};
Node::Node(float D)
{
	Next = NULL;
	AData = D;
};
Node_Tree::Node_Tree()
{
	Data = "";
	Left = NULL;
	Right = NULL;
};
Node_Tree::Node_Tree(string Data)
{
	this->Data = Data;
	Left = NULL;
	Right = NULL;
};
Node_Tree::~Node_Tree()
{
	delete[] Left;
	delete[] Right;
	Data = "";
};
BST::BST()
{
	Root = NULL;
	Size = 0;
	Questions = NULL;
	Values = NULL;
};
bool BST::isEmpty()
{
	if (Root == NULL)
	{
		return true;
	}
	return false;
};
Node_Tree* BST::SetNewNode(string Ques)
{
	Node_Tree* NewNode = new Node_Tree(Ques);
	return NewNode;
};
Node_Tree* BST::Insertion(Node_Tree* currentPtr , string Ques)
{
	if (currentPtr == NULL)
	{
		return SetNewNode(Ques);
	}
	if (currentPtr->Left == NULL && currentPtr->Right == NULL)
	{
		//Will add the same Question on both, left and right node of the tree
		
		currentPtr->Left = SetNewNode(Ques);
		currentPtr->Right = SetNewNode( Ques);
	}
	else
	{
		Insertion(currentPtr->Left , Ques);
		Insertion(currentPtr->Right , Ques);
	}
	return currentPtr;
};
void BST::InOrder(Node_Tree *currentPtr)																//InOrder Traversal
{
	if (currentPtr != NULL)
	{
		InOrder(currentPtr->Left);
		cout << currentPtr->Data << " " << endl;
		InOrder(currentPtr->Right);
	}
};
void BST::PreOrder(Node_Tree *currentPtr)																//PreOrder Traversal
{	
	if (currentPtr != NULL)
	{
		cout << currentPtr->Data << " " << endl;
		PreOrder(currentPtr->Left);
		PreOrder(currentPtr->Right);
	}
};
void BST::PrintBSTCases(Node_Tree *root, int space , int height)										//Printing 2D Tree
{
    // Base case
    if (root == nullptr)
        return;
 
    // increase distance between levels
    space += height;
 
    // print right child first
    PrintBSTCases(root->Right, space);
    cout << endl;
 
    // print current node after padding with spaces
    for (int i = height; i < space; i++)
        cout << ' ';
    cout << root->Data;
 
    // print left child
    cout << endl;
    PrintBSTCases(root->Left, space);
};
Node_Tree* BST::getRoot()
{
	return Root;
};
void BST::setRoot(Node_Tree *ptr)
{
	Root = ptr;
};
void BST::ReadQuestionBank()			
{
	string line;
	string word;
	string Array[2];
	Questions = new string[3];
	Values = new float[3];
	fstream fin("QuestionsBank.csv",ios::in);														//Question Bank File Opening
	if (fin.is_open())
	{
		int i = 0;
		while(getline(fin,line))
		{	
			stringstream s(line);
			int j=0;
			while (getline(s,word,','))
			{
				Array[j] = word;
				j++;
			}
			Questions[i] = Array[0];
			Values[i] = stof (Array[1]);
			i++;
		}	
	}
	else
	{
		cout << "File doesnot exist." << endl;
	}
	fin.close();
	
	
	// Building Up Binary Search Tree
	
	Node_Tree *tempPtr = new Node_Tree();
	
	for(int i = 0 ; i < 3 ; i++)
	{
		if (isEmpty())
		{
			tempPtr = Insertion(getRoot() , Questions[i]);
			setRoot(tempPtr);																		//Setting Up The Root Pointer
		}	
		else
		{
			Insertion(getRoot() , Questions[i]);
		}
	}
};
bool BST::isLeafNode(Node_Tree *currentPtr)
{
	if (currentPtr->Right == NULL && currentPtr->Left == NULL)
	{
		return true;
	}
	else 
	{
		return false;
	}
};
void BST::CriteriaSet(Node_Tree *tempPtr , Node *currentPtr2 , int index , string Travelling , string Tourism)
{
	//For Training Data
	
	if (isEmpty())
	{
		return;
	}
	if (tempPtr->Data == "safe" || tempPtr->Data == "unsafe")
	{
		return;
	}
	
	//Condition is to Check Leaf Node & Check if "New Cases" Node has both Right and Left Filled.
	if (BST::isLeafNode(tempPtr) || ((tempPtr->Right == NULL || tempPtr->Left == NULL) && tempPtr->Data == "new cases"))
	{
		if (currentPtr2->AData < Values[index])															//If New Cases < 5000
		{
			tempPtr->Left = new Node_Tree(Travelling);
			tempPtr->Left->Left = new Node_Tree(Tourism);
		}
		else 																							//If New Cases > 5000
		{
			tempPtr->Right = new Node_Tree(Travelling);	
			tempPtr->Right->Left = new Node_Tree(Tourism);
		}
		return;
	}
	if (tempPtr == NULL)
	{
		return;
	}	
	if (currentPtr2->AData > Values[index])															//If Greater, Go Right
	{
		CriteriaSet(tempPtr->Right , currentPtr2->Next , index + 1 , Travelling , Tourism);	
	}
	else if (currentPtr2->AData < Values[index])													//If Lesser, Go Left
	{
		CriteriaSet(tempPtr->Left , currentPtr2->Next , index + 1 , Travelling , Tourism);	
	}
};
void BST::CriteriaCheck(Node_Tree *RootPtr , Node *currentPtr , int index , Node *tempPtr)
{
	//For Testing Data
	
	if (RootPtr == NULL)
	{
		return;
	}	
	if (RootPtr->Data == "new cases")
	{
		if (currentPtr->AData < Values[index])
		{
			tempPtr->Data.TravellingOutput = RootPtr->Left->Data;								//Saving Output in Struct
			tempPtr->Data.TourismOutput = RootPtr->Left->Left->Data;							//Saving Output in Struct
		}
		else 
		{
			tempPtr->Data.TravellingOutput = RootPtr->Right->Data;								//Saving Output in Struct
			tempPtr->Data.TourismOutput = RootPtr->Right->Left->Data;							//Saving Output in Struct
		}
		return;
	}
	if (currentPtr->AData > Values[index])														//If Greater, Go Right
	{
		CriteriaCheck(RootPtr->Right , currentPtr->Next , index + 1 , tempPtr);
	}
	else if (currentPtr->AData < Values[index])													//If Lesser, Go Left
	{
		CriteriaCheck(RootPtr->Left , currentPtr->Next , index + 1 , tempPtr);	
	}
};
SingleLinkedList::SingleLinkedList ()
{
	Size = 0;
	Head = Tail = NULL;
};
void SingleLinkedList::InsertAtLast (COORD q)
{
	Node *new_node = new Node;
	new_node->Data.ActiveCases=q.ActiveCases;
	new_node->Data.Country=q.Country;
	new_node->Data.NewCases=q.NewCases;
	new_node->Data.TotalCases=q.TotalCases;
	new_node->Data.TotalDeaths=q.TotalDeaths;
	new_node->Data.TotalCasesPerMillion=q.TotalCasesPerMillion;
	new_node->Data.NewDeaths=q.NewDeaths;
	new_node->Data.TotalRecovered=q.TotalRecovered;
	new_node->Data.CriticalCases=q.CriticalCases;
	new_node->Data.Population=q.Population;
	new_node->Data.TotalTests=q.TotalTests;
	new_node->Data.DeathPerMillion=q.DeathPerMillion;
	new_node->Data.TestPerMillion=q.TestPerMillion;
	new_node->Data.TravellingOutput = q.TravellingOutput;
	new_node->Data.TourismOutput = q.TourismOutput;
	new_node->Next = NULL;
	
	if(Head == NULL && Tail == NULL)
	{
		Head = new_node;
		Tail = new_node;
	}
	else
	{
		Tail->Next = new_node;
		Tail = new_node;
	}
	Size++;
};
void SingleLinkedList::Insert(float V)
{
	Node* new_node = new Node(V);
	if(Head == NULL && Tail == NULL)
	{
		Head = new_node;
		Tail = new_node;
	}
	else
	{
		Tail->Next = new_node;
		Tail = new_node;
	}
	Size++;
};
int SingleLinkedList::Get_Size()
{
	return Size;
};
Node* SingleLinkedList::getHead()
{
	return Head;
};
void SingleLinkedList::DisplayList ()
{
	Node *tempPtr = new Node();
	tempPtr = Head;	
	cout << "\tCountry" << setw(12) << " TotalCases" << setw(12) << " NewCases" <<  setw(12) << " TotalDeaths" <<  setw(12) << " NewDeaths " <<  setw(12) 
	<< " ActiveCases " <<  setw(12) << " TotalRecovered " <<  setw(12) << " CriticalCases  "<<  setw(12) << " Population " <<  setw(12) << "   TotalTests " << 
	 setw(12) << "    TotalCasesPerMillion" <<  setw(12) << endl;
	while(tempPtr!=NULL)
	{	
		cout << endl;
 	  	cout << tempPtr->Data.Country <<  setw(14) << tempPtr->Data.TotalCases <<  setw(14) << tempPtr->Data.NewCases <<  setw(14) << tempPtr->Data.TotalDeaths
		<<  setw(14) << tempPtr->Data.NewDeaths <<setw(14) <<tempPtr->Data.ActiveCases <<  setw(14) << tempPtr->Data.TotalRecovered << setw(14) 
		<< tempPtr->Data.CriticalCases <<  setw(14) << tempPtr->Data.Population <<  setw(14) << tempPtr->Data.TotalTests <<  setw(14) << 
		tempPtr->Data.TotalCasesPerMillion <<  setw(14) << endl;
      	tempPtr = tempPtr->Next;
	}
	cout << endl;
};

Stack::Stack()
{
	top=-1;
	d=new COORD [Max_Countries];
};
void Stack::Swap1(COORD* a, COORD* b)  
{  
    COORD t = *a;  
    *a = *b;  
    *b = t;  
};
int Stack::Partition(COORD arr[],int high,int low,int x)
{
	int i=low-1;
	for (int j=low;j<high;j++)
	{
		if (x==1)
		{
			if (arr[j].TotalDeaths<arr[high].TotalDeaths)
			{
				i++;
				Stack::Swap1(&arr[i],&arr[j]);
			}
		}
		else
		{
			if (arr[j].ActiveCases<arr[high].ActiveCases)
			{
				i++;
				Stack::Swap1(&arr[i],&arr[j]);
			}
		}
	}
	Stack::Swap1(&arr[i+1],&arr[high]);
	return i+1;
};		
void Stack::QuickSort(COORD arr[], int low,int high,int x)
{
	if (low<high)
	{
		int pi=0;
		pi=Stack::Partition(arr,high,low,x);
		QuickSort(arr,low,pi-1,x);
		QuickSort(arr,pi+1,high,x);
    }
};		
void Stack::Sort(int x){
	 Stack::QuickSort(d,0,Max_Countries-1,x);
};
void Stack::Push(COORD D) 
{
   if (top>=Max_Countries)
   {
   		cout<<"Full!";
   		return;
   }
   d[++top].Country=D.Country;
   d[top].TotalCases=D.TotalCases;
   d[top].NewCases=D.NewCases;
   d[top].CriticalCases=D.CriticalCases;
   d[top].DeathPerMillion=D.DeathPerMillion;
   d[top].ActiveCases=D.ActiveCases;
   d[top].NewDeaths=D.NewDeaths;
   d[top].Population=D.Population;
   d[top].TestPerMillion=D.TestPerMillion;
   d[top].TotalCasesPerMillion=D.TotalCasesPerMillion;
   d[top].TotalDeaths=D.TotalDeaths;
   d[top].TotalRecovered=D.TotalRecovered;
   d[top].TotalTests=D.TotalTests;
};
void Stack::Display(int x) 
{
	Stack::Sort(x);
	cout << "\nCountry: " <<d[top].Country;
	cout << "\nTotal Cases: " << d[top].TotalCases;
	cout << "\nNew Cases: " << d[top].NewCases;
	cout << "\nTotal Deaths: " << d[top].TotalDeaths;
	cout << "\nActive Cases: " << d[top].ActiveCases;
	cout << "\nTotal Recovered: " << d[top].TotalRecovered;
	cout << "\nCritical Cases: " << d[top].CriticalCases;
	cout << "\nPopulation: " << d[top].Population; 
	cout << "\nTotal Tests: " << d[top].TotalTests; 
	cout << "\nTotal Cases Per Million: " << d[top].TotalCasesPerMillion;
	cout << "\nDeath Per Million: " << d[top].DeathPerMillion;
	cout << "\nTests Per Million: " << d[top].TestPerMillion;
};

void NaiveBayes::Filing()
{
	string line;
	string word;
	string Array[5];
	fstream fin("Symptom.csv",ios::in);
	if (fin.is_open())
	{
		int i = 0;
		while(getline(fin,line))
		{	
			stringstream s(line);
			int j=0;
			while (getline(s,word,','))
			{
				Array[j] = word;
				j++;
			}
			this->Total_Cases = stoi (Array[0]);
			this->Fever_Cases = stoi (Array[1]);
			this->Cough_Cases = stoi (Array[2]);
			this->Shortness_Breath_Cases = stoi (Array[3]);
			this->Tiredness_Cases = stoi (Array[4]);
			i++;	
		}
	}
};
void NaiveBayes::Calculate_Probability()
{	
	this->Probability_Cough_Cases=this->Cough_Cases/this->Total_Cases;
	this->Probability_Fever_Cases=this->Fever_Cases/this->Total_Cases;
	this->Probability_ShortnessBreath_Cases=this->Shortness_Breath_Cases/this->Total_Cases;
	this->Probability_Tiredness_Cases=this->Tiredness_Cases/this->Total_Cases; 
};
void NaiveBayes::Predict_Covid(int num_symp,char *symp)
{
	int flag=0;
	double probab=0;
	double calc_probab=0;
	for (int i=0;i<num_symp;i++)
	{
		if (toupper(symp[i]=='F'))
		{
			flag=1;
			break;
		}
	}
	if (flag==0|| (num_symp==1 && toupper(symp[num_symp-1]=='F')))
	{
		cout<<"Very Minimal Chances Of Covid19";
		return;
	}
	for (int i=0;i<num_symp;i++)
	{
		if (toupper(symp[i])=='C')
		{ 	if (probab!=0)
				probab*=this->Probability_Cough_Cases; 
			else
				probab=this->Probability_Cough_Cases;
		}
		else if (toupper(symp[i])=='S')
		{
			if (probab!=0)
				probab*=this->Probability_ShortnessBreath_Cases;
			else
				probab=this->Probability_ShortnessBreath_Cases;
		}
		else if (toupper(symp[i])=='T')
		{
			if (probab!=0)
			probab*=this->Probability_Tiredness_Cases;
			else
			probab=this->Probability_Tiredness_Cases;		
		}
	}
	calc_probab=probab/this->Probability_Fever_Cases;  //conditional 
	if (calc_probab<0.50)
	{
		cout <<"  "<<setprecision(4)<<calc_probab*100 <<"% chance Of Covid 19. Very Less Chance Of Covid.No Need To Worry :)";
		return;
	}
	if (calc_probab>=0.50 && calc_probab<0.80)
	{
		cout <<"  "<<setprecision(4)<<calc_probab*100 <<"% Chance Of Covid 19. Get Yourself Tested. Chances That You Have Covid19 :)";
		return;
	}
	if (calc_probab>0.80)
	{
		cout <<"  "<<setprecision(4)<<calc_probab*100 <<"% Chance Of Covid 19. You Probably Have Covid19. Better Quarantine Yourself And Get Tested :)";
		return;
	}
};

bool CovidTravelIndicator::Filteration(string (&Array)[15] , int Size)
{
	//Removing Spaces and Invalid Characters from the file
	
	if (Array[0] == "")
	{
		return false;
	}
	for (int i = 0 ; i < Size ; i++)
	{
		if (Array[i] == "" || Array[i] == "N/A")
		{
			Array[i] = "0";
		}
	}
	return true;
};
void CovidTravelIndicator::Filing()
{
	string line;
	string word;
	string Array[15];
	fstream fin("TrainingData.csv",ios::in);
	COORD D;
	if (fin.is_open())
	{
		int i = 0;
		while(getline(fin,line))
		{	
			stringstream s(line);
			int j=0;
			while (getline(s,word,','))
			{
				Array[j] = word;
				j++;
			}
			if (Filteration(Array , 15))
			{
				D.Country = Array[0];
				D.TotalCases = stoi (Array[1]);
				D.NewCases = stoi (Array[2]);
				D.TotalDeaths = stoi (Array[3]);
				D.NewDeaths = stoi (Array[4]);
				D.TotalRecovered = stoi (Array[5]);
				D.ActiveCases = stoi (Array[6]);
				D.CriticalCases = stoi (Array[7]);
				D.TotalCasesPerMillion = stof (Array[8]);
				D.DeathPerMillion = stof (Array[9]);
				D.TotalTests = stoi (Array[10]);
				D.TestPerMillion = stof (Array[11]);
				D.Population = stoi (Array[12]);
				D.TravellingOutput = Array[13];
				D.TourismOutput = Array[14];
				L.InsertAtLast(D);
				S.Push(D);
				i++;	
			}
			else
			{
				cout << "\nFile doesnot exist." << endl;
			}
		}
	}
};
void CovidTravelIndicator::SearchByCountry(string Search_Country)
{	
	//Linear Search

	Node *currentPtr = new Node();
	currentPtr = L.getHead();
	while (currentPtr != NULL)
	{
		if (currentPtr->Data.Country == Search_Country)
		{
	 	  	cout << "\nCountry: " << currentPtr->Data.Country;
			cout << "\nTotal Cases: " << currentPtr->Data.TotalCases;
			cout << "\nNew Cases: " << currentPtr->Data.NewCases;
			cout << "\nTotal Deaths: " << currentPtr->Data.TotalDeaths;
			cout << "\nActive Cases: " << currentPtr->Data.ActiveCases;
			cout << "\nTotal Recovered: " << currentPtr->Data.TotalRecovered;
			cout << "\nCritical Cases: " << currentPtr->Data.CriticalCases;
			cout << "\nPopulation: " << currentPtr->Data.Population; 
			cout << "\nTotal Tests: " << currentPtr->Data.TotalTests; 
			cout << "\nTotal Cases Per Million: " << currentPtr->Data.TotalCasesPerMillion;
			cout << "\nDeath Per Million: " << currentPtr->Data.DeathPerMillion;
			cout << "\nTests Per Million: " << currentPtr->Data.TestPerMillion;			
		}
			currentPtr = currentPtr->Next;
	}
};
void CovidTravelIndicator::SearchSpecificCountry(string Search_Country)
{	
	//Linear Search
	
	Node *currentPtr = new Node();
	currentPtr = L.getHead();
	while (currentPtr != NULL)
	{
		if (currentPtr->Data.Country == Search_Country)
		{
	 	  	cout << "\nCountry: " << currentPtr->Data.Country;
			cout << "\nTotal Cases: " << currentPtr->Data.TotalCases;
			cout << "\nNew Cases: " << currentPtr->Data.NewCases;
			cout << "\nTotal Deaths: " << currentPtr->Data.TotalDeaths;
			cout << "\nActive Cases: " << currentPtr->Data.ActiveCases;
			cout << "\nTotal Recovered: " << currentPtr->Data.TotalRecovered;
			cout << "\nCritical Cases: " << currentPtr->Data.CriticalCases;
			cout << "\nPopulation: " << currentPtr->Data.Population; 
			cout << "\nTotal Tests: " << currentPtr->Data.TotalTests; 
			cout << "\nTotal Cases Per Million: " << currentPtr->Data.TotalCasesPerMillion;
			cout << "\nDeath Per Million: " << currentPtr->Data.DeathPerMillion;
			cout << "\nTests Per Million: " << currentPtr->Data.TestPerMillion;		
			cout << "\nTravelling: " << currentPtr->Data.TravellingOutput;
			cout << "\nTourism: " << currentPtr->Data.TourismOutput;
		}
		currentPtr = currentPtr->Next;
	}
};
void CovidTravelIndicator::Search_Safe_Toursim_Countries()
{
	Node *currentPtr = new Node();
	currentPtr = L.getHead();
	while (currentPtr != NULL)
	{
		if (currentPtr->Data.TourismOutput == "safe")
		{
	 	  	cout << endl << currentPtr->Data.Country << endl;
		}
		currentPtr = currentPtr->Next;
	}
};
void CovidTravelIndicator::Search_Safe_Travelling_Countries()
{
	Node *currentPtr = new Node();
	currentPtr = L.getHead();
	while (currentPtr != NULL)
	{
		if (currentPtr->Data.TravellingOutput == "safe")
		{
	 	  	cout << endl << currentPtr->Data.Country << endl;
		}
		currentPtr = currentPtr->Next;
	}
};
void CovidTravelIndicator::DisplayWorldStats()
{
	L.DisplayList();
};
void CovidTravelIndicator::CountryByMostNumberOfDeaths()
{
	
	S.Display(1);
};
void CovidTravelIndicator::CountryByMostNumberOfCases()
{
	S.Display(0);
};
void CovidTravelIndicator::Build_Tree()
{
	//Training Phase of Data
	
	Node* currentPtr = L.getHead();									
	B1.ReadQuestionBank();
	SingleLinkedList tList[71];														//Temporary Linked List to store Active Casses , New Deaths and New Cases
	int i = 0;
	while(currentPtr != NULL)
	{										
		tList[i].Insert(currentPtr->Data.ActiveCases);
		tList[i].Insert(currentPtr->Data.NewDeaths);	
		tList[i].Insert(currentPtr->Data.NewCases);
		
		//Function Calling to Train Machine
		
		B1.CriteriaSet(B1.getRoot() , tList[i].getHead() , 0 , currentPtr->Data.TravellingOutput , currentPtr->Data.TourismOutput);
		currentPtr = currentPtr->Next;
		i++;
	}	
};
void CovidTravelIndicator::TestData_Filing()
{
	string line;
	string word;
	string Array[15];
	fstream fin("TestingData.csv",ios::in);															//Testing Data File Opening
	COORD D2;
	if (fin.is_open())
	{
		int i = 0;
		while(getline(fin,line))
		{	
			stringstream s(line);
			int j=0;
			while (getline(s,word,','))
			{
				Array[j] = word;
				j++;
			}
			if (Filteration(Array , 13))
			{
				D2.Country = Array[0];
				D2.TotalCases = stoi (Array[1]);
				D2.NewCases = stoi (Array[2]);
				D2.TotalDeaths = stoi (Array[3]);
				D2.NewDeaths = stoi (Array[4]);
				D2.TotalRecovered = stoi (Array[5]);
				D2.ActiveCases = stoi (Array[6]);
				D2.CriticalCases = stoi (Array[7]);
				D2.TotalCasesPerMillion = stof (Array[8]);
				D2.DeathPerMillion = stof (Array[9]);
				D2.TotalTests = stoi (Array[10]);
				D2.TestPerMillion = stof (Array[11]);
				D2.Population = stoi (Array[12]);
				D2.TravellingOutput = "";
				D2.TourismOutput = "";
				TestingList.InsertAtLast(D2);
				i++;	
			}
			else
			{
				cout << "\nFile doesnot exist." << endl;
			}
		}
	}
};
void CovidTravelIndicator::Test_Data()
{
	//Testing Phase of Data
	
	TestData_Filing();
	SingleLinkedList tempList[35];											
	int i = 0;
	Node* currentPtr = TestingList.getHead();
	Node* tempPtr = TestingList.getHead();
	fstream fout("TestingDataWithOutput.csv",ios::app);												//Testing Data Output File
	while(currentPtr != NULL)
	{										
		tempList[i].Insert(currentPtr->Data.ActiveCases);
		tempList[i].Insert(currentPtr->Data.NewDeaths);	
		tempList[i].Insert(currentPtr->Data.NewCases);
		B1.CriteriaCheck(B1.getRoot() , tempList[i].getHead() , 0 , tempPtr );
		fout << currentPtr->Data.Country << "," << currentPtr->Data.TravellingOutput << "," << currentPtr->Data.TourismOutput << endl;
		i++;
		currentPtr = currentPtr->Next;
		tempPtr = tempPtr->Next;
	}
	fout.close();
};
void CovidTravelIndicator::PrintBinaryTree()
{
	B1.BST::PrintBSTCases(B1.getRoot());
};
void CovidTravelIndicator::SARSPrecaution()
{
	string ch="COVID-19 TRANSMISSION AND PROTECTIVE MEASURES";
	cout<<"\t\t\t";
	for(int i=0;i<44;i++){
		cout<<ch[i];
		usleep(10000);
	}
	cout << endl;
	fstream fin("Precautions.txt");
	if (fin.is_open())
   cout << fin.rdbuf();
};
