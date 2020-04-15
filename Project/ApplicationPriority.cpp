#include "ApplicationPriority.hpp"
#include<bits/stdc++.h>
#include <iostream>
using namespace std;
#include <fstream>
#include <string>

//got method for comparing strings regardless of upper/lower case letter in hasMajor from:
//https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/

//split functions from CSCI 1300 used to break up data in order to add to our priority queue
int split(string str, char c, string array[], int size)
{
   if (str.length() == 0) {
        return 0;
    }
   string word = "";
   int count = 0;
   str = str + c;
   for (int i = 0; i < str.length(); i++)
   {
       if (str[i] == c)
       {
           if (word.length() == 0)
               continue;
           array[count++] = word;
           word = "";
       } else {
           word = word + str[i];
       }
   }
   return count ;
}

//swaps 2 elements in the priority queue
void swap(PoolNode *a, PoolNode *b)
{
  PoolNode temp= *a;
  *a = *b;
  *b = temp;
}

ApplicationPriority::ApplicationPriority(string filename, string mj[], int numMajors, string name, int priority)
{
    //we initialize our variables
  collegeName=name;
  maxAcceptedLL = 10;
  currAcceptedLL = 0;
  currQueueSize=0;
  maxQueueSize=0;
  majorCount=numMajors;
  this->priority=priority;
  for(int i=0; i<majorCount; i++)
  {
    majors[i]=mj[i];
  }

  headLL=NULL;
  string line;
 string lnarray[10];
 ifstream applicantfile;
 int count=0;
 applicantfile.open(filename.c_str());
 //this counts for the max size of our priority queue
 while (getline(applicantfile, line))
 {
   maxQueueSize++;
 }
 // we reset the reading of the file
 applicantfile.clear();
 applicantfile.seekg(0, ios::beg);
 // here we create the priority queue with that max size
ApplicantPool=new PoolNode[maxQueueSize];
 if(applicantfile.is_open())
 {
   cout << endl << "Reading from file..." << endl << endl;
   while(getline(applicantfile, line))
   {

       split(line, ',', lnarray, 6);
       PoolNode* newstudent = new PoolNode;
       newstudent->name = lnarray[0];
       newstudent->gpa = stof(lnarray[1]);
       newstudent->SAT = stof(lnarray[2]);
       newstudent->major = lnarray[3];
       newstudent->numExtra = stoi(lnarray[4]);
       newstudent->timing = stoi(lnarray[5]);
       addtoPool(lnarray[0], stof(lnarray[1]) ,lnarray[3],stoi(lnarray[4]),stoi(lnarray[5]), stof(lnarray[2]));
       count++;
   }
 }
 else
 {
     cout << "file was not read from" << endl;

 }
}

//we deallocate our used memory and write our results to a text file
ApplicationPriority::~ApplicationPriority()
{

  string x;
  if(priority==1)
  {
    x="Highest GPA";
  }
  if(priority==2)
  {
    x="Highest SAT Score";
  }
  if(priority==3)
  {
    x="Most Extra Curricular Hours";
  }
    ofstream myfile;
    myfile.open("acceptedList.txt");
    int y=1;
    AcceptNode* curr= headLL;
    if (myfile.is_open())      //write top students to file
    {
        myfile <<"============"<<collegeName<<"'s Accepted List"<<"==========="<<endl;
        // myfile <<"Students with "<<x<<"          "<<endl<<endl;
        while(curr!=NULL)
        {
            myfile << y<< ": "<< curr->studentName<<endl;
            myfile<<"   GPA: "<<curr->gpa<<endl;
            myfile<<"   SAT: "<<curr->SAT<<endl;
            myfile<<"   Number of extra curricular hours: "<<curr->numExtra<<endl;
            myfile<<"   Major: "<<curr->major<<endl;
            myfile<<"   Order applied in: "<<curr->timing<<endl;
            y++;
            curr=curr->next;
        }
    }
    myfile.close();

    delete[] ApplicantPool;      //delete queue
    for(AcceptNode* i = headLL; i!=NULL; i = i->next)     //delete linked list
    {
        delete(i);
    }

}

