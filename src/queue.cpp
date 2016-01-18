#include "queue.h"
#include<iostream>
#include<cstdlib>

using namespace std;

queue::queue()
{
  head = tail = NULL;
}

// Destruktor - usuwa liste z pamieci
//-----------------------------------
queue::~queue()
{
  while(head) pop();
}

// Sprawdza, czy kolejka jest pusta
//---------------------------------
bool queue::empty_q()
{
  return !head;
}

// Zwraca poczatek kolejki.
// Wartosc specjalna to -MAXINT
//-----------------------------
int queue::pull()
{
  if(head) return head->data;
  else  cout<<"Nie ma nic w kolejce";
   exit(0);
}

//zwraca adres drzewa
Node* queue::pulltree()
{
    if(head) return head->adres;
    else return NULL;
}
// Zapisuje do kolejki
//--------------------
void queue::push( Node * n)
{
  list_ * p, * root;
  p = new list_;
  p->next = NULL;
  p->key = n->key;
  p->data = n->frequency;
  p->adres=n;

  if(!head) head = tail = p;
  else if(head->data > p->data)
  {
    p->next = head;
    head    = p;
  }
  else
  {
    root = head;
    while((root->next) && (root->next->data <= p->data))
      root = root->next;
    p->next = root->next;
    root->next = p;
    if(!p->next) tail = p;
  }
}
//*****************
//zapis do kolejki dla korzeni
 void queue::pushroot(Node * n)
 {
  list_* p, * r;
  p = new list_;
  p->next = NULL;
  p->data = n->frequency;
  p->adres=n;

  if(!head) head = tail = p;
  else if(head->data > p->data)
  {
    p->next = head;
    head    = p;
  }
  else
  {
    r = head;
    while((r->next) && (r->next->data <= p->data))
      r = r->next;
    p->next = r->next;
    r->next = p;
    if(!p->next) tail = p;
  }
}


// Usuwa z kolejki
//----------------
void queue::pop()
{
  if(head)
  {
    list_ * p = head;
    head = head->next;
    if(!head) tail = NULL;
    delete p;
  }
}
