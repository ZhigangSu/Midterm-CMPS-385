// WarehouseStack.cpp
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

const int MAX_STACK = 100;

struct Box {
    int id;
    string item;
    double weight;
    string dest;
};

struct BoxStack {
    Box data[MAX_STACK];
    int top;
};

void initStack(BoxStack& s) {
    s.top = -1;
}

bool isEmpty(const BoxStack& s) {
    return s.top == -1;
}

bool isFull(const BoxStack& s) {
    return s.top == MAX_STACK - 1;
}

bool push(BoxStack& s, const Box& b) {
    if (isFull(s)) return false;
    s.data[++s.top] = b;
    return true;
}

bool pop(BoxStack& s, Box& out) {
    if (isEmpty(s)) return false;
    out = s.data[s.top--];
    return true;
}

bool peek(const BoxStack& s, Box& out) {
    if (isEmpty(s)) return false;
    out = s.data[s.top];
    return true;
}

int size(const BoxStack& s) {
    return s.top + 1;
}

double totalWeight(const BoxStack& s) {
    double sum = 0.0;
    for (int i = 0; i <= s.top; ++i) sum += s.data[i].weight;
    return sum;
}

void printHeader() {
    cout << "****** Welcome to Warehouse Inventory Stack Tracker ******\n";
    cout << "Please choose one of the following operations:\n";
    cout << "1. Add Box to Stack\n";
    cout << "2. View Current Stack\n";
    cout << "3. Remove Top Box (Dispatch)\n";
    cout << "4. View Inventory Summary\n";
    cout << "5. Exit\n";
}

void viewStack(const BoxStack& s) {
    cout << "========= STACKED BOXES (Top to Bottom) =========\n";
    cout << left << setw(10) << "Box ID"
        << left << setw(13) << "Item"
        << left << setw(12) << "Weight(kg)"
        << left << setw(15) << "Destination" << "\n";
    cout << "-----------------------------------------------\n";
    cout << fixed << showpoint << setprecision(2);
    for (int i = s.top; i >= 0; --i) {
        cout << left << setw(10) << s.data[i].id
            << left << setw(13) << s.data[i].item
            << left << setw(12) << s.data[i].weight
            << left << setw(15) << s.data[i].dest << "\n";
    }
}

void saveToFile(const BoxStack& s, const string& filename) {
    ofstream fout(filename.c_str());
    fout << "ID,Item,Weight,Destination\n";
    for (int i = s.top; i >= 0; --i) {
        fout << s.data[i].id << ","
            << s.data[i].item << ","
            << s.data[i].weight << ","
            << s.data[i].dest << "\n";
    }
    fout.close();
}

int main() {
    BoxStack s;
    initStack(s);

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
            if (isFull(s)) {
                cout << "Stack is full. Cannot add more boxes.\n";
            }
            else {
                Box b;
                cout << "Enter Box ID: ";
                cin >> b.id; cin.ignore(10000, '\n');
                cout << "Enter Item Name: ";
                getline(cin, b.item);
                cout << "Enter Weight (kg): ";
                cin >> b.weight; cin.ignore(10000, '\n');
                cout << "Enter Destination: ";
                getline(cin, b.dest);

                if (push(s, b)) {
                    cout << "Box added to stack!\n";
                }
                else {
                    cout << "Failed to add box.\n";
                }
            }
        }
        else if (choice == 2) {
            if (isEmpty(s)) {
                cout << "Stack is empty.\n";
            }
            else {
                viewStack(s);
            }
        }
        else if (choice == 3) {
            if (isEmpty(s)) {
                cout << "Stack is empty. No boxes to dispatch.\n";
            }
            else {
                Box topBox;
                pop(s, topBox);
                cout << "Top box dispatched:\n";
                cout << "ID: " << topBox.id
                    << ", Item: " << topBox.item
                    << ", Destination: " << topBox.dest << "\n";
            }
        }
        else if (choice == 4) {
            cout << "========== INVENTORY SUMMARY ==========\n";
            cout << "Total Boxes in Stack: " << size(s) << "\n";
            cout << fixed << showpoint << setprecision(2);
            cout << "Total Weight: " << totalWeight(s) << " kg\n";
            Box topBox;
            if (peek(s, topBox)) {
                cout << "Top Box: ID " << topBox.id << " - " << topBox.item << "\n";
            }
            else {
                cout << "Top Box: (none)\n";
            }
            cout << "=======================================\n";
        }
        else if (choice == 5) {
            saveToFile(s, "inventory.txt");
            cout << "Inventory saved to inventory.txt. Have a productive day!\n";
        }
        else {
            cout << "Invalid option.\n";
        }

        if (choice != 5) {
            cout << "\n";
        }
    } while (choice != 5);

    return 0;
}