//this is our "enqueue" function where we take information and add to our priority queue of student applicants
void ApplicationPriority::addtoPool(string name, float gpa, string major, int xtraC, int timing, float SATscore)
{
    if(currQueueSize==maxQueueSize)
    {
        cout << "Pool full" << endl;
        return;
    }
    if(hasMajor(major))   //only add if the college provides the students major
    {

        PoolNode temp=PoolNode();
        temp.name=name;
        temp.gpa=gpa;
        temp.major=major;
        temp.numExtra=xtraC;
        temp.timing=timing;              //store info
        temp.SAT=SATscore;
        ApplicantPool[currQueueSize]=temp;
        currQueueSize++;
        //depending on what the college chooses to prioritize we call a different repair function
            if(priority==1)
            {
                GPArepairupwards(currQueueSize-1);
            }
            if(priority==2)
            {
                SATrepairupwards(currQueueSize-1);
            }
            if(priority==3)
            {
                Curricularrepairupwards(currQueueSize-1);
            }
 }
}

//we "dequeue" off our priority queue while adding the accepted students into a linked list of students admitted into the college
void ApplicationPriority::acceptTopN(int n)
{
  for(int i=0; i<n; i++)   //for loop to dequeue n students
  {
        if (isEmpty())
        {
            cout << "Heap empty, no students to accept" << endl;
            return;
        }
        if(isFull())
        {
            cout << "Accepted student list is fill" << endl;
            return;
        }

        if (currQueueSize==1)
        {
            currAcceptedLL++;
            PoolNode temp;
            //------------------
            AcceptNode* student=new AcceptNode;
            student->studentName=ApplicantPool[0].name;
            student->gpa=ApplicantPool[0].gpa;
            student->SAT=ApplicantPool[0].SAT;
            student->major=ApplicantPool[0].major;
            student->numExtra=ApplicantPool[0].numExtra;        //store information
            student->timing=ApplicantPool[0].timing;
            student->next=NULL;
            AcceptNode* temp2;
            temp2=headLL;
            while (temp2 != NULL)
            {
                temp2=temp2->next;
            }
            temp2=new AcceptNode;
            temp2=student;
            if (headLL == NULL)
            {
              headLL=temp2;
            }
            else
            {
              AcceptNode* last=headLL;
              while (last->next != NULL)
              {
                last=last->next;         //find end of linked list
              }
              last->next=temp2;      //add student
            }
            //------------------
            ApplicantPool[0]=temp;
            currQueueSize--;
            cout<<"adding to accepted list "<<temp2->studentName<<endl;  //no need to repair

        }
        else if (currQueueSize>1)   //if more than one student in queue
        {
            currAcceptedLL++;
            PoolNode temp;
            //------------------
            // this is where we make a new node for the linked list and add it to the end
            AcceptNode* student=new AcceptNode;
            student->studentName=ApplicantPool[0].name;
            student->gpa=ApplicantPool[0].gpa;                 //store info
            student->SAT=ApplicantPool[0].SAT;
            student->major=ApplicantPool[0].major;
            student->numExtra=ApplicantPool[0].numExtra;
            student->timing=ApplicantPool[0].timing;
            student->next=NULL;
            AcceptNode* temp2;
            temp2=headLL;
            while (temp2 != NULL)
            {
                temp2=temp2->next;
            }
            temp2=new AcceptNode;
            temp2=student;
            if (headLL == NULL)
            {
              headLL=temp2;
            }
            else
            {
              AcceptNode* last=headLL;
              while (last->next != NULL)
              {
                last=last->next;
              }
              last->next=temp2;       //add student to linked list
            }
            //------------------
            cout<<"adding to accepted list "<<temp2->studentName<<endl;
            ApplicantPool[0]=ApplicantPool[currQueueSize-1];
            currQueueSize--;
            //depending on the priority we call a different repair function
            if(priority==1)
            {
                GPArepairdownwards(0);
            }
            if(priority==2)
            {
                SATrepairdownwards(0);
            }
            if(priority==3)
            {
                Curricularrepairdownwards(0);
            }
        }
    }
}

