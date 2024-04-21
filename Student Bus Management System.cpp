#include <bits/stdc++.h>

using namespace std;

// ANSI escape codes for styling
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string ITALIC = "\033[3m";
const string UNDERLINE = "\033[4m";
const string RED_TEXT = "\033[91m";
const string GREEN_TEXT = "\033[92m";
const string YELLOW_TEXT = "\033[93m";
const string BLUE_TEXT = "\033[94m";
const string MAGENTA_TEXT = "\033[95m";
const string CYAN_TEXT = "\033[96m";

class Person
{
public:
    Person(const string &name, const string &address, const string &contact)
        : name(name), address(address), contact(contact) {}

    ~Person(){};

    void displayInfo() const
    {
        cout << YELLOW_TEXT << setw(20) << left << name
             << setw(30) << left << address
             << setw(15) << left << contact
             << RESET;
    }

    string getName() const { return name; }

protected:
    string name;
    string address;
    string contact;
};

class Student : public Person
{
public:
    Student(const string &name, const string &address, const string &contact,
            const string &rollNo, const string &course)
        : Person(name, address, contact), rollNo(rollNo), course(course) {}

    void displayInfo() const
    {
        Person::displayInfo();
        cout << CYAN_TEXT << setw(15) << left << rollNo
             << course << RESET << endl;
    }

        // Function to retrieve address
    string getAddress() const { return address; }

    // Function to retrieve contact
    string getContact() const { return contact; }

    string getCourse() const { return course; }

private:
    string rollNo;
    string course;
};

class Bus
{
public:
    string busNo; // Make busNo public

    Bus(const string &busNo, int capacity) : busNo(busNo), capacity(capacity)
    {
        passengers.reserve(capacity);
    }

    bool addPassenger(const shared_ptr<Student> &student)
    {
        if (isFull())
        {
            cout << RED_TEXT << "Bus " << busNo << " is full." << RESET << endl;
            return false;
        }

        passengers.push_back(student);
        return true;
    }

    void displayPassengers() const
    {
        cout << BOLD << UNDERLINE << GREEN_TEXT << "\nBus " << busNo << " passengers:" << RESET << endl;
        cout << YELLOW_TEXT << setw(20) << left << "Name"
             << setw(30) << left << "Address"
             << setw(15) << left << "Contact"
             << setw(15) << left << "Roll No"
             << "Course" << RESET << endl;
        cout << YELLOW_TEXT << string(95, '-') << RESET << endl;
        for (const auto &passenger : passengers)
        {
            passenger->displayInfo();
        }
    }

    vector<shared_ptr<Student>> getPassengers() const
    {
        return passengers;
    }

private:
    bool isFull() const { return passengers.size() == capacity; }

    int capacity;
    vector<shared_ptr<Student>> passengers;
};

// Function to get user input for strings
string getStringInput(const string &prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

// Function to get user input for integers
int getIntInput(const string &prompt)
{
    int input;
    while (true)
    {
        cout << prompt;
        if (cin >> input)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            break;
        }
        else
        {
            cout << RED_TEXT << "Invalid input. Please enter an integer." << RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return input;
}

void saveData(const vector<Bus> &buses)
{
    ofstream outputFile("bus_data.txt");
    if (!outputFile)
    {
        cout << RED_TEXT << "Error: Unable to open file for writing." << RESET << endl;
        return;
    }

    for (const auto &bus : buses)
    {
        outputFile << bus.busNo << " " << bus.getPassengers().size() << endl;
        for (const auto &passenger : bus.getPassengers())
        {
            outputFile << passenger->getName() << " " << passenger->getAddress() << " " << passenger->getContact() << " " << passenger->getName() << " " << passenger->getCourse() << endl;
        }
    }

    outputFile.close();
    cout << GREEN_TEXT << "Data saved successfully." << RESET << endl;
}



void loadData(vector<Bus> &buses)
{
    ifstream inputFile("bus_data.txt");
    if (!inputFile)
    {
        cout << RED_TEXT << "Error: Unable to open file for reading." << RESET << endl;
        return;
    }

    buses.clear();
    string line;
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string busNo;
        int numPassengers;
        ss >> busNo >> numPassengers;
        int capacity = numPassengers;

        Bus bus(busNo, capacity);
        for (int i = 0; i < numPassengers; ++i)
        {
            string name, address, contact, rollNo, course;
            getline(inputFile, line);
            stringstream passengerStream(line);
            passengerStream >> name >> address >> contact >> rollNo >> course;
            auto passenger = make_shared<Student>(name, address, contact, rollNo, course);
            bus.addPassenger(passenger);
        }
        buses.push_back(bus);
    }

    inputFile.close();
    cout << GREEN_TEXT << "Data loaded successfully." << RESET << endl;
}

int main()
{
    cout << GREEN_TEXT << BOLD << "**" << RESET << endl;
    cout << BOLD << GREEN_TEXT << "*             Welcome to Student Bus Management        *" << RESET << endl;
    cout << BOLD << GREEN_TEXT << "*                      System                          *" << RESET << endl;
    cout << GREEN_TEXT << BOLD << "**" << RESET << endl;

    int choice;
    cout << CYAN_TEXT << "Enter 1 to load existing data or any other key to start fresh: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<Bus> buses;
    if (choice == 1)
    {
        loadData(buses);
    }
    else
    {
        int numBuses = getIntInput(CYAN_TEXT + "Enter the number of buses: " + RESET);

        for (int i = 0; i < numBuses; ++i)
        {
            string busNo = getStringInput(CYAN_TEXT + "Enter the bus number for Bus " + to_string(i + 1) + ": " + RESET);
            int capacity = getIntInput(CYAN_TEXT + "Enter the capacity of Bus " + to_string(i + 1) + ": " + RESET);
            buses.emplace_back(busNo, capacity);
        }

        cout << ITALIC << YELLOW_TEXT << "\nEnter student details for each bus or type 'done' to finish.\n"
             << RESET << endl;

        for (int i = 0; i < numBuses; ++i)
        {
            cout << ITALIC << YELLOW_TEXT << "Bus " << buses[i].busNo << ":" << RESET << endl;
            while (true)
            {
                string name = getStringInput(CYAN_TEXT + "Name: " + RESET);
                if (name == "done")
                {
                    break;
                }
                string address = getStringInput(CYAN_TEXT + "Address: " + RESET);
                string contact = getStringInput(CYAN_TEXT + "Contact: " + RESET);
                string rollNo = getStringInput(CYAN_TEXT + "Roll No: " + RESET);
                string course = getStringInput(CYAN_TEXT + "Course: " + RESET);

                auto student = make_shared<Student>(name, address, contact, rollNo, course);
                if (!buses[i].addPassenger(student))
                {
                    break;
                }
            }
        }
    }

    for (int i = 0; i < buses.size(); ++i)
    {
        cout << endl;
        buses[i].displayPassengers();
    }

    cout << CYAN_TEXT << "Enter 1 to save the data or any other key to exit: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (choice == 1)
    {
        saveData(buses);
    }

    return 0;
}
