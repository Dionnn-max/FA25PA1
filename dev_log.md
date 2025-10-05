# Developer Log – Programming Assignment 1

## Entry 1
**What I tried:**  
I made rotate() only move the head pointer because I thought the tail didn’t matter for rotation.

**What broke:**  
After a few turns the list started looping weirdly — the last robot didn’t go back to the first one, and display() went infinite.

**Why it happened:**  
In a circular linked list, both head and tail have to move together, or tail->next stops pointing at head.

**Fix:**  
I changed rotate() to move both

**Proof it works:**  

tail = head;
head = head->next;

## Entry 2
What I tried:
I wrote pop_front() but forgot the single-node case.

What broke:
When the last robot’s battery hit zero, the program crashed with a dangling pointer because tail still pointed to freed memory.

Why it happened:
When there’s only one node, deleting it means both head and tail should become nullptr.

Fix:
Added a check:
if (head == tail) { delete head; head = tail = nullptr; count = 0; return; }

## Entry 3
What I tried:
I implemented splitIntoTwo() but both new lists ended up with the same nodes.

What broke:
After printing the two rings, both had the same robots, and deleting one corrupted the other.

Why it happened:
I forgot to actually close each half into its own circle. Both tails still pointed into the original ring.

Fix:
After finding the midpoint, I closed them like this:

tail1->next = head1;
tail2->next = head2;