//this functions allows use to search for a specific student in the priority queue and display their information
void ApplicationPriority:: viewStudent(string name)
{
    bool found=false;
    for (int i=0; i<maxQueueSize; i++)
    {
        if (name==ApplicantPool[i].name)    //search for student in queue
        {
            found=true;
            cout << "Name: " << ApplicantPool[i].name << endl;
            cout << "GPA: " << ApplicantPool[i].gpa << endl;
            cout << "SAT Score: " << ApplicantPool[i].SAT << endl;
            cout << "Declared Major: " << ApplicantPool[i].major << endl;
            cout << "Hours of Extra Curricular Activities: " << ApplicantPool[i].numExtra << endl;
            cout << "Order of Application Received: " << ApplicantPool[i].timing << endl;
            return;
        }
    }
    if (found==false)
    {
        cout << "No student with the name " << name << " found in the applicants" << endl;
    }
}

//if there is a student that the college wants to admit that isnt from the priority queue then they can use
//this function in order to do that
bool ApplicationPriority:: addSpecificStudent(string name, float gpa, string major, int numExtra, float SAT)
{
            if(maxAcceptedLL==currAcceptedLL)
            {
              cout << "Maximum Number of Students Accepted, no more students can be admitted" << endl;
              return false;
            }
            else
            {
            AcceptNode* student=new AcceptNode;
            student->studentName=name;
            student->gpa=gpa;
            student->SAT=SAT;                                //store student information
            student->major=major;
            student->numExtra=numExtra;
            student->timing=currQueueSize++;
            student->next=NULL;
            AcceptNode* temp2;
            temp2=headLL;
            while (temp2 != NULL)
            {
                temp2=temp2->next;
            }
            temp2=new AcceptNode;
            temp2=student;
            if (headLL == NULL)      //add them as the head if the list is empty
            {
              headLL=temp2;
            }
            else
            {
              AcceptNode* last=headLL;
              while (last->next != NULL)    //add them to end of linked list
              {
                last=last->next;
              }
              last->next=temp2;
            }
              currAcceptedLL++;
              currQueueSize--;
            }

return true;
}

//this allows us to take a student off the accepted list and re add them into priority queue
bool ApplicationPriority:: deleteSpecificStudent(string name)
{

        AcceptNode* curr=headLL;
        AcceptNode* prev=headLL;
        if(curr!=NULL && curr->studentName==name)
        {
           //add them back in queue and delete from linked list if student is head
            addtoPool(curr->studentName, curr->gpa, curr->major, curr->numExtra, curr->timing, curr->SAT);
           cout<<curr->studentName<<" removed from accepted list"<<endl;
            headLL=curr->next;
            delete curr;
            currAcceptedLL--;
            return true;
        }
        while(curr!= NULL && curr->studentName!=name)
        {
            prev=curr;
            curr=curr->next;   //find student
        }
        if(curr==NULL)
        {
            cout<<"Student not found"<<endl;
            return false;
        }
        else
        {
            //add them back in queue and delete from accepted list
            addtoPool(curr->studentName, curr->gpa, curr->major, curr->numExtra, curr->timing, curr->SAT);
            prev->next=curr->next;
            cout<<curr->studentName<<" removed from accepted list"<<endl;
            delete curr;
            currAcceptedLL--;
            return true;
        }

}

int ApplicationPriority:: getAcceptedSize()
{
  return currAcceptedLL;
}

//this prints the list of students currently on the accepted linked list
void ApplicationPriority::printAcceptedLL()
{
    cout << "Currently accepted students..." << endl;
    for(AcceptNode* tmp = headLL; tmp!=NULL; tmp = tmp->next)
    {
        cout << tmp->studentName << endl;
    }
}


// Repair Functions
//for all of our repair functions depending on what the college prioritizes it will prioritize that and if
//there is a tie then the student that first submitted their application is prioritized
//-----------------------------------------------------------------------------

void ApplicationPriority:: GPArepairupwards(int _index)
{
    //swap is parent has lower gpa than given index or the same gpa but parent applied after
    while ((_index!= 0 && ApplicantPool[parent(_index)].gpa < ApplicantPool[_index].gpa)
        || (ApplicantPool[parent(_index)].timing > ApplicantPool[_index].timing
        && ApplicantPool[parent(_index)].gpa ==  ApplicantPool[_index].gpa))
      {
        swap(&ApplicantPool[_index], &ApplicantPool[parent(_index)]);
        _index = parent(_index);  //update index
      }
}

