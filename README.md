# Programming Assignment 1 – Robot Relay Ring
# Author : Dion Chen
## Overview
- Circular Linked List implementation
- Robot Relay Ring (round-robin scheduler)
- Split a Circular Linked List problem

## What I Implemented
- [x] Append
- [x] Pop front
- [x] Rotate
- [x] Display
- [x] Split
- [x] Merge
- [x] Run turns

## How the Circular List Works
I keep the donut alive by always making tail ->next == head.
- On append, the bnew node next points to head, the old tail point to the new node, then i move tail to the new node.
- On pop_front, I move head forward and set tail -> next = head.
- On rotate, I set tail = head and head = head->next. The circle stays closed because the tail is always “behind” the head and already points back to it.
- Before clear, I break the circle once (tail->next = nullptr) so a normal while delete works.

## Why Circular Linked List Fits a Relay
A delay/round robin is basically take a turn, pass teh baton,repeat. The circle gives that for free after the last robot, we naturally come back to the first without special cases. It’s fair because everyone eventually gets the CPU time slice unless paused, and scheduling is just rotate().

## Comparison
- Head only linear list: append is O(n) (you have to walk to the end), pop_front is O(1), rotation needs extra checks.
- Head + tail (linear): append O(1), pop_front O(1), but wrap-around still needs logic.
Circular (head + tail): append O(1), pop_front O(1), and rotate is literally two pointer moves. Traversal is still O(n) (we stop when we loop back to head). For this project, circular felt the cleanest because wrap behavior is automatic.

## Split Problem
- Even (4 robots: A → B → C → D): first ring gets A, B; second gets C, D. I close each with their own tail pointing back to their head.
- Odd (5 robots: A → B → C → D → E): first ring gets A, B, C the extra node due to ceiling, second gets D, E. After split, the original list becomes empty so ownership is clear.

## Reflection
I only moved head in rotate() and forgot to move tail, which slowly broke the tail->next == head promise. Output got weird and sometimes infinite.
and the way how i fix it is I made rotate() set tail = head; head = head->next; so both pointers march together. After that, the ring stayed honest. I learned that Circles are chill if you respect the invariant. One missing pointer update ruins everything. Also, breaking the circle before clear() saves you from deleting in loops forever.
