#include "fstream"
#include <iostream>
#include <math.h>

using namespace std;
class PQSort
{
    public:
        int getFinalArraySize();
        int getCurrentHeapSize();
        PQSort(int size);
        void buildPQArray(ifstream &inFile, ofstream &outFile1);
        void insertOneDataItem(int data);
        void bubbleUp(int kidIndex);
        void deletePQArray(ofstream &outFile1, ofstream &outFile2);
        int deleteRoot();
        void bubbleDown();
        void printPQArray(ofstream &outFile1);
        bool isPQArrayFull();
        bool isPQArrayEmpty();
        virtual ~PQSort();

    protected:

    private:
        int* PQAry;
        int finalHeapSize;
        int currentHeapSize;
        static const int ROOT_INDEX = 1;
        int getFatherIndex(int i);
        int getLeftChildIndex(int i);
        int getRightChildIndex(int i);
        bool hasLeftChild(int i);
        bool hasRightChild(int i);
};


int main(int argc, char** argv){

    ifstream inFile;
    inFile.open(argv[1]);
    ofstream outFile1;
    outFile1.open(argv[2]);
    ofstream outFile2;
    outFile2.open(argv[3]);
    int data, size = 0;

    while(inFile >> data){
        size++;
    }

    inFile.close();
    PQSort* pq = new PQSort(size);

    inFile.open(argv[1]);
    pq->buildPQArray(inFile,outFile1);
    pq->deletePQArray(outFile1, outFile2);
}

PQSort::PQSort(int size)
{
    finalHeapSize = size+1;
    PQAry = new int[finalHeapSize];
    PQAry[0] = 0;
    currentHeapSize = 0;
}

void PQSort::buildPQArray(ifstream &inFile, ofstream &outFile1){
    int data = 0;
    while(inFile >> data){

        insertOneDataItem(data);
        //CURRENT HEAP SIZE NOW 1, on first iteration after InsertOneDataItem
        bubbleUp(getCurrentHeapSize());
        printPQArray(outFile1);
    }
    inFile.close();
}

void PQSort::insertOneDataItem(int data){
    if(!isPQArrayFull()){
        currentHeapSize++;
        PQAry[getCurrentHeapSize()] = data;
        PQAry[0] = currentHeapSize;

    }
}

void PQSort::bubbleUp(int kidIndex){
    int fatherIndex = getFatherIndex(kidIndex);
    while(PQAry[kidIndex] < PQAry[fatherIndex]){
        if(kidIndex == 1) break;
        int temp = PQAry[fatherIndex];
        PQAry[fatherIndex] = PQAry[kidIndex];
        PQAry[kidIndex] = temp;
        kidIndex = fatherIndex;
        fatherIndex = getFatherIndex(kidIndex);
    }
}

void PQSort::deletePQArray(ofstream &outFile1, ofstream &outFile2){
    while(!isPQArrayEmpty()){
        outFile2 << "| " << deleteRoot() << " ";
        if(getCurrentHeapSize() > 0) bubbleDown();
        printPQArray(outFile1);
    }
    outFile2 << "|";
    outFile1.close();
    outFile2.close();
}

int PQSort::deleteRoot(){
    int root = PQAry[ROOT_INDEX];
    PQAry[ROOT_INDEX] = PQAry[getCurrentHeapSize()];
    currentHeapSize--;
    PQAry[0] = getCurrentHeapSize();
    return root;
}

void PQSort::bubbleDown(){
    int fatherIndex = ROOT_INDEX;
    int bubbleDownValue = PQAry[fatherIndex];

    while(hasLeftChild(fatherIndex)){
        int smallKidIndex = getLeftChildIndex(fatherIndex);
        if(hasRightChild(fatherIndex) && PQAry[getRightChildIndex(fatherIndex)] < PQAry[smallKidIndex]){
            smallKidIndex = getRightChildIndex(fatherIndex);
        }
        if(PQAry[smallKidIndex] >= bubbleDownValue) break;
        PQAry[fatherIndex] = PQAry[smallKidIndex];
        fatherIndex = smallKidIndex;
    }
    PQAry[fatherIndex] = bubbleDownValue;
}
void PQSort::printPQArray(ofstream &outFile1){
    for(int i=0; i < min(getCurrentHeapSize() +1, 10) ; i++){
            outFile1 << PQAry[i] << "    ";
    }
    outFile1 << endl;
}

bool PQSort::isPQArrayFull(){
    if(getCurrentHeapSize() < getFinalArraySize()) return false;
    else return true;
}

bool PQSort::isPQArrayEmpty(){
    if(getCurrentHeapSize() == 0) return true;
    else return false;
}

int PQSort::getCurrentHeapSize(){
    return currentHeapSize;
}

int PQSort::getFinalArraySize(){
    return finalHeapSize;
}

int PQSort::getFatherIndex(int i){
    return (i/2);
}

int PQSort::getLeftChildIndex(int i){
    return (2*i);
}

int PQSort::getRightChildIndex(int i){
    return (2*i + 1);
}

bool PQSort::hasLeftChild(int i){
    if(getLeftChildIndex(i) <= getCurrentHeapSize()) return true;
    else return false;
}

bool PQSort::hasRightChild(int i){
    if(getRightChildIndex(i) <= getCurrentHeapSize()) return true;
    else return false;
}

PQSort::~PQSort()
{
    delete [] PQAry;
}
