#ifndef QUEUEARRAY_H
#define QUEUEARRAY_H
#include <queue>
using namespace std;
template <class etype>
class QueueArray
{
    public:
    QueueArray(int);
    ~QueueArray();
    int Asize();
    etype Dequeue();
    int Enqueue(const etype &item,const int index);
    int QAsize();
    int Qsize(int index) ;
    etype* Qstate(int index);

  private:
    int size;      //size of the array
    queue<etype>* array;   //the array of queues
    int totalItems; //total number of items stored in the queues
};

#endif // QUEUEARRAY_H
