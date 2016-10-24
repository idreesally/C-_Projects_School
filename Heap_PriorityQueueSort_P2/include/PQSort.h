#ifndef PQSORT_H
#define PQSORT_H
#include "fstream"
#include <iostream>
#include <math.h>

using namespace std;
class PQSort
{
    public:
        PQSort(int size);
        int getFinalArraySize();
        int getCurrentHeapSize();
        void buildPQArray(ifstream &inFile, ofstream &outFile1);
        void insertOneDataItem(int data);
        void bubbleUp(int kidIndex);
        void deletePQArray(ofstream &outFile1, ofstream &outFile2);
        int deleteRoot();
        void bubbleDown();
        int root();
        void printPQArray(ofstream &outFile1);
        bool isPQArrayFull();
        bool isPQArrayEmpty();
        virtual ~PQSort();

    protected:

    private:
        int finalHeapSize;
        int currentHeapSize;
        static const int ROOT_INDEX = 1;
        int* PQAry;
        int getFatherIndex(int i);
        int getLeftChildIndex(int i);
        int getRightChildIndex(int i);
        bool hasLeftChild(int i);
        bool hasRightChild(int i);
};

#endif // PQSORT_H