//same as above but with numExtra values
void ApplicationPriority:: Curricularrepairupwards(int _index)
{
    while ((_index!= 0 && ApplicantPool[parent(_index)].numExtra < ApplicantPool[_index].numExtra)
        || (ApplicantPool[parent(_index)].timing > ApplicantPool[_index].timing
        && ApplicantPool[parent(_index)].numExtra ==  ApplicantPool[_index].numExtra))
      {
        swap(&ApplicantPool[_index], &ApplicantPool[parent(_index)]);
        _index = parent(_index);
      }
}

//same as above but with SAT values
void ApplicationPriority:: SATrepairupwards(int _index)
{
    while (( _index!= 0 && ApplicantPool[parent(_index)].SAT < ApplicantPool[_index].SAT)
        || ( _index!=0 && ApplicantPool[parent(_index)].timing > ApplicantPool[_index].timing
        && ApplicantPool[parent(_index)].SAT ==  ApplicantPool[_index].SAT))
      {
        swap(&ApplicantPool[_index], &ApplicantPool[parent(_index)]);
        _index = parent(_index);
      }
}


//when a student is dequeued and gpa is priority
void ApplicationPriority:: GPArepairdownwards(int i)
{

  int l = leftChild(i);       //find left and right child indexs
  int r = rightChild(i);
  int smallest = i;


  //if left child has higher gpa than "smallest" index or the same gpa and left child applied first
  if((l<currQueueSize && ApplicantPool[l].gpa > ApplicantPool[i].gpa)
    || (l <currQueueSize && ApplicantPool[l].gpa == ApplicantPool[i].gpa &&
        ApplicantPool[l].timing < ApplicantPool[i].timing))
  {
    smallest=l;    //update smallest variable to left child index
  }

  //if right child has higher gpa tha "smallest" index or the same gpa and right child applied first
  if((r < currQueueSize && ApplicantPool[r].gpa > ApplicantPool[smallest].gpa )
    || (r < currQueueSize && ApplicantPool[r].gpa == ApplicantPool[smallest].gpa &&
       ApplicantPool[r].timing < ApplicantPool[smallest].timing))
  {
    smallest = r;   //update smallest variable to right child index
  }

  if( smallest!= i )
  {
    swap(&ApplicantPool[i], &ApplicantPool[smallest]);  //call swap function
    GPArepairdownwards(smallest);  //call recursivly
  }
}

//when a student is dequeued and SAT is priority
//same as GPA but using SAT values
void ApplicationPriority:: SATrepairdownwards(int i)
{
  int l = leftChild(i);
  int r = rightChild(i);
  int smallest = i;

  if( ((l<currQueueSize) && (ApplicantPool[l].SAT > ApplicantPool[i].SAT))
    || (l <currQueueSize && ApplicantPool[l].SAT == ApplicantPool[i].SAT &&
        ApplicantPool[l].timing < ApplicantPool[i].timing) )
  {
    smallest=l;
  }

  if( (r < currQueueSize && ApplicantPool[r].SAT > ApplicantPool[smallest].SAT )
    || (r < currQueueSize && ApplicantPool[r].SAT == ApplicantPool[smallest].SAT &&
       ApplicantPool[r].timing < ApplicantPool[smallest].timing) )
  {
    smallest = r;
  }

  if(smallest!= i )
  {
    swap(ApplicantPool[i], ApplicantPool[smallest]);
    SATrepairdownwards(smallest);
  }
}

//when a student is dequeued and curricular is priority
//same as GPArepair but using numExtra values
void ApplicationPriority:: Curricularrepairdownwards(int i)
{
int l = leftChild(i);
  int r = rightChild(i);
  int smallest = i;

  if((l<currQueueSize && ApplicantPool[l].numExtra > ApplicantPool[i].numExtra)
    || ((l <currQueueSize && ApplicantPool[l].numExtra == ApplicantPool[i].numExtra) &&
        (ApplicantPool[l].timing < ApplicantPool[i].timing)))
  {
    smallest=l;
  }

  if( (r < currQueueSize && ApplicantPool[r].numExtra > ApplicantPool[smallest].numExtra)
    || ( (r < currQueueSize && ApplicantPool[r].numExtra == ApplicantPool[smallest].numExtra) &&
       (ApplicantPool[r].timing < ApplicantPool[smallest].timing)) )
  {
    smallest = r;
  }

  if(smallest!= i )
  {
    swap(&ApplicantPool[i], &ApplicantPool[smallest]);
    Curricularrepairdownwards(smallest);
  }
}


