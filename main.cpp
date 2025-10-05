#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <iomanip>
#include "linkedlist.h"

using namespace std;

struct Robot {
    int id;
    string name;
    int battery;
    int drain;
    bool paused;
    Robot(int pid=0, string n="?", int b=0, int d=1)
        : id(pid), name(n), battery(b), drain(d), paused(false) {}
    friend ostream& operator<<(ostream& os, const Robot& r) {
        os << "Robot(" << r.name
           << ", Battery=" << r.battery
           << ", Drain=" << r.drain
           << (r.paused ? ", paused" : "")
           << ")";
        return os;
    }
};

static int nextId = 1;
static int score  = 0;
static int quantum = 1;
static long long ticks = 0;

// the rings
static LinkedList<Robot> ring;     // main
static LinkedList<Robot> ringA;    // split A
static LinkedList<Robot> ringB;    // split B

void addRobot(LinkedList<Robot>& rr) {
    string nm; int bat;
    cout << "Robot name: "; cin >> nm;
    cout << "Battery: ";    cin >> bat;
    if (bat < 0) bat = 0;
    int d = (quantum > 0 ? quantum : 1);
    rr.append(Robot(nextId++, nm, bat, d));
    score += 2; // +2 add robot
}

void runOneTurn(LinkedList<Robot>& rr) {
    if (rr.size() == 0) return;
    Robot& cur = rr.front(); // we know it's not empty bc we checked
    ++ticks;

    if (cur.paused) { // paused just rotates
        rr.rotate();
        return;
    }

    ++score; // +1 valid turn
    int d = (cur.drain > 0 ? cur.drain : 1);
    int use = (d <= cur.battery ? d : cur.battery);
    cur.battery -= use;

    if (cur.battery <= 0) {
        cout << cur.name << " (id=" << cur.id << ") returns to dock.\n";
        rr.pop_front();
        score += 3;// +3 removal
    } else {
        rr.rotate();
    }
}

void runNTurns(LinkedList<Robot>& rr) {
    int N; cout << "N: "; cin >> N; if (N < 0) N = 0;
    for (int i = 0; i < N && rr.size() > 0; ++i) runOneTurn(rr);
}

void pauseResume(LinkedList<Robot>& rr) {
    if (rr.size() == 0) { cout << "No robots.\n"; return; }
    int who; cout << "Robot id to toggle: "; cin >> who;

    // hacky linear scan by rotating around once
    bool found = false;
    int n = rr.size();
    for (int i = 0; i < n; ++i) {
        Robot& r = rr.front();
        if (r.id == who) { r.paused = !r.paused; found = true; break; }
        rr.rotate();
    }
    // rotate back to original head
    for (int i = 0; i < n; ++i) rr.rotate();

    if (!found) cout << "No robot with id " << who << "\n";
    else cout << "Toggled robot " << who << ".\n";
}

void showRing(LinkedList<Robot>& rr) {
    rr.display();
}

void splitRing(LinkedList<Robot>& rr) {
    rr.splitIntoTwo(ringA, ringB);
    cout << "First:  "; ringA.display();
    cout << "Second: "; ringB.display();
    score += 5; // +5 successful split
}

void mergeRings(LinkedList<Robot>& /*rr*/) {
    ringA.mergeWith(ringB);
    cout << "Merged: "; ringA.display();
}

void statsReport(LinkedList<Robot>& rr) {
    int sum = 0, cnt = 0;
    if (!rr.empty()) {
        int n = rr.size();
        for (int i = 0; i < n; ++i) {
            sum += rr.front().battery;
            ++cnt;
            rr.rotate();
        }
        // rotate back
        for (int i = 0; i < n; ++i) rr.rotate();
    }
    cout << "Robots: " << cnt
         << "\nAverage battery: " << fixed << setprecision(2)
         << (cnt ? (double)sum / cnt : 0.0)
         << "\nTicks: " << ticks << "\n";
}

int main() {
    unordered_map<int, function<void()>> cmd;
    cmd[1] = [&]{ addRobot(ring); };
    cmd[2] = [&]{ runOneTurn(ring); };
    cmd[3] = [&]{ runNTurns(ring); };
    cmd[4] = [&]{ pauseResume(ring); };
    cmd[5] = [&]{ showRing(ring); };
    cmd[6] = [&]{ splitRing(ring); };
    cmd[7] = [&]{ mergeRings(ring); };
    cmd[8] = [&]{ statsReport(ring); };

    cout << "Welcome to Robot Relay Ring (pls don’t segfault)\n";
    while (true) {
        cout << "\n=== Robot Relay Ring ===\n";
        cout << "Robots: " << ring.size()
             << "   Score: " << score
             << "   Quantum: " << quantum
             << "   Clock: " << ticks << "\n";
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
    return 0;
}
