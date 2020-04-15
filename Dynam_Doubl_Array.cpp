#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct wordItem
{
  string word;
  int count=0;
};

void getStopWords(const char *ignoreWordFileName, string ignoreWords[])
{
  ifstream file;
  file.open(ignoreWordFileName);
  if (file.is_open())
  {
    for (int i=0; i<50; i++)
    {
      string line="";
      getline(file, line);
      if (line.length()>0)
      {
        ignoreWords[i]=line;
      }
    }

  }
  else
  {
    cout << "Failed to open " << ignoreWordFileName << endl;
  }
}

bool isStopWord(string word, string ignoreWords[])
{
  for (int i=0; i<50; i++)
  {
    if (word==ignoreWords[i])
    {
      return true;
    }
  }
  return false;
}

int getTotalNumberNonStopWords (wordItem uniqueWords[], int length)
{
  int sum=0;
  for (int i=0; i<length; i++)
  {
    sum+=uniqueWords[i].count;
  }
    return sum;
}

void arraySort(wordItem uniqueWords[], int length)
{
  for (int i=0; i<length; i++)
  {
    wordItem MostSoFar=uniqueWords[i];
    for (int j=i+1; j<=length; j++)
    {
      if (MostSoFar.count<uniqueWords[j].count)
      {
        MostSoFar=uniqueWords[j];
        wordItem temp=uniqueWords[i];
        uniqueWords[i]=uniqueWords[j];
        uniqueWords[j]=temp;
      }
    }
  }
}

void printTopN (wordItem uniqueWords[], int TopN, int totalNumWords)
{
  cout << "Probabilities of top " << TopN << " most frequent words" <<endl;
  cout << "---------------------------------------" << endl;
  for (int i=0; i<TopN; i++)
  {
    float num=uniqueWords[i].count;
    float probability=num/totalNumWords;
    cout << fixed;
    cout << setprecision(4);
    cout << probability << " - " << uniqueWords[i].word << endl;
  }
}

 void resize(wordItem **arrayPtr, int *capacity)
 {
 	int newCapacity = *capacity * 2;
   // cout<<"Resizing from "<<*capacity<<" to "<<newCapacity<<endl;
 	wordItem *newArray = new wordItem[newCapacity];
	for (int i=0; i<*capacity; i++)
 	{
 		newArray[i]=(*arrayPtr)[i];
 	}
 	delete [] *arrayPtr;
 	*arrayPtr = newArray;
 	*capacity = newCapacity;
 }

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" <<endl;

  }
  string wordsToIgnore[50];
  int numWords=0;
  int entries=0;
  int numberOfDoubles=0;
  int wordCapacity=100;
  wordItem *arrayOfWords;
  arrayOfWords=new wordItem[wordCapacity];
  bool found=false;
  bool foundIgnoreWord=false;
  string line="";
  getStopWords(argv[3],wordsToIgnore);
  ifstream file;
  file.open(argv[2]);
  if (file.is_open())
  {
    // while(getline(file,line,' '))
    // {
    //   found=false;
    //   for (int i=0; i<50; i++)
    //   {
    //     if (line==wordsToIgnore[i])
    //     {
    //       found=true;
    //     }
    //   }
    //   if (found==false && line!="" && line.length()>0)
    //   {
    //     numWords++;
    //   }
    // }
    // file.clear();
    // file.seekg(0, ios::beg);
    while (getline(file,line,' '))
    {
      found=false;
      foundIgnoreWord=false;
      //checks if the word is already in the wordItem array
      //I WASNT IGNORING THE WORDS
      for (int j=0; j<50; j++)
      {
        if (line==wordsToIgnore[j])
        {
          foundIgnoreWord=true;
        }
      }
      for (int i=0; i<wordCapacity; i++)
      {
        if (line == arrayOfWords[i].word && foundIgnoreWord==false)
        {
          found=true;
          arrayOfWords[i].count++;
        }
        if(entries == wordCapacity)
        {
          numberOfDoubles++;
          resize(&arrayOfWords, &wordCapacity);
        }
      }
      if (found==false && foundIgnoreWord==false)
      {
        arrayOfWords[entries].word=line;
        arrayOfWords[entries].count=1;
        entries++;
      }

    }
  }
  arraySort(arrayOfWords, entries);
  cout << "Array doubled: " << numberOfDoubles << endl;
  cout << "#" << endl;
  cout << "Unique non-common words: " << entries << endl;
  cout << "#" <<endl;
  cout << "Total non-common words: " << getTotalNumberNonStopWords(arrayOfWords,entries) <<endl;
  cout << "#" <<endl;
  printTopN(arrayOfWords, stoi(argv[1]), getTotalNumberNonStopWords(arrayOfWords,entries));

//testing the functions below to see if they work
  // getStopWords(argv[1], wordsToIgnore);
  // cout << isStopWord("me",wordsToIgnore);

}
