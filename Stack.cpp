#include "RPNCalculator.hpp"
#include <iostream>
using namespace std;

RPNCalculator::RPNCalculator()
{
  stackHead=NULL;
}

RPNCalculator::~RPNCalculator()
{
  while(stackHead != NULL)
  {
    pop();
  }
}

bool RPNCalculator::isEmpty()
{
  if (stackHead == NULL)
  {
    return true;
  }
  return false;

}

void RPNCalculator::push(float num)
{
  Operand* temp;
  temp = new Operand;
  temp->number = num;
  temp->next=stackHead;
  stackHead=temp;
}

void RPNCalculator::pop()
{
  if (isEmpty())
  {
    cout << "Stack empty, cannot pop an item." << endl;
    return;
  }
  Operand* temp=stackHead;
  stackHead=stackHead->next;
  delete temp;

}

Operand* RPNCalculator::peek()
{
  if(isEmpty())
  {
    cout << "Stack empty, cannot peek." << endl;
    return NULL;
  }
  return stackHead;
}

bool RPNCalculator::compute(string symbol)
{
  float sum;
  float product;
  float var1;
  float var2;
  if (symbol != "+" && symbol != "*")
  {
    cout << "err: invalid operation" << endl;
    return false;
  }
  if(isEmpty())
  {
    cout << "err: not enough operands" << endl;
    return false;
  }
  var1=stackHead->number;
  pop();
  if (isEmpty())
  {
    cout << "err: not enough operands" << endl;
    push(var1);
    return false;
  }
  push(var1);
  var2=stackHead->next->number;
  if (symbol=="+")
  {
    sum=var1+var2;
    pop();
    pop();
    push(sum);
    return sum;
  }
  if (symbol=="*")
  {
    product=var1*var2;
    pop();
    pop();
    push(product);
    return product;
  }

}
