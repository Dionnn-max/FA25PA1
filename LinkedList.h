#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

// Node for Circular Linked List
template<typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(const T& val) : data(val), next(nullptr) {}
};

// Circular Linked List
template<typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    bool empty() const { return head == nullptr; }
    int size() const { return count; }

    // TODO: Append new node at tail (maintain circular link)
    void append(const T& value);

    // TODO: Return reference to head’s data
    T& front();

    // TODO: Update head’s data
    void set_front(const T& value);

    // TODO: Remove head node safely
    void pop_front();

    // TODO: Advance head and tail one step (rotate)
    void rotate();

    // TODO: Clear all nodes
    void clear();

    // TODO: Display list once around (stop at head again)
    void display() const;

    // TODO: Split into two circular lists
    void splitIntoTwo(LinkedList<T>& first, LinkedList<T>& second);

    // TODO: Merge another circular list into this one
    void mergeWith(LinkedList<T>& other);
};

#endif
