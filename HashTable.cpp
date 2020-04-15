#include "HashTable.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void sort(wordItem* array[], int n)
{
  int max;
  for (int i=0; i<n-1; i++)
  {
    max=i;
    for (int j=i+1; j<n; j++)
    {
      if (array[j]->count > array[max]->count)
      {
        max=j;
      }
    }
    wordItem* temp=array[i];
    array[i]=array[max];
    array[max]=temp;

  }
}

void getStopWords(char *ignoreWordFileName, HashTable &stopWordsTable)
{
  string line="";
  ifstream file;
  file.open(ignoreWordFileName);
  if(file.is_open())
  {
    while(getline(file, line))
    {
      stopWordsTable.addWord(line);
    }
  }
}

bool isStopWord(string word, HashTable &stopWordsTable)
{
  if(stopWordsTable.isInTable(word))
  {
    return true;
  }
  return false;
}

HashTable::HashTable(int TableSize)
{
  hashTable=new wordItem*[TableSize];
  for (int i=0; i<TableSize; i++)
  {
    hashTable[i]=NULL;
  }
  numItems=0;
  numCollisions=0;
  hashTableSize=TableSize;

}

HashTable::~HashTable()
{
  for (int i=0; i<hashTableSize; i++)
  {
    wordItem* temp=hashTable[i];
    while(temp != NULL)
    {
      wordItem* temp2=temp;
      temp=temp->next;
      delete temp2;
    }
  }
}

void HashTable::addWord(string word)
{
  int index=getHash(word);
  if (hashTable[index]==NULL)
  {
    numItems++;
    hashTable[index]=new wordItem;
    hashTable[index]->word=word;
    hashTable[index]->count=1;
    hashTable[index]->next=NULL;
    return;
  }
  if(hashTable[index] != NULL)
  {
    numItems++;
    numCollisions++;
    wordItem* temp=hashTable[index];
    hashTable[index]=new wordItem;
    hashTable[index]->word=word;
    hashTable[index]->count=1;
    hashTable[index]->next=temp;
    return;
  }
}

bool HashTable::isInTable(string word)
{
  if(searchTable(word) != NULL)
  {
    return true;
  }
  return false;

}

void HashTable::incrementCount(string word)
{
  wordItem* temp=searchTable(word);
  if (temp != NULL)
  {
    temp->count=(temp->count)+1;
    return;
  }
  if (temp==NULL)
  {
    return;
  }

}

void HashTable::printTopN(int n)
{
  wordItem* array[numItems];
  int x=0;
  for (int i=0; i<hashTableSize; i++)
  {
    wordItem* temp=hashTable[i];
    while(temp != NULL)
    {
      array[x]=temp;
      x++;
      temp=temp->next;
    }
  }
  int m;
  m=sizeof(array)/sizeof(array[0]);
  sort(array, m);
  for (int a=0; a<n; a++)
  {
    cout << fixed;
    cout << setprecision(4);
    float x=array[a]->count;
    float y=getTotalNumWords();
    float prob=x/y;
    cout << prob << " - " << array[a]->word << endl;
  }


}

int HashTable::getNumCollisions()
{
  return numCollisions;
}

int HashTable::getNumItems()
{
  return numItems;
}

int HashTable::getTotalNumWords()
{
  int sum=0;
  for(int i=0; i<hashTableSize; i++)
  {
    wordItem* temp=hashTable[i];
    if (temp != NULL)
    {
      while (temp != NULL)
      {
        sum+=temp->count;
        temp=temp->next;
      }
    }
  }
  return sum;
}

unsigned int HashTable::getHash(string word)
{
  unsigned int hashValue = 5381;
  int length = word.length();
  for (int i=0;i<length;i++)
  {
    hashValue=((hashValue<<5)+hashValue) + word[i];
  }
  hashValue %= hashTableSize;
  return hashValue;
}

wordItem* HashTable::searchTable(string word)
{
  int i=getHash(word);
  wordItem* temp=hashTable[i];
  while (temp != NULL)
  {
    if (temp->word==word)
    {
      return temp;
    }
    temp=temp->next;
  }
  return NULL;

}
