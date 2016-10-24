#include <iostream>
#include <fstream>

using namespace std;

class ListNode
{	
	friend class LinkedListStack;
	
	public:
		string data;
		ListNode* next;
		
		ListNode();
		ListNode(string d);
};

class LinkedListStack
{	
	friend class RadixSort;

	public:
		ListNode* top;
		int stackSize;
		int longestStringLength;
	
		LinkedListStack();
		void push(ListNode* newNode);
		ListNode* pop();
		bool isEmpty();
		void printStack();
};

class LinkedListQueue
{
	friend class RadixSort;
	
	public:
		ListNode* head;
		ListNode* tail;
		int queueSize;
		
		LinkedListQueue();
		void addTail(ListNode* newNode);
		ListNode* deleteHead();
		bool isEmpty();
		void printQueue();		
};

class RadixSort{
	
	public:
		static const int tableSize = 256;
		int currentDigit;
		int currentTable;
		LinkedListQueue** hashTable;
	
		RadixSort(LinkedListStack lls);
		void performSort(LinkedListStack lls);
		void padString(ListNode* nodeToPad, int longestStringLength);
		char getVal(ListNode* node, int digitIndex);
		int getHashIndex(char val);
		void printTable(LinkedListQueue table[]);
};

int main(int argc, char ** argv)
{	
	ifstream inFile;
	inFile.open(argv[1]);
	
	LinkedListStack stack;
	string word = "";
		
	while(inFile>>word)
	{		
		ListNode* newWord = new ListNode(word);
		stack.push(newWord);
	}
			
	stack.printStack();
	RadixSort* rs = new RadixSort(stack);
	
	return 0;
}

//-------------------- LIST NODE --------------------------//
ListNode::ListNode(){}

ListNode::ListNode(string d)
{
	data = d;
	next = NULL;
}

//------------------LINKED LIST STACK --------------------//
LinkedListStack::LinkedListStack()
{
	stackSize = 0;
	longestStringLength = 0;
	top = NULL;
}

void LinkedListStack::push(ListNode* newNode)
{
	if(isEmpty())
	{
		top = newNode;
	}
	else{
		newNode->next = top;
		top = newNode;
	}
	if(newNode->data.length() > longestStringLength) longestStringLength = newNode->data.length();
	stackSize++;
}

ListNode* LinkedListStack::pop()
{
	if(stackSize > 1)
	{
		ListNode* temp = top;
		top = top->next;
		stackSize--;
		return temp;
	}
	else if(stackSize == 1)
	{
		ListNode* temp = top;
		top = NULL;
		stackSize--;
		return temp;
	}
	else if(isEmpty()){
		return NULL;
	}
}
bool LinkedListStack::isEmpty()
{
	if(stackSize==0) return true;
	else return false;
}

void LinkedListStack::printStack()
{
	cout<< "-----------STACK PRINTING----------" << endl;
	ListNode* tempTop = top; 
	
	while(tempTop != NULL){
		cout << tempTop->data << endl;
		tempTop = tempTop->next;
	}
	cout << endl <<endl;
}

//--------------------- LINKED LIST QUEUE -------------------//
LinkedListQueue::LinkedListQueue()
{
	ListNode* dummy = new ListNode();
	head = dummy;
	tail = dummy;
	
	queueSize = 0;
}

void LinkedListQueue::addTail(ListNode* newNode)
{
	newNode->next = NULL;
	if(isEmpty()){
		head = newNode;
		tail = newNode;
		queueSize++;
	}
	else{
		tail->next = newNode;
		tail = newNode;
		queueSize++;
	}
}

ListNode* LinkedListQueue::deleteHead()
{
	if(queueSize > 0)
	{
		ListNode* temp = head;
		head = head->next;
		queueSize--;
		return temp;
	} 
	else return NULL;
}

void LinkedListQueue::printQueue()
{
	ListNode* tempHead = head;
	cout << tempHead->data;
	tempHead = tempHead->next;
	
	while(tempHead != NULL)
	{ 
		cout << "," << tempHead->data;
		tempHead = tempHead->next;
	}
	cout << endl << endl;
}

bool LinkedListQueue::isEmpty()
{
	if(queueSize==0) return true;
	else return false;
}

//------------------------- Radix Sort -----------------------//
RadixSort::RadixSort(LinkedListStack lls)
{
	currentDigit = lls.longestStringLength; // -1
	currentTable = 0;
	
	hashTable = new LinkedListQueue*[2];
	hashTable[0] = new LinkedListQueue[tableSize];
	hashTable[1] = new LinkedListQueue[tableSize];

	performSort(lls);
}

void RadixSort::performSort(LinkedListStack lls)
{
	while(!lls.isEmpty()){
		ListNode* newNode = lls.pop();
		
		padString(newNode, lls.longestStringLength);
		char val = getVal(newNode, currentDigit);
		int hashIndex = getHashIndex(val);
		
		hashTable[currentTable][hashIndex].addTail(newNode);
	}
	
	printTable(hashTable[currentTable]);

	currentDigit--; //access the 2nd digit
	currentTable = 1; //currentTable = hashTable[2]
	int previousTable = 0; // hashtable[1]
	int currentQueue = 0;

	while(currentDigit > -1)
	{
		while(currentQueue < tableSize-1)
		{
			while(!hashTable[previousTable][currentQueue].isEmpty())
			{
				ListNode* newNode = hashTable[previousTable][currentQueue].deleteHead();
				char val = getVal(newNode, currentDigit);
				int hashIndex = getHashIndex(val);
				hashTable[currentTable][hashIndex].addTail(newNode);
			}
			currentQueue++;
		}
		
		//printTable(hashTable[currentTable]);
		int temp = currentTable;
		currentTable = previousTable;
		previousTable = temp;
		currentQueue=0;
		currentDigit--;
	}
	
	printTable(hashTable[previousTable]);
	//printTable(hashTable[currentTable]);
}

void RadixSort::padString(ListNode* nodeToPad, int longestStringLength)
{
	string newString = nodeToPad->data;
	int startCount = nodeToPad->data.length();
	
	for(int i=startCount; i< longestStringLength; i++)  
	{	
		//newString = " " + newString;	
		newString += " ";
	}
	newString = " " + newString;
	nodeToPad->data = newString;
}

char RadixSort::getVal(ListNode* node, int digitIndex)
{
	char val = node->data[digitIndex];
	return val;
}

int RadixSort::getHashIndex(char val)
{
	int index = (int) val;
	return index;
}

void RadixSort::printTable(LinkedListQueue table[])
{
	cout << "------------- TABLE PRINTING ---------------" << endl;
	for(int i = 0; i < tableSize; i++)
	{
		if(!table[i].isEmpty()){
			cout << "Table[" << currentTable << "][" << i << "]: ";
			table[i].printQueue();
		}	
	}
}
