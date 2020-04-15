#include "MovieTree.hpp"
#include <iostream>
using namespace std;

TreeNode* minNode(TreeNode* node)
{
  TreeNode* temp=node;
  while(temp->leftChild != NULL)
  {
    temp=temp->leftChild;
  }
  return temp;
}

void DeleteTree(TreeNode* node)
{
  if (node)
  {
    DeleteTree(node->leftChild);
    DeleteTree(node->rightChild);
    delete node;
  }
}

void DeleteLL(LLMovieNode* head)
{
  if(head == NULL)
  {
    return;
  }
  LLMovieNode* temp=head;
  LLMovieNode* NextNode;
  while(temp != NULL)
  {
    NextNode=temp->next;
    delete temp;
    temp=NextNode;
  }
  head=NULL;
}

void TraverseTree(TreeNode* node)
{
  TraverseTree(node->leftChild);
  TraverseTree(node->rightChild);
  DeleteLL(node->head);
}

TreeNode* deleteNode(TreeNode* root, char title)
{
  if (root == NULL)
  {
    return NULL;
  }
  if (title < root->titleChar)
  {
    root->leftChild=deleteNode(root->leftChild, title);
  }
  else if (title > root->titleChar)
  {
    root->rightChild=deleteNode(root->rightChild, title);
  }
  else
  {
    if (root->leftChild==NULL)
    {
      TreeNode* temp=root->rightChild;
      delete root;
      return temp;
    }
    else if(root->rightChild==NULL)
    {
      TreeNode* temp=root->leftChild;
      delete root;
      return temp;
    }
    else
    {
    TreeNode* temp=minNode(root->rightChild);
    root->titleChar=temp->titleChar;
    root->head=temp->head;
    root->rightChild=deleteNode(root->rightChild, temp->titleChar);
    }
  }
  return root;
}

TreeNode* insertNode(TreeNode* node, char character, int ranking, string title, int year, float rating)
{
  if (node==NULL)
  {
    node=new TreeNode;
    node->titleChar=character;
    LLMovieNode* movie=new LLMovieNode(ranking, title, year, rating);
    node->head=movie;
    return node;
  }
  if (character < node->titleChar)
  {
    node->leftChild=insertNode(node->leftChild, character, ranking, title, year, rating);
  }
  else if (character > node->titleChar)
  {
    node->rightChild=insertNode(node->rightChild, character, ranking, title, year, rating);
  }
  else if (character == node->titleChar)
  {
    LLMovieNode* temp=node->head;
    LLMovieNode* movie=new LLMovieNode(ranking, title, year, rating);
    if (temp->title > movie->title)
    {
      movie->next=temp;
      node->head=movie;
      return node;
    }
    while(temp->next != NULL && temp->next->title < movie->title)
    {
      temp=temp->next;
    }
    movie->next=temp->next;
    temp->next=movie;
    return node;
  }
  return node;
}



void InOrderPrint(TreeNode* node)
{
  if (node==NULL)
  {
    return;
  }
  InOrderPrint(node->leftChild);
  LLMovieNode* temp=node->head;
  if (temp != NULL)
  {
  cout << "Movies starting with letter: " <<  node->titleChar << endl;
  }
  while(temp != NULL)
  {
    cout << " >> " << temp->title << " " << temp->rating << endl;
    temp=temp->next;
  }
  InOrderPrint(node->rightChild);
}

TreeNode* searchTree(char letter, TreeNode* node)
{
  TreeNode* temp=node;
  if (temp==NULL)
  {
      return NULL;
  }
  while (temp != NULL)
  {
    if (letter < temp->titleChar)
    {
      temp=temp->leftChild;
    }
    if (letter > temp->titleChar)
    {
      temp=temp->rightChild;
    }
    if (temp==NULL)
    {
      return NULL;
    }
    if (letter == temp->titleChar)
    {
      return temp;
    }
  }
}

MovieTree::MovieTree()
{
  root=NULL;
}

MovieTree::~MovieTree()
{
  //post order recursion to delete tree
  TraverseTree(root);
  DeleteTree(root);
}

void MovieTree::printMovieInventory()
{
  InOrderPrint(root);
}

void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
  char letter=title[0];
  root=insertNode(root, letter, ranking, title, year, rating);
}

void MovieTree::deleteMovie(string title)
{

  char letter=title[0];
  TreeNode* temp=searchTree(letter, root);
    if (temp==NULL)
  {
    cout << "Movie: " << title << " not found, cannot delete." << endl;
    return;
  }
  LLMovieNode* temp2=temp->head;

  while(temp2 != NULL)
  {
    if(temp2->title==title)
    {
      temp->head=temp2->next;
      delete temp2;
      if(temp->head==NULL)
      {
        deleteNode(root, temp->titleChar);

      }
      return;
    }
    if (temp2->next->title == title && temp2->next != NULL)
    {
      LLMovieNode* ToDelete=temp2->next;
      temp2->next=temp2->next->next;
      delete ToDelete;
      return;
    }
    temp2=temp2->next;
  }
  cout << "Movie: " << title << " not found, cannot delete." << endl;
}


// TreeNode* temp=searchTree(letter, root);
// if (temp==NULL)
// {
//
// }
// LLMovieNode* temp2=temp->head;
// while(temp2 != NULL)
// {
//   if (temp2->title > title)
//   {
//     LLMovieNode* movie=new LLMovieNode;
//     movie->ranking=ranking;
//     movie->title=title;
//     movie->year=year;
//     movie->rating=rating;
//     movie->next=temp2;
//     temp->head=movie;
//     return;
//   }
  // if (temp2->next->title > title && temp2->title < title && temp2->next != NULL)
  // {
  //   LLMovieNode* movie=new LLMovieNode;
  //   movie->ranking=ranking;
  //   movie->title=title;
  //   movie->year=year;
  //   movie->rating=rating;
  //   movie->next=temp2->next;
  //   temp2->next=movie;
  //   return;
  // }
//   temp2=temp2->next;
// }
// LLMovieNode* movie=new LLMovieNode;
// movie->ranking=ranking;
// movie->title=title;
// movie->year=year;
// movie->rating=rating;
// movie->next=NULL;
// temp2=movie;
// return;
