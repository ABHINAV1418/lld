#include <iostream>
#include <vector>
using namespace std;

class Student {
private:
    string name;
    int rollNumber;
    string address;

public:
    // Constructor
    Student(string name, int rollNumber) {
        this->name = name;
        this->rollNumber = rollNumber;
    }

    void setAddress(string addr) {
        address = addr;
    }

    void enroll() {
        cout << name << " enrolled.\n";
    }

    void dropOut() {
        cout << name << " dropped out.\n";
    }

    string getName() const {
        return name;
    }

    int getRollNumber() const {
        return rollNumber;
    }
};

class University {
private:
    string name;
    string address;
    vector<Student*> students;  // Aggregation: University has many Students (but doesn't own them)

public:
    // Constructor
    University(string name, string addr) {
        this->name = name;
        this->address = addr;
    }

    void admitStudent(Student* student) {
        students.push_back(student);
        cout << student->getName() << " admitted to " << name << ".\n";
    }

    void listStudents() {
        cout << "Students in " << name << ":\n";
        for (Student* s : students) {
            cout << " - " << s->getName() << " (Roll: " << s->getRollNumber() << ")\n";
        }
    }
};

int main() {
    Student* s1 = new Student("Alice", 101);
    Student* s2 = new Student("Bob", 102);

    University u("IIT Bombay", "Mumbai");

    u.admitStudent(s1);
    u.admitStudent(s2);

    u.listStudents();

    delete s1;
    delete s2;

    return 0;
}