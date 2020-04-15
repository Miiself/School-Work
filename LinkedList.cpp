/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
head=NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
if (head==NULL)
{
  return true;
}
else
{
  return false;
}
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
Country* n;
Country* temp;
temp=head;
if (previous==NULL)
{
  cout << "adding: " << countryName << " (HEAD)" << endl;
  n=new Country;
  n->name=countryName;
  head=n;
  n->next=temp;
}
else
{
  cout << "adding: " << countryName << " (prev: " <<previous->name << ")" << endl;
  n=new Country;
  temp=previous->next;
  n->name=countryName;
  previous->next=n;
  n->next=temp;
}

}


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName)
{
  Country* temp;
  Country* ToDelete;
  temp=head;
  bool found=false;
  if (temp->name==countryName)
  {
    head=temp->next;
    ToDelete=temp;
    found=true;

  }
  while (found == false && temp != NULL)
  {
    // temp=temp->next;
    if (temp->next != NULL)
    {
      if (temp->next->name == countryName)
      {
        found=true;
        ToDelete=temp->next;
        temp->next=temp->next->next;
      }
    }
    if (found==false)
    {
      temp=temp->next;
    }
  }
  if (found == false)
  {
    cout << "Country does not exist." << endl;
    return;
  }
  if (ToDelete->name == countryName)
  {
    delete ToDelete;
  }

}


/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
  deleteEntireNetwork();
  insertCountry(NULL, "United States");
  insertCountry(head, "Canada");
  insertCountry(head->next, "Brazil");
  insertCountry(head->next->next, "India");
  insertCountry(head->next->next->next, "China");
  insertCountry(head->next->next->next->next, "Australia");
}


/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
  Country* temp;
  temp=head;
  while (temp != NULL)
  {
    if (temp->name == countryName)
    {
      return temp;
    }
    temp=temp->next;
  }
  return NULL;

}


/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork()
{
  Country* temp;
  if (head != NULL)
  {
  while(head!=NULL)
  {
  temp=head;
  head=temp->next;
  cout << "deleting: " << temp->name << endl;
  delete temp;
  }
  cout << "Deleted network" << endl;
  }

}


/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
  Country* temp;
  temp=head;
  bool found=false;
  if (head != NULL)
  {
    while (found==false)
    {
      temp->message=message;
      temp->numberMessages++;
      cout << temp->name << " [# messages received: " << temp->numberMessages << "] received: " << temp->message << endl;
        if (temp->name == receiver)
        {
          found=true;
        }
        temp=temp->next;
    }
  }
  else
  {
    cout << "Empty list" << endl;
    return;
  }

}


/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
  cout << "== CURRENT PATH ==" <<endl;

  if (head==NULL)
  {
    cout << "nothing in path" <<endl;
  }

  Country* temp;
  temp=head;
  if (temp != NULL)
  {
    while (temp != NULL)
    {
      cout << temp->name << " -> " ;
      temp=temp->next;
    }
    cout << "NULL" <<endl;
  }
  cout << "===" <<endl;
  cout << endl;

}


/*
 * Purpose: reverse the entire network t
 * @param ptr head of list
 */
void CountryNetwork::reverseEntireNetwork()
{
  Country* prev=NULL;
  Country* Next;
  Country* temp;
  temp=head;
  while (temp != NULL)
  {
    Next=temp->next;
    temp->next=prev;
    prev=temp;
    temp=Next;
  }
  head=prev;

}
