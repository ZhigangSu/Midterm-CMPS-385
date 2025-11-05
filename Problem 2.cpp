#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

const int MAX_QUEUE = 100;

struct Taxi {
    int id;
    string driver;
    string model;
    string plate;
};

struct TaxiQueue {
    Taxi data[MAX_QUEUE];
    int frontIdx;
    int rearIdx;
    int count;
};

void initQueue(TaxiQueue& q) {
    q.frontIdx = 0;
    q.rearIdx = -1;
    q.count = 0;
}

bool isEmpty(const TaxiQueue& q) {
    return q.count == 0;
}

bool isFull(const TaxiQueue& q) {
    return q.count == MAX_QUEUE;
}

bool enqueue(TaxiQueue& q, const Taxi& t) {
    if (isFull(q)) return false;
    q.rearIdx = (q.rearIdx + 1) % MAX_QUEUE;
    q.data[q.rearIdx] = t;
    q.count++;
    return true;
}

bool dequeue(TaxiQueue& q, Taxi& out) {
    if (isEmpty(q)) return false;
    out = q.data[q.frontIdx];
    q.frontIdx = (q.frontIdx + 1) % MAX_QUEUE;
    q.count--;
    return true;
}

bool front(const TaxiQueue& q, Taxi& out) {
    if (isEmpty(q)) return false;
    out = q.data[q.frontIdx];
    return true;
}

bool rear(const TaxiQueue& q, Taxi& out) {
    if (isEmpty(q)) return false;
    out = q.data[q.rearIdx];
    return true;
}

void printHeader() {
    cout << "****** Welcome to Airport Taxi Queue System ******\n";
    cout << "Please choose one of the following operations:\n";
    cout << "1. Add Taxi to Queue\n";
    cout << "2. View Waiting Taxis\n";
    cout << "3. Dispatch Next Taxi\n";
    cout << "4. View Queue Summary\n";
    cout << "5. Exit\n";
}

void viewQueue(const TaxiQueue& q) {
    cout << "========= WAITING TAXIS (Front to Rear) =========\n";
    cout << left << setw(7) << "ID"
        << left << setw(15) << "Driver"
        << left << setw(16) << "Model"
        << left << setw(12) << "Plate" << "\n";
    cout << "---------------------------------------------\n";
    if (isEmpty(q)) return;

    int idx = q.frontIdx;
    for (int i = 0; i < q.count; ++i) {
        const Taxi& t = q.data[idx];
        cout << left << setw(7) << t.id
            << left << setw(15) << t.driver
            << left << setw(16) << t.model
            << left << setw(12) << t.plate << "\n";
        idx = (idx + 1) % MAX_QUEUE;
    }
}

void saveToFile(const TaxiQueue& q, const string& filename) {
    ofstream fout(filename.c_str());
    fout << "ID,Driver,Model,Plate\n";
    int idx = q.frontIdx;
    for (int i = 0; i < q.count; ++i) {
        const Taxi& t = q.data[idx];
        fout << t.id << ","
            << t.driver << ","
            << t.model << ","
            << t.plate << "\n";
        idx = (idx + 1) % MAX_QUEUE;
    }
    fout.close();
}

int main() {
    TaxiQueue q;
    initQueue(q);

    int choice;
    do {
        printHeader();
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            continue;
        }
        cin.ignore(10000, '\n');

        if (choice == 1) {
            if (isFull(q)) {
                cout << "Queue is full. No more taxis can be added at this time.\n";
            }
            else {
                Taxi t;
                cout << "Enter Taxi ID: ";
                cin >> t.id; cin.ignore(10000, '\n');
                cout << "Enter Driver Name: ";
                getline(cin, t.driver);
                cout << "Enter Car Model: ";
                getline(cin, t.model);
                cout << "Enter License Plate: ";
                getline(cin, t.plate);

                if (enqueue(q, t)) {
                    cout << "Taxi added to queue!\n";
                }
                else {
                    cout << "Failed to add taxi.\n";
                }
            }
        }
        else if (choice == 2) {
            if (isEmpty(q)) {
                cout << "No taxis waiting.\n";
            }
            else {
                viewQueue(q);
            }
        }
        else if (choice == 3) {
            if (isEmpty(q)) {
                cout << "No taxis available for dispatch.\n";
            }
            else {
                Taxi t;
                dequeue(q, t);
                cout << "Taxi dispatched:\n";
                cout << "ID: " << t.id
                    << ", Driver: " << t.driver
                    << ", Car: " << t.model
                    << ", Plate: " << t.plate << "\n";
            }
        }
        else if (choice == 4) {
            cout << "========== QUEUE SUMMARY ==========\n";
            cout << "Total Taxis Waiting: " << q.count << "\n";
            Taxi f, r;
            if (front(q, f)) {
                cout << "Front Taxi: ID " << f.id << " - " << f.driver << "\n";
            }
            else {
                cout << "Front Taxi: (none)\n";
            }
            if (rear(q, r)) {
                cout << "Rear  Taxi: ID " << r.id << " - " << r.driver << "\n";
            }
            else {
                cout << "Rear  Taxi: (none)\n";
            }
            cout << "===================================\n";
        }
        else if (choice == 5) {
            saveToFile(q, "taxis.txt");
            cout << "Taxi queue saved to taxis.txt. Have a safe dispatch!\n";
        }
        else {
            cout << "Invalid option.\n";
        }

        if (choice != 5) cout << "\n";
    } while (choice != 5);

    return 0;
}
