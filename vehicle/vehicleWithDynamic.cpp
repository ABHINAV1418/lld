#include <iostream>

using namespace std;

class Vehicle {
    int totalPassengers;
    int totalDistanceTravelled;
    int totalTime;
    int chassisNumber;
    int numberOfWheels;

    public :

    Vehicle(int totalPassengers, int chassisNumber, int numberOfWheels) {
        this->totalPassengers = totalPassengers;
        this->chassisNumber = chassisNumber;
        this->numberOfWheels = numberOfWheels;
    }

    int getTotalDistanceTravelled() {
        return this->totalDistanceTravelled;
    }

    virtual void printDetails() const {
        cout << "Vehicle Info:\n";
        cout << "  Passengers: " << totalPassengers << "\n";
        cout << "  Chassis No: " << chassisNumber << "\n";
        cout << "  Wheels: " << numberOfWheels << "\n";
    }

    void startEngine() {
        cout<<"Vehicle's engine started ";
    }

    void stop() {
        cout<<"Vehicle's engine stopped";
    }

    virtual void calculateMileage() const {
        cout<<"Vehicle's milege is "<<endl;
    }

    virtual void transportGoods() {
        cout<<"vehicle's transport goods are "<<endl;
    }
    
    virtual ~Vehicle() noexcept {}
};

class Car: public Vehicle {
    string carType;
    
    public:

    Car(int passengers, int chassisNumber, int numberOfWheels, string carType): Vehicle(passengers, chassisNumber, numberOfWheels) {
        this->carType = carType;
    }

    string getCarType() const {
        return this->carType;
    }
    
    void printDetails() const override {
        cout << "[Car]\n";
        Vehicle :: printDetails();
        cout << "  Car Type: " << carType << "\n";
    }

    void calculateMileage() const override {
        cout<< "Cars milege is "<<endl;
    }
};

class Truck: public Vehicle {
    int totalLuggageSpace;
    
    public:

    Truck(int passengers, int chassisNumber, int numberOfWheels, int totalLuggageSpace): Vehicle(passengers, chassisNumber, numberOfWheels) {
        this->totalLuggageSpace = totalLuggageSpace;
    }

    int getTotalLuggageSpace() {
        return this->totalLuggageSpace;
    }

    void transportGoods() {
        cout<<"Trucks transport goods are "<<endl;
    }
};

class MotorBike: public Vehicle {
    bool hasContainer;
    
    public:

    MotorBike(int passengers, int chassisNumber, int numberOfWheels, bool hasContainer): Vehicle(passengers, chassisNumber, numberOfWheels) {
        this->hasContainer = hasContainer;
    }

    int hasContainerOrNot() {
        return this->hasContainer;
    }

    void calculateMileage() const override {
        cout << "Motorbike has high mileage.\n";
    }
};

int main() {
    // Car car = Car(3, 1234, 4, "hatchback");
    // Truck truck = Truck(2, 345, 8, 234);
    MotorBike bike = MotorBike(1, 356, 2, 0);
    // cout << "Car type: " << car.getCarType() << endl;
    // car.printDetails(); // this doesn't do any polymorphism printDetails only specific to car
    // making a vechicle pointer will enable polymorphism
    Vehicle *v = new Car(4, 999, 4, "random"); // only pointers or refernce preserve the polymorphic behaviour
    // Vehicle v =  Car(4, 999, 4, "random"); making a vechicle object here will will take printDetails of vehicle and not of car class
    // v = new Truck()
    v->printDetails();
    v->calculateMileage();
    Vehicle *v2 = new Truck(4, 876, 8, 88);
    v2->transportGoods();
    // delete v;
}