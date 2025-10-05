#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node(const T& val) : data(val), next(nullptr) {}
};

// circular list that tries its best
template<typename T>
class LinkedList {
private:
    Node<T>* head; // first guy
    Node<T>* tail; // last guy (points back to first guy)
    int count;     // how many guys total

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    bool empty() const { return head == nullptr; }
    int  size()  const { return count; }

    // add to the back, keep the donut closed
    void append(const T& value) {
        Node<T>* n = new Node<T>(value);
        if (!head) {
            head = tail = n;
            n->next = head; // single node donut
        } else {
            n->next = head; // new tail points to head
            tail->next = n; // old tail points to new tail
            tail = n; // this is the tail now
        }
        ++count; // invariant stays true: tail->next should be head
    }

    // head's data but if it's empty you poked the bear
    T& front() {
        if (!head) throw runtime_error("front() on empty list (my bad)");
        return head->data;
    }

    // overwrite whatever is at the front
    void set_front(const T& value) {
        if (head) head->data = value;
    }

    // yeet the first node, but safely
    void pop_front() {
        if (!head) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            count = 0;
            return;
        }
        Node<T>* old = head;
        head = head->next; // move forward
        tail->next = head; // close the loop
        delete old;
        --count;
    }

    // pass the baton: both head and tail move one step
    void rotate() {
        if (!head || head == tail) return; // 0 or 1 node, nothing moves
        tail = head;
        head = head->next;
        // circle still closed because tail->next already points to head
    }

    // delete everything
    void clear() {
        if (!head) return;
        tail->next = nullptr; // make it a normal linked list first
        Node<T>* cur = head;
        while (cur) {
            Node<T>* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        count = 0;
    }

    // show exactly one lap
    void display() const {
        if (!head) { cout << "[] (empty)\n"; return; }
        cout << "[";
        const Node<T>* cur = head;
        do {
            cout << cur->data;
            cur = cur->next;
            if (cur != head) cout << " -> ";
        } while (cur != head);
        cout << "] (circular)\n";
    }

    // split this ring into two rings: first gets ceil(n/2), second gets floor(n/2)
    void splitIntoTwo(LinkedList<T>& first, LinkedList<T>& second) {
        first.clear(); second.clear();
        if (!head) return;

        if (count == 1) { // trivial
            first.append(head->data);
            clear();
            return;
        }

        // fast/slow pointer classic move to find the mid for a circle
        Node<T>* slow = head;
        Node<T>* fast = head;
        while (fast->next != head && fast->next->next != head) {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node<T>* head1 = head;
        Node<T>* head2 = slow->next;
        Node<T>* tail1 = slow;
        Node<T>* tail2 = (fast->next == head ? fast : fast->next);

        // close both donuts
        tail1->next = head1;
        tail2->next = head2;

        // hand over pointers+sizes
        first.head = head1; first.tail = tail1; first.count = (count + 1) / 2;
        second.head = head2; second.tail = tail2; second.count = count / 2;

        // original list becomes empty
        head = tail = nullptr;
        count = 0;
    }

    // glue another ring onto this ring in O(1). other becomes empty afterwards.
    void mergeWith(LinkedList<T>& other) {
        if (&other == this || other.empty()) return;
        if (empty()) {
            head = other.head; tail = other.tail; count = other.count;
        } else {
            Node<T>* a_head = head;
            Node<T>* a_tail = tail;
            Node<T>* b_head = other.head;
            Node<T>* b_tail = other.tail;
            a_tail->next = b_head;
            b_tail->next = a_head;
            tail = b_tail;
            count += other.count;
        }
        other.head = other.tail = nullptr;
        other.count = 0;
    }
};

#endif
