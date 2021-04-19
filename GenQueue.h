#ifndef GEN_QUEUE_H
#define GEN_QUEUE_H
#include <iostream>
#include "linkedlist.h"

using namespace std;

template <typename T>
class GenQueue {
  public:
    GenQueue();
    ~GenQueue();

    //core functions
    void Enqueue(T d); //aka insert
    T Dequeue(); //aka remove

    //aux functions
    T peek();
    ListNode<T>* returnListNode(); //gets the front node
    bool isEmpty();
    size_t getSize();

    ListNode<T> *front; //our listnode variable
  private:
    DoublyLinkedList<T> *dl; //instance of our doubly linked list class
};

template <typename T>
GenQueue<T>::GenQueue() {
  dl = new DoublyLinkedList<T>();
  front = NULL; //setting front equal to null
}

template <typename T>
GenQueue<T>::~GenQueue() {
  delete dl;
}

template <typename T>
void GenQueue<T>::Enqueue(T d) {
  dl->InsertBack(d);
}

template <typename T>
T GenQueue<T>::Dequeue() {
  //check if empty
  if (isEmpty()) {
    throw runtime_error ("queue is empty");
  }
  return dl->RemoveFront();
}

template <typename T>
ListNode<T>* GenQueue<T>::returnListNode() {
  front = dl->ReturnListNode(); //gets the front listnode and returns it 
  return front;
}

template <typename T>
T GenQueue<T>::peek() {
  return dl->Peek();
}

template <typename T>
bool GenQueue<T>::isEmpty() {
  return dl->IsEmpty();
}

template <typename T>
size_t GenQueue<T>::getSize() {
  return dl->GetSize();
}

#endif
