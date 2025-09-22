# Understanding the Output of Robot Relay Ring

## Starting the Program
When you first run the program, you’ll see the main menu:

```
=== Robot Relay Ring ===
Clock: 0
Robots: 0
Score: 0
1) Add robot
2) Run 1 turn
3) Run N turns
4) Pause/Resume robot by id
5) Display ring
6) Split ring into two smaller rings
7) Merge rings
8) Stats report
0) Exit
Choose:
```

- **Clock** shows how many turns have passed in the game.  
- **Robots** shows how many robots are currently in the ring.  
- **Score** shows how many points you have earned for correct actions.  

---

## Adding Robots
If you choose option **1**, you add a robot:

```
Choose: 1
Robot name: Alpha
Battery: 5
```

Now the menu updates:

```
Clock: 0
Robots: 1
Score: 2
```

Robots went up to 1, and Score went up to 2 because adding a robot gives you points.  

---

## Displaying the Ring
If you choose option **5 (Display):**

```
Choose: 5
[Robot(Alpha, Battery=5)] (circular)
```

This shows the robot in the circle.  

If you add another robot:

```
Choose: 1
Robot name: Beta
Battery: 3
Choose: 5
[Robot(Alpha, Battery=5) -> Robot(Beta, Battery=3)] (circular)
```

Now you can see Alpha pointing to Beta, and Beta pointing back to Alpha, which is why it is circular.  

---

## Running Turns
When you choose option **2 (Run 1 turn):**

```
Choose: 2
Alpha completed a task. Battery now 4.
```

The Clock increases by 1. After Alpha’s turn, the ring rotates so Beta is now at the front.

```
Clock: 1
Robots: 2
Score: 5
```

If Beta’s battery runs down to 0:

```
Choose: 2
Beta completed a task. Battery now 0.
Beta returned to dock.
```

Now Robots goes down by 1, and Score goes up by 3 for a correct removal.  

---

## Splitting the Ring
If you add several robots and then choose option **6 (Split):**

```
Choose: 6
First half:
[Robot(Alpha, Battery=3) -> Robot(Beta, Battery=2)] (circular)

Second half:
[Robot(Gamma, Battery=4) -> Robot(Delta, Battery=5)] (circular)
```

The robots are divided into two smaller circles. Both halves are still circular.  

---

## Stats Report
When you choose option **8 (Stats report):**

```
Choose: 8
Robots remaining: 3
Average battery: 4
Total turns taken: 7
```

This gives you a snapshot of the system at that point in time.  

---

## Exiting
When you are finished, choose option **0**:

```
Choose: 0
Goodbye!
```

That ends the program cleanly.  

---

## Wrap Up
- **Clock** tells you how far the simulation has gone.  
- **Robots** tells you how many are still active in the ring.  
- **Score** rewards you for correct operations.  
- **Display** shows you the actual circle of robots and their current batteries.  
- Each option changes these numbers in a predictable way, so you can always double-check your work.  
