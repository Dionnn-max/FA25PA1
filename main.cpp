#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include "linkedlist.h"

using namespace std;

// Robot type lives here, not in the container
struct Robot {
    int id;
    string name;
    int battery;
    int drain;
    bool paused;
    Robot(int pid, string n, int b, int d)
        : id(pid), name(n), battery(b), drain(d), paused(false) {}
};

static int nextId = 1;
static int score  = 0;
static int quantum = 1;

// ---------------- Menu Actions ----------------
void addRobot(LinkedList<Robot>& ring) {
    cout << "(TODO) implement append before this works.\n";
    // Example call once append is ready:
    // string name; int battery;
    // cout << "Robot name: "; cin >> name;
    // cout << "Battery: "; cin >> battery;
    // ring.append(Robot(nextId++, name, battery, quantum));
    // score += 2;
}

void runOneTurn(LinkedList<Robot>&) {
    cout << "(TODO) runOneTurn not implemented yet.\n";
}

void runNTurns(LinkedList<Robot>&) {
    cout << "(TODO) runNTurns not implemented yet.\n";
}

void pauseResume(LinkedList<Robot>&) {
    cout << "(TODO) pause/resume not implemented yet.\n";
}

void showRing(LinkedList<Robot>&) {
    cout << "(TODO) implement display before this works.\n";
    // Example: ring.display();
}

void splitRing(LinkedList<Robot>&) {
    cout << "(TODO) implement splitIntoTwo before this works.\n";
}

void mergeRings(LinkedList<Robot>&) {
    cout << "(TODO) implement mergeWith before this works.\n";
}

void statsReport(LinkedList<Robot>&) {
    cout << "(TODO) stats report not implemented yet.\n";
}

// ---------------- Main ----------------
int main() {
    LinkedList<Robot> ring;

    unordered_map<int, function<void()>> cmd;
    cmd[1] = [&]{ addRobot(ring); };
    cmd[2] = [&]{ runOneTurn(ring); };
    cmd[3] = [&]{ runNTurns(ring); };
    cmd[4] = [&]{ pauseResume(ring); };
    cmd[5] = [&]{ showRing(ring); };
    cmd[6] = [&]{ splitRing(ring); };
    cmd[7] = [&]{ mergeRings(ring); };
    cmd[8] = [&]{ statsReport(ring); };

    while (true) {
        cout << "\n=== Robot Relay Ring ===\n";
        cout << "Robots: " << ring.size() << "   Score: " << score << "   Quantum: " << quantum << "\n";
        cout << "1) Add robot\n";
        cout << "2) Run 1 turn\n";
        cout << "3) Run N turns\n";
        cout << "4) Pause/Resume robot\n";
        cout << "5) Display ring\n";
        cout << "6) Split ring into two\n";
        cout << "7) Merge rings\n";
        cout << "8) Stats report\n";
        cout << "0) Exit\n";
        cout << "Choose: ";

        int choice;
        if (!(cin >> choice)) break;
        if (choice == 0) { cout << "Goodbye!\n"; break; }

        auto it = cmd.find(choice);
        if (it != cmd.end()) it->second();
        else cout << "Invalid choice. Try again.\n";
    }
}
