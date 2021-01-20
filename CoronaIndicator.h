#include <string>
using namespace std;

typedef struct DataSet{
	string Country;
	int TotalCases;
	int NewCases;
	int TotalDeaths;
	int NewDeaths;
	int TotalRecovered;
	int ActiveCases;
	int CriticalCases;
	int Population;	
	int TotalTests;		
	float TotalCasesPerMillion;
	float DeathPerMillion;
	float TestPerMillion;
	string TravellingOutput;
	string TourismOutput;
}COORD;

class Node{
	friend class SingleLinkedList;
	friend class CovidTravelIndicator;
	friend class BST;
private:
	Node *Next;
	COORD Data;
	float AData;
public:
	Node();
	Node(float D);
};

class Node_Tree{
	friend class BST;
private:
	string Data;
	Node_Tree *Left;
	Node_Tree *Right;
public:
	Node_Tree();
	Node_Tree(string Data);
	~Node_Tree();
};

class BST{
private:
	Node_Tree *Root;
	int Size;
	string *Questions;
	float *Values;
public:
	BST();

	bool isEmpty();																					//Check if there are no nodes.
	
	Node_Tree* SetNewNode(string Ques);																//Getting a new node.

	Node_Tree* Insertion(Node_Tree* currentPtr , string Ques);
	
	void InOrder(Node_Tree *currentPtr);															//Traversal Methods.

	void PreOrder(Node_Tree *currentPtr);															//Traversal Methods.

	void PrintBSTCases(Node_Tree *root, int space = 0, int height = 10);							//2D representation of our tree.

	Node_Tree* getRoot();																			//Get the root pointer.
	
	bool isLeafNode(Node_Tree *currentPtr);															//Checking the leaf node properties.
	
	void setRoot(Node_Tree *ptr);																	//Setting the root ptr.

	void ReadQuestionBank();	//This reads our questionsBank.csv file into the program and makes a BST of Active cases ->New Deaths ->New cases

	void CriteriaSet(Node_Tree *tempPtr , Node *currentPtr2 , int index , string Travelling , string Tourism);	//This sets the criteria for the training dataset
																												//(UNSAFE OR SAFE) for each country.	

	void CriteriaCheck(Node_Tree *RootPtr , Node *currentPtr , int index , Node *tempPtr);	
	//This function is solely for testing Data to produce an output based on the training that the computer have done. Outputs from testing dataset shall be printed
	//In another TestingDataOutput.csv file.
};

class SingleLinkedList{
private:	
	Node *Head;
	Node *Tail;
	int Size;
public:
	SingleLinkedList ();																						//Default Constructor

	void InsertAtLast (COORD q);																				//LinkedList Insertion

	void Insert(float V);																						//Different Insertion For Active Cases , New Deaths and New Cases

	int Get_Size();																								//Returns size of the linked list.

	Node* getHead();																							//Returns the head pointer
	
	void DisplayList ();
	
};

class Stack{
private:
	int top;
	COORD *d;
public:	
	Stack();

	void Swap1(COORD* a, COORD* b)  ;

	int Partition(COORD arr[],int high,int low,int x);

	void QuickSort(COORD arr[], int low,int high,int x);
		
	void Sort(int x);

	void Push(COORD D) ;
	
	void Display(int x) ;
};

class NaiveBayes{
private:
	long double Total_Cases;
	long double Fever_Cases;
	long double Cough_Cases;
	long double Shortness_Breath_Cases;
	long double Tiredness_Cases;
	double Probability_Fever_Cases;
	double Probability_Cough_Cases;
	double Probability_ShortnessBreath_Cases;
	double Probability_Tiredness_Cases;
public:
	void Filing();

	void Calculate_Probability();
	
	void Predict_Covid(int num_symp,char *symp);
};

class CovidTravelIndicator{
private:
	Stack S;
	SingleLinkedList L;
	SingleLinkedList TestingList;
	BST B1;
public:
	bool Filteration(string (&Array)[15] , int Size);
	
	void Filing();
	
	void SearchByCountry(string Search_Country);
	
	void SearchSpecificCountry(string Search_Country);
	
	void Search_Safe_Toursim_Countries();

	void Search_Safe_Travelling_Countries();

	void DisplayWorldStats();

	void CountryByMostNumberOfDeaths();
	
	void CountryByMostNumberOfCases();
	
	void Build_Tree();

	void TestData_Filing();

	void Test_Data();
		
	void PrintBinaryTree();

	void SARSPrecaution();	
};

