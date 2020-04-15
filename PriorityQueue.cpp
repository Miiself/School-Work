#include "PriorityQueue.hpp"
#include <iostream>
using namespace std;
void swap(GroupNode *a, GroupNode *b)
{
  GroupNode temp=*a;
  *a=*b;
  *b=temp;
}

void PriorityQueue::repairDownward(int index)
{
  int lc=(2*index)+1;
  int rc=(2*index)+2;
  int small=index;
  if (lc< currentQueueSize  && priorityQueue[lc].groupSize < priorityQueue[index].groupSize)
    {
      small=lc;
    }
  if (lc < currentQueueSize && priorityQueue[lc].groupSize==priorityQueue[small].groupSize && priorityQueue[lc].cookingTime<priorityQueue[small].cookingTime )
  {
    small=lc;
  }
  if (lc<currentQueueSize && rc<currentQueueSize && priorityQueue[lc].groupSize==priorityQueue[rc].groupSize  )
  {
    if(priorityQueue[rc].groupSize > priorityQueue[small].groupSize)
    {
        return;
    }
    else if (priorityQueue[rc].groupSize == priorityQueue[small].groupSize)
    {
        if (priorityQueue[lc].cookingTime < priorityQueue[small].cookingTime)
            small = lc;
        if (priorityQueue[lc].cookingTime < priorityQueue[small].cookingTime)
            small = rc;
         if (small != index)
         {
            swap(&priorityQueue[index], &priorityQueue[small]);
            repairDownward(small);
            return;
         }
    }
    else
    {

        if (priorityQueue[lc].cookingTime < priorityQueue[rc].cookingTime)
            {
              small=lc;
            }
        else
            {
              small=rc;
            }
        swap(&priorityQueue[index], &priorityQueue[small]);
        repairDownward(small);
        return;
    }
  }
  if (rc<currentQueueSize && priorityQueue[rc].groupSize < priorityQueue[small].groupSize)
   {
     small=rc;
   }
  if (rc < currentQueueSize && priorityQueue[rc].groupSize==priorityQueue[small].groupSize && priorityQueue[rc].cookingTime<priorityQueue[small].cookingTime )
  {
    small=rc;
  }

  if (small != index)
  {
    swap(&priorityQueue[index], &priorityQueue[small]);
    repairDownward(small);
  }
}

void PriorityQueue::repairUpward(int index)
{
    if (index==0)
    {
        return;
    }
  int parent=(index-1)/2;
  if (priorityQueue[index].groupSize>priorityQueue[parent].groupSize)
  {
    return;
  }
  else if(priorityQueue[index].groupSize==priorityQueue[parent].groupSize && priorityQueue[index].cookingTime>priorityQueue[parent].cookingTime)
  {
    return;
  }
  if (priorityQueue[index].groupSize<priorityQueue[parent].groupSize)
  {

    swap(&priorityQueue[index], &priorityQueue[parent]);

  }
  else if(priorityQueue[index].groupSize==priorityQueue[parent].groupSize && priorityQueue[index].cookingTime<priorityQueue[parent].cookingTime)
  {
    swap(&priorityQueue[index], &priorityQueue[parent]);
  }
  index=parent;
  repairUpward(index);

}


PriorityQueue::PriorityQueue(int queueSize)
{
  maxQueueSize=queueSize;
  currentQueueSize=0;
  priorityQueue=new GroupNode[queueSize];
}

PriorityQueue::~PriorityQueue()
{
  delete[] priorityQueue;
}

void PriorityQueue::enqueue(string groupName, int groupSize, int cookTime)
{

  GroupNode temp=GroupNode();
  temp.groupName=groupName;
  temp.groupSize=groupSize;
  temp.cookingTime=cookTime;
  priorityQueue[currentQueueSize]=temp;
  currentQueueSize++;
  if (currentQueueSize>1)
  {
  repairUpward(currentQueueSize-1);
  }

}

void PriorityQueue::dequeue()
{
  if (isEmpty())
  {
    cout << "Heap empty, cannot dequeue" << endl;
    return;
  }
  if (currentQueueSize==1)
  {
    currentQueueSize--;
    GroupNode temp;
    priorityQueue[0]=temp;
  }
  else if (currentQueueSize>1)
  {
    GroupNode temp;
    priorityQueue[0]=priorityQueue[currentQueueSize-1];
    priorityQueue[currentQueueSize-1]=temp;
    currentQueueSize--;
    repairDownward(0);
  }
}

GroupNode PriorityQueue::peek()
{
  return priorityQueue[0];
}

bool PriorityQueue::isFull()
{
  if (currentQueueSize==maxQueueSize)
  {
    return true;
  }
  return false;

}

bool PriorityQueue::isEmpty()
{
  if (currentQueueSize==0)
  {
    return true;
  }
  return false;
}


// void PriorityQueue::repairDownward(int index)
// {
//   int lc=(2*index)+1;
//   int rc=(2*index)+2;
//   int small=index;
//   if (lc<currentQueueSize && rc<currentQueueSize && priorityQueue[lc].groupSize==priorityQueue[rc].groupSize  )
//   {
//     if(priorityQueue[rc].groupSize > priorityQueue[small].groupSize)
//     {
//         return;
//     }
//     else if (priorityQueue[rc].groupSize == priorityQueue[small].groupSize)
//     {
//         if (priorityQueue[lc].cookingTime < priorityQueue[small].cookingTime)
//             small = lc;
//         if (priorityQueue[lc].cookingTime < priorityQueue[small].cookingTime)
//             small = rc;
//          if (small != index)
//          {
//             swap(&priorityQueue[index], &priorityQueue[small]);
//             repairDownward(small);
//             return;
//          }
//     }
//     else
//     {
//
//         if (priorityQueue[lc].cookingTime < priorityQueue[rc].cookingTime)
//             {
//               small=lc;
//             }
//         else
//             {
//               small=rc;
//             }
//         swap(&priorityQueue[index], &priorityQueue[small]);
//         repairDownward(small);
//         return;
//     }
//   }
//
//   if (lc < currentQueueSize && priorityQueue[lc].groupSize==priorityQueue[small].groupSize && priorityQueue[lc].cookingTime<priorityQueue[small].cookingTime )
//   {
//     small=lc;
//   }
//   if (lc< currentQueueSize && rc<currentQueueSize && priorityQueue[lc].groupSize < priorityQueue[index].groupSize && priorityQueue[lc].groupSize<priorityQueue[rc].groupSize )
//   {
//     small=lc;
//   }
//   if (rc < currentQueueSize && priorityQueue[rc].groupSize==priorityQueue[small].groupSize && priorityQueue[rc].cookingTime<priorityQueue[small].cookingTime )
//   {
//     small=rc;
//   }
//   if (lc< currentQueueSize && rc<currentQueueSize && priorityQueue[rc].groupSize < priorityQueue[index].groupSize && priorityQueue[rc].groupSize<priorityQueue[lc].groupSize)
//   {
//     small=rc;
//   }
//   if (small != index)
//   {
//     swap(&priorityQueue[index], &priorityQueue[small]);
//     repairDownward(small);
//   }
// }
