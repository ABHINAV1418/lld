#include <iostream>
using namespace std;

class Student {
    string name;
    int rollNumber;
    string address;

    public: 

    Student(string name, int rollNumber) {
        this->name = name;
        this->rollNumber = rollNumber;
    }
    
    string getName() {
        return this->name;
    }

    int getRollNumber() {
        return this->rollNumber;
    }
    void setAddress(string address) {
    }
    void enroll(string name) {
    } 
    void dropOut(string name) {
    }
};

class University {
    string name;
    string address;
    vector<Student> students; // doing this is wrong 

    public: 
    
    University(string name, string addr) {
        this->name = name;
        this->address = addr;
    }

    void admitStudent(Student student) {
        students.push_back(student);
        cout << student.getName() << " admitted to " << name << ".\n";
    }

    void listStudents() {
        cout << "Students in " << name << ":\n";
        for (Student s : students) {
            cout << " - " << s.getName() << " (Roll: " << s.getRollNumber() << ")\n";
        }
    }
};

int main() {
    Student s1("Abhinav", 001);
    Student s2("Ayush", 002);

    University uni("IIIT", "Sonepat");
    uni.admitStudent(s1);
    uni.admitStudent(s2);
    cout<<"name of student1 "<<s1.getName()<<endl;
    cout<<"studets in uni. are "<<endl;
    uni.listStudents();

}

