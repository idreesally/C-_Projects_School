#include "PQSort.h"


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
        //cout << data << endl;
        insertOneDataItem(data);
        //cout << PQAry[0] <<"    " <<PQAry[getCurrentHeapSize()] << endl;
        //CURRENT HEAP SIZE NOW 1, on first iteration after InsertOneDataItem
        bubbleUp(getCurrentHeapSize());
        printPQArray(outFile1);
    }
    inFile.close();
    cout << getCurrentHeapSize() << "    " << getFinalArraySize() << "     " << endl;
    //cout << PQAry[getFinalHeapSize()] << "      " << getFinalHeapSize();

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
    cout << "deletePQArray working" << endl;
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
            //cout << PQAry[i] << "     ";
            outFile1 << PQAry[i] << "    ";
    }
    //cout <<endl;
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

int PQSort::root(){
    return PQAry[1];
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
