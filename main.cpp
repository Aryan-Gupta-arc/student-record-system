#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    float marks;

    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << "\nRoll No: " << rollNo << "\nName: " << name << "\nMarks: " << marks << "\n";
    }
};

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);
    if (!file) {
        cerr << "File could not be opened.\n";
        return;
    }
    s.input();
    file.write(reinterpret_cast<char*>(&s), sizeof(s));
    file.close();
    cout << "Student record added.\n";
}

void displayAll() {
    Student s;
    ifstream file("students.dat", ios::binary);
    if (!file) {
        cerr << "No records found.\n";
        return;
    }
    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        s.display();
        cout << "-----------------------------";
    }
    file.close();
}

void searchStudent(int roll) {
    Student s;
    bool found = false;
    ifstream file("students.dat", ios::binary);
    if (!file) {
        cerr << "No records found.\n";
        return;
    }
    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "Record Found:\n";
            s.display();
            found = true;
            break;
        }
    }
    file.close();
    if (!found)
        cout << "Record not found.\n";
}

void deleteStudent(int roll) {
    Student s;
    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo != roll)
            outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
        else
            found = true;
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Record not found.\n";
}

void updateStudent(int roll) {
    Student s;
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "Current details:\n";
            s.display();
            cout << "\nEnter new details:\n";
            s.input();
            file.seekp(-static_cast<int>(sizeof(s)), ios::cur);
            file.write(reinterpret_cast<char*>(&s), sizeof(s));
            found = true;
            cout << "Record updated successfully.\n";
            break;
        }
    }

    file.close();
    if (!found)
        cout << "Record not found.\n";
}

int main() {
    int choice, roll;

    do {
        cout << "\n==== Student Record Management System ====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Delete Student\n";
        cout << "5. Update Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            cout << "Enter Roll No to search: ";
            cin >> roll;
            searchStudent(roll);
            break;
        case 4:
            cout << "Enter Roll No to delete: ";
            cin >> roll;
            deleteStudent(roll);
            break;
        case 5:
            cout << "Enter Roll No to update: ";
            cin >> roll;
            updateStudent(roll);
            break;
        case 6:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
