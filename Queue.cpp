#include "ProducerConsumer.hpp"
#include <iostream>
using namespace std;

ProducerConsumer::ProducerConsumer()
{
  queueFront=-1;
  queueEnd=-1;
}

bool ProducerConsumer::isEmpty()
{
  if (queueFront==-1 && queueEnd== -1)
  {
    return true;
  }
  return false;

}

bool ProducerConsumer::isFull()
{
  if (queueSize() == 20)
  {
    return true;
  }
  return false;

}

void ProducerConsumer::enqueue(string player)
{
  if (isFull())
  {
    cout << "Queue full, cannot add new item" << endl;
    return;
  }
  else if (isEmpty())
  {
    queueFront=0;
    queueEnd=0;
  }
  else
  {
    queueEnd=(queueEnd+1)%SIZE;
  }
  queue[queueEnd]=player;
}

void ProducerConsumer::dequeue()
{
  if (isEmpty())
  {
  cout << "Queue empty, cannot dequeue an item" << endl;
    return;
  }
  else if(queueFront==queueEnd)
  {
    queueFront=-1;
    queueEnd=-1;
  }
  else
  {
    queueFront=(queueFront+1)%SIZE;
  }


}

int ProducerConsumer::queueSize()
{
  int count=0;
  int beg=queueFront;
  int end=queueEnd;
  while (beg != end)
  {
    beg++;
    if (beg>=20)
    {
      beg=0;
    }
    count ++;
  }
  if (isEmpty()==false)
  {
  count++;
  }
  return count;


}

string ProducerConsumer::peek()
{
  if (isEmpty())
  {
    cout << "Queue empty, cannot peek" << endl;
    return "";
  }
  return queue[queueFront];

}
