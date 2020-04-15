#include "ApplicationPriority.hpp"
#include <iostream>
using namespace std;
#include <string>

//g++ -std=c++11 ApplicationPriority.cpp driver.cpp -o run

int main(int argc, char* argv[])
{
    string input;//
    int choice = 0;//menu selection input
    int priority;//
    string filename;
    int size;
    int nApplicants;
    string numMajors;               //declare variables
    string searchName;
    string collegename;
    int num;

    //get colleges information
    cout<<"What is your college's name"<<endl;
    getline(cin, collegename);
    cout<<"How many majors does "<< collegename<<" provide" <<endl;
    getline(cin, numMajors);
    string majors[stoi(numMajors)];
    cout<<"List the majors"<<endl;
    string major;
    for(int i=0; i<stoi(numMajors); i++)   //fill colleges major array
    {
        getline(cin, major);
        majors[i]=major;
    }
    cout<<endl;
    cout<<"Only showing students with "<<collegename<<"'s majors."<<endl;

    cout << "What does " <<collegename<<" look for most in a student"<< endl;
    cout << "(1) to prioritize GPA " << endl;
    cout << "(2) to prioritize SAT " << endl;
    cout << "(3) to prioritize Extracurricular Activities " << endl;

    cin>>priority;
    while(priority!=1 && priority!=2 && priority!=3)
    {
      cout << "Enter a valid input."<<endl;
            cin.clear();
            cin.ignore();
            cin >> priority;
    }

    cout << "What is the name of your applicant file(don't forget .txt)" << endl;
    cin >> filename;

    //pass in information to Application Priority class
    ApplicationPriority myApplicants(filename,majors, stoi(numMajors), collegename, priority);

    cout<<"What is your colleges capacity"<<endl;
    cin>>nApplicants;
    // {
    //   cout << "Enter a valid input."<<endl;
    //         cin.clear();
    //         cin.ignore();
    //         cin >> nApplicants;
    // }
    myApplicants.setNumberToAccept(nApplicants);   //get max size of linked list

    string addName;
    string addMajor;
    string addMajor2;
    int addTiming;
    float addSAT;
    float addGPA;
    int addXtra;
    int setprefrence=0;

    //menu options
    while(choice!=8)
    {
        cout << "============Main Menu============" << endl;
        cout << "1. Change Priority" << endl;
        cout << "2. View top applicants" << endl;
        cout << "3. Search for a Student" << endl;
        cout << "4. Accept students from pool" << endl;
        cout << "5. Manually add student from outside of pool" << endl;
        cout << "6. Delete Student from accepted list" << endl;
        cout << "7. View accepted Students" <<endl;
        cout << "8. Quit" << endl;
        cout<<"Students in queue: "<<myApplicants.getQueueSize()<<endl;
        cout<<"Accepted students: "<<myApplicants.getAcceptedSize()<<endl;
        //cout<<endl;
        cin >> choice;
        while(!cin)
        {
          cout << "Enter a valid input."<<endl;
                cin.clear();
                cin.ignore();
                cin >> choice;
        }

        switch(choice)
        {
            //to change the colleges prefrences
            case 1:
            cout << "What do you want to change your priority to?" << endl;
            cout << "(1) to prioritize GPA " << endl;
            cout << "(2) to prioritize SAT " << endl;
            cout << "(3) to prioritize Extracurricular Activities " << endl;
            cin>>priority;
            while(priority!=1 && priority!=2 && priority!=3)
            {
              cout << "Enter a valid input."<<endl;
                    cin.clear();
                    cin.ignore();
                    cin >> priority;
            }

            myApplicants.setPriority(priority);   //set new priority
            break;


            //to view top students in the queue
            case 2:

                cout<<"How many students would you like to view?"<<endl;
                cin>>num;
                myApplicants.printTopN(num);
                break;

            //to search a specific student
            case 3:

                cout<<"Enter name of student to search"<<endl;
                getline(cin, searchName);
                getline(cin, searchName);
                cout<<endl;
                myApplicants.viewStudent(searchName);
                break;

            //to accept (dequeue) students from the list
            case 4:

                cout<<"How many students do you want to add from the list"<<endl;
                cin>>nApplicants;
                myApplicants.acceptTopN(nApplicants);
                break;

            //to add in a new student to accepted list
            case 5:

                cout<<"Student name: "<<endl;
                getline(cin, addName);
                getline(cin, addName);
                cout<<"Major: "<<endl;
                cin>>addMajor2;
                cout<<"SAT score: "<<endl;
                cin>>addSAT;
                cout<<"GPA: "<<endl;
                cin>>addGPA;
                cout<<"Extracurricular Hours: "<<endl;
                cin>>addXtra;
                //pass in students information
                if(myApplicants.addSpecificStudent(addName, addGPA, addMajor2, addXtra, addSAT))
                {
                    cout<<addName<<" added to accepted list"<<endl;
                }
                break;

            //remove a student from accepted list
            case 6:
              if(myApplicants.getAcceptedSize()==0)
              {
                cout<<"No students have been accepted"<<endl;
                break;
              }
                cout<<"Enter name of student to remove from accepted list"<<endl;
                getline(cin, addName);
                getline(cin, addName);
                myApplicants.deleteSpecificStudent(addName);  //pass in students name
                break;

            //view accepted students in linked list
            case 7:
              if(myApplicants.getAcceptedSize()==0)
              {
                cout<<"No students have been excepted"<<endl;
                break;
              }
                myApplicants.printAcceptedLL();
                break;

            //quit and print accepted students to new file
            case 8:
                cout<<"Accepted list printed to seperate file, goodbye!"<<endl;
                choice=8;
                break;
            default:
                cout << "Given input is not an option" << endl << endl;
                break;
                break;


        }
    }
return 0;
}
