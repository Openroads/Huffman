#ifndef QUEUE_H
#define QUEUE_H

#include<iostream>

using namespace std;
struct Node
{
  Node * parent, * left, * right;
  int frequency;
  int key;
};

struct list_
{
  list_ * next;
  Node *adres;
  int data;
  int key;
};

class queue
{
  private:
    list_ * head;
    list_ * tail;

  public:
    queue();                    // konstruktor
    ~queue();                   // destruktor
    bool empty_q();
    int  pull();
    Node* pulltree();
    void push(Node * n);
    void pushroot(Node * n);
    void pop();
};
#endif // QUEUE_H
