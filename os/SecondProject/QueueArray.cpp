#include "QueueArray.h"
#include <cstddef>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;
//Alex Wellock
//Constructor for the queue array.  It sets the default size
//to 10, initializes the private variables size and totalItems
template <class etype>
QueueArray<etype>::QueueArray(int sz = 10):size(sz),totalItems(0)
{
  array = new queue<etype>[size];
  if( array == NULL)
  {
    cout << "Not enough memory to create the array" << endl;
    exit(-1);
  }
}

template <class etype>
QueueArray<etype>::~QueueArray()
{
    delete [] array;
}

/**
    Enqueues item in the queue of array index
    index. Returns 1 if item is successfully enqueued; -1, if index is out of range; 0,
    otherwise
**/
template <class etype>
int QueueArray<etype>::Enqueue(const etype &item ,int index){
    if(index > size){
        return -1;
    }
    queue<etype> &q = array[index];
    try{
        q.push(item);
    }
    catch(...){return 0;}
    totalItems++;
    return 1;

}
template <class etype>
etype QueueArray<etype>::Dequeue(){
    for(int i = 0; i < size; i++){
        queue<etype> &q = array[i];
        if(q.size() > 0){
            etype var = q.front();
            q.pop();
            return var;
        }
    }
    return 0;
}

template <class etype>
int QueueArray<etype>::Qsize(int index){
    if(index > size){
        return -1;
    }
    queue<etype> q = array[index];
    return q.size();
}

template <class etype>
int QueueArray<etype>::Asize(){
    return size;
}

template <class etype>
int QueueArray<etype>::QAsize(){
    return totalItems;
}
template <class etype>
etype* QueueArray<etype>::Qstate(int index){
    if(index > size){
        return NULL;
    }
    etype* theCopy;
    queue<etype> toCopy = array[index]; //curent queue to be copyed
    theCopy = new etype [toCopy.size()]; //queue to be returned
    for(int i = 0; i < toCopy.size(); i++){
        etype var = toCopy.front();
//        cout << "THE VAR IS:  " << var << endl;
        toCopy.pop();
        theCopy[i] = var;
        toCopy.push(var);
    }
//    cout << "WHAT IS IN THE ARRAY" << endl;
//    for(int i = 0; i < toCopy.size(); i++){
//        cout << theCopy[i] <<" ";
//    }
    cout << endl;
    return theCopy;
}
