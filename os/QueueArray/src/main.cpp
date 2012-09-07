#include <iostream>
#include "QueueArray.cpp"

using namespace std;
int main()
{
  QueueArray <int> qai(5);
  QueueArray <char> qac(8);
  int i, r, *ibuf, ielem;
  char *cbuf, celem;


  cout << "Size of the int queue array is " << qai.Asize()
       << endl;
  cout << "Total number of elements in the char queue array is "
       << qac.QAsize() << endl;

  cout << endl;
  for (i = 0; i < 5; i++) {
    r = qai.Enqueue(i, 0);
    cout << "Return value is " << r << endl;
  }
  r = qai.Enqueue(10, 10);
  cout << "Return value is " << r << endl;
  for (i = 0; i < 8; i++) qai.Enqueue(7, 2);
  for (i = 0; i < 2; i++) qai.Enqueue(10, 4);

  cout << "Number of elements in the first queue in int queue array is "
       << qai.Qsize(0) << endl;
  cout << "Number of elements in the second queue in int queue array is "
       << qai.Qsize(1) << endl;
  cout << "Number of elements in the third queue in int queue array is "
       << qai.Qsize(2) << endl;
  cout << "Number of elements in the fourth queue in int queue array is "
       << qai.Qsize(3) << endl;
  cout << "Number of elements in the fifth queue in int queue array is "
       << qai.Qsize(4) << endl;
  cout << "Total number of elements in the int queue array is "
       << qai.QAsize() << endl;

  cout << endl;

  for (i = 0; i < 11; i++) {
    r = qac.Enqueue('a', 6);
    cout << "Return value is " << r << endl;
  }
  for (i = 0; i < 6; i++) qac.Enqueue('b', 1);
  for (i = 0; i < 4; i++) qac.Enqueue('c', 5);

  cout << "Number of elements in the second queue in char queue array is "
       << qac.Qsize(1) << endl;
  cout << "Number of elements in the third queue in char queue array is "
       << qac.Qsize(2) << endl;
  cout << "Number of elements in the fourth queue in char queue array is "
       << qac.Qsize(3) << endl;
  cout << "Total number of elements in the char queue array is "
       << qac.QAsize() << endl;

  cout << endl;

  cbuf = qac.Qstate(6);
  cout << "Elements in the seventh queue in char queue array are";
  for (i = 0; i < qac.Qsize(6); i++) cout << " " << cbuf[i];
  cout << endl;

  cout << endl;

  ibuf = qai.Qstate(4);
  cout << " Elements in the fifth queue in int queue array are";
  for (i = 0; i < qai.Qsize(4); i++) cout << " " << ibuf[i];
  cout << endl;

  ielem = qai.Dequeue();
  cout << "Dequeued element from the int queue array is " << ielem << endl;
  ielem = qai.Dequeue();
  cout << "Dequeued element from the int queue array is " << ielem << endl;
  ibuf = qai.Qstate(0);
  cout << " Elements in the first queue in int queue array are";
  for (i = 0; i < qai.Qsize(0); i++) cout << " " << ibuf[i];
  cout << endl;

  cbuf = qac.Qstate(1);
  cout << " Elements in the second queue in char queue array are";
  for (i = 0; i < qac.Qsize(1); i++) cout << " " << cbuf[i];
  cout << endl;

  celem = qac.Dequeue();
  cout << "Dequeued element from the char queue array is " << celem << endl;
  celem = qac.Dequeue();
  cout << "Dequeued element from the char queue array is " << celem << endl;
  celem = qac.Dequeue();
  cout << "Dequeued element from the char queue array is " << celem << endl;
  cbuf = qac.Qstate(1);
  cout << " Elements in the second queue in char queue array are";
  for (i = 0; i < qac.Qsize(1); i++) cout << " " << cbuf[i];
  cout << endl;
  return 0;
}