//------------------------------------------------------------------------------

// Index Functions
//==============================================================================
int ApplicationPriority:: parent(int index)
{
    return ((index-1)/2);
}

int ApplicationPriority:: leftChild(int index)
{
    return ((2*index) + 1);
}

int ApplicationPriority:: rightChild(int index)
{
    return ((2*index) + 2);
}
//==============================================================================


bool ApplicationPriority:: hasMajor(string maj)    //return true if college provides students major
{
    string maj1 = maj;
    transform(maj1.begin(), maj1.end(), maj1.begin(), ::tolower);
    string maj2;
    for(int j=0; j<majorCount; j++)
    {
        maj2 = majors[j];
        transform(maj2.begin(), maj2.end(), maj2.begin(), ::tolower);
        if(maj1==maj2)    //compare students major to colleges major array
        {
          return true;
        }
    }
  return false;
}

//return true if queue is empty
bool ApplicationPriority:: isEmpty()
{
    if(currQueueSize==0)
    {
        return true;
    }
    return false;
}


//return true is link list (accepted students) has reached capacity
bool ApplicationPriority:: isFull()
{
    if(currAcceptedLL==maxAcceptedLL)
    {
        return true;
    }
    return false;
}

//changes the priority and fixes the priority queue
void ApplicationPriority:: setPriority(int num)
{
  priority = num;    //set new priority
  int x=currQueueSize;
  PoolNode temparr[currQueueSize];   //create a temp array to store students
  for(int i=0; i<x; i++)
  {
    temparr[i]=peek();   //store students in array and dequeue them
    dequeue();
  }
  for(int i=0; i<x; i++)   //add back in all the students. Queue will repair itself based on new priority
  {
    addtoPool(temparr[i].name,temparr[i].gpa, temparr[i].major, temparr[i].numExtra, temparr[i].timing,temparr[i].SAT);
  }
}

//let the college set how many students to accept (max size of linked list)
void ApplicationPriority:: setNumberToAccept(int num)
{
    this->maxAcceptedLL=num;
}

//return first student in queue
PoolNode ApplicationPriority:: peek()
{
   return ApplicantPool[0];

}

//remove first student in queue
void ApplicationPriority:: dequeue()
{
  currQueueSize--;     //decrease queue size
  ApplicantPool[0]=ApplicantPool[currQueueSize];   //replace first student with last student

  //repair accordingly
  if(priority==1)
  {
      GPArepairdownwards(0);
  }
  if(priority==2)
  {
      SATrepairdownwards(0);
  }
  if(priority==3)
  {
      Curricularrepairdownwards(0);
  }
}


//return number of students currently in the queue
int ApplicationPriority:: getQueueSize()
{
  return currQueueSize;
}

//function to print top students in the queue
void ApplicationPriority:: printTopN(int n)
{
 int size=currQueueSize;
 string x;
 if(priority==1)
 {
   x="Highest GPA";
 }
 if(priority==2)
 {
   x="Highest SAT Score";
 }
 if(priority==3)
 {
   x="Most Extra Curricular hours";
 }
  PoolNode temparr[n];
  if(n==0)
    {
       return;
    }
  if(size<n)     //if they want to see more students then are in the queue
  {
    cout<<"There are not "<<n<<" students in the queue"<<endl;
    return;
  }
  cout<<endl;
  cout<<"Students with "<<x<<endl;
  for(int i=0; i<n; i++)
  {
    PoolNode temp= peek();     //get the top student from the queue
    cout << "Name: " << temp.name << endl;
    cout << "GPA: " << temp.gpa << endl;
    cout << "SAT Score: " << temp.SAT << endl;                     //print out their information
    cout << "Declared Major: " << temp.major << endl;
    cout << "Hours of Extra Curricular Activities: " << temp.numExtra << endl;
    cout << "Order of Application Received: " << temp.timing << endl<<endl;
    temparr[i]=temp;    //store the student in the array
    dequeue();          //dequeue the student
  }
  for(int i=0; i<n; i++)   //add back in all the students dequeues in the array
  {
    addtoPool(temparr[i].name,temparr[i].gpa, temparr[i].major, temparr[i].numExtra, temparr[i].timing,temparr[i].SAT);
  }
}
