#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class ListNode
{
    friend class LinkedList;

    public:
        ListNode();
        ListNode(string d);
        ListNode(string d, ListNode *n);

    	string data;
        ListNode* next;
        int count = 0;
};

class LinkedList
{
    public:
        LinkedList();
        ListNode* findSpot(string dataToFind);
        void listInsert(ListNode * spot, ListNode * newNode);
        string debugPrint();
        string printSortedList();
        bool containsCommonWord(string word);

    private:
    	ListNode *listHead = new ListNode();
        ListNode *dummy = new ListNode();
        
};

int main(int argc, char ** argv){

	LinkedList CWordListHead;
	LinkedList textListHead;
	string word = "";
	string textWord = "";

	ifstream inFile1;
	inFile1.open(argv[1]);
	ifstream inFile2;
	inFile2.open(argv[2]);
	ofstream outFile1;
	outFile1.open(argv[3]);
	ofstream outFile2;
	outFile2.open(argv[4]);

	while (inFile1>>word) 
	{
		ListNode *spot = CWordListHead.findSpot(word);
		ListNode *newWord = new ListNode(word);
		CWordListHead.listInsert(spot, newWord);
	
		string wordList = CWordListHead.debugPrint();
		outFile1 << wordList << endl;
	}
	outFile1 << "\n\n";
	
	int insertionCount = 0;
    while(inFile2 >> textWord){
        if(!CWordListHead.containsCommonWord(textWord)){
            ListNode* spot = textListHead.findSpot(textWord);

            if(spot != NULL){
                ListNode* newWord  = new ListNode(textWord);
                textListHead.listInsert(spot, newWord);
                insertionCount++;
            }
        }

        if(insertionCount >= 5){
            outFile1 << (textListHead.debugPrint() + "\n\n");
            insertionCount = 0;
        }
    }
    
    outFile2 << (textListHead.printSortedList());

	inFile1.close();
	inFile2.close();
    outFile1.close();
    outFile2.close();
	return 0;
}

ListNode::ListNode(){}

ListNode::ListNode(string d)
	:data(d), count(1), next(NULL)
	{}
	
ListNode::ListNode(string d, ListNode *n) {
	count = 1;
	data = d;
	next = n;
}

LinkedList::LinkedList()
{
    string d = "dummy";
	dummy->data = d;
	listHead->data = "ListHead";
	listHead->next = dummy;
}

ListNode* LinkedList::findSpot(string dataToFind) {
	ListNode *spot = listHead->next;

	while (spot->next != NULL  && spot->next->data.compare(dataToFind) <= 0) {
		spot = spot->next;
	}

    if(spot->data == dataToFind){
        spot->count++;
        return NULL;
    }
    else{
        return  spot;
    }

}

void LinkedList::listInsert(ListNode *spot, ListNode *newNode) {
	newNode->next = spot->next;
	spot->next = newNode;
}

string LinkedList::debugPrint() {
	ListNode *temp = listHead->next;

	string toReturn = listHead->data;

	while (temp != NULL) {
		toReturn += " --> (" + temp->data + ", ";
		if (temp->next == NULL) {
			toReturn += "null)";
		}
		else {
			toReturn += temp->next->data + ")";
		}
		temp = temp->next;
	}

	return toReturn;
}

string LinkedList::printSortedList(){
    ListNode* temp = listHead->next->next;
    string toReturn = "";

    while(temp != NULL){
        toReturn += temp->data+ "    " + to_string(temp->count) + "\n";
        temp = temp->next;
    }

    return toReturn;
}

bool LinkedList::containsCommonWord(string data){
    ListNode* temp = listHead->next;

    while(temp != NULL){
        if (temp->data == data) return true;
        temp = temp->next;
    }
    return false;
}
