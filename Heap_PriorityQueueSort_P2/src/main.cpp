#include <iostream>
#include <fstream>
#include "PQSort.h"


using namespace std;
int main(int argc, char** argv){
    //cout << 1/2 << endl;

    ifstream inFile;
    inFile.open(argv[1]);
    ofstream outFile1;
    outFile1.open(argv[2]);
    ofstream outFile2;
    outFile2.open(argv[3]);
    int data, size = 0;

    while(inFile >> data){
        //cout << data << endl;
        size++;
    }

    inFile.close();
    PQSort* pq = new PQSort(size);
    //cout << endl << pq->getFinalArraySize() << endl;

    inFile.open(argv[1]);
    pq->buildPQArray(inFile,outFile1);
    pq->deletePQArray(outFile1, outFile2);

}
