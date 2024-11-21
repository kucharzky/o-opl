#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

class Addr {
    string Country;
    string City;
    string Street;
public:
    Addr(string co, string ci, string st) : Country(co), City(ci), Street(st) {}
    string get_Country() const {
        return Country;
    }
    string get_City() const {
        return City;
    }
    string get_Street() const {
        return Street;
    }
};

class Person {
    string firstName;
    string lastName;
    int age;
    Addr adr;
public:
    Person(string _firstName, string _lastName, int _age, Addr _adr) : firstName(_firstName), lastName(_lastName), age(_age), adr(_adr) {}

    void set_adr(Addr adres) {
        adr = adres;
    }
    void set_firstName(string fN) {
        firstName = fN;
    }
    void set_lastName(string lN) {
        lastName = lN;
    }
    void set_age(int value) {
        age = value;
    }

    string get_firstName() const {
        return firstName;
    }

    string get_lastName() const {
        return lastName;
    }

    int get_age() const {
        return age;
    }

    Addr get_adr() const {
        return adr;
    }

    friend ostream& operator <<(ostream& o, const Person& p) {
        o << "First Name: " << p.firstName << ", Last Name: " << p.lastName << ", Age: " << p.age
            << ", Address: " << p.adr.get_Country() << ", " << p.adr.get_City() << ", " << p.adr.get_Street();
        return o;
    }

    friend istream& operator >>(istream& i, Person& p) {
        i >> p.firstName >> p.lastName >> p.age;
        string country, city, street;
        i >> country >> city >> street;
        p.adr = Addr(country, city, street);
        return i;
    }
};

// case sensitivity
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

bool isValidName(const string& name) {
    if (name.empty()) return false;
    return all_of(name.begin(), name.end(), [](char ch) {
        return isalpha(ch) || isspace(ch);
        });
}

bool isValidAge(int age) {
    return age > 0 && age < 150;
}

// czyszczenie cin
void clearInputBuffer() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

string getValidString(const string& prompt, const string& fieldName) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << fieldName << " cannot be empty. Please try again.\n";
            continue;
        }
        if (!isValidName(input)) {
            cout << "Invalid " << fieldName << ". Please use only letters and spaces.\n";
            continue;
        }
        return input;
    }
}

int getValidAge() {
    int age;
    while (true) {
        cout << "Enter age: ";
        if (cin >> age) {
            clearInputBuffer();
            if (isValidAge(age)) {
                return age;
            }
            cout << "Invalid age. Please enter a number\n";
        }
        else {
            cout << "Invalid input. Please enter a valid number.\n";
            clearInputBuffer();
        }
    }
}

class DataBase {
public:
    using DB = vector<Person>;
    DB db;

    void add(Person& p) {
        db.push_back(p);
    }

    void remove(const string& firstName, const string& lastName) {
        string searchFirstName = toLowerCase(firstName);
        string searchLastName = toLowerCase(lastName);
        vector<size_t> matches;

        // szukanie tych samych osob w bazie
        for (size_t i = 0; i < db.size(); ++i) {
            if (toLowerCase(db[i].get_firstName()) == searchFirstName &&
                toLowerCase(db[i].get_lastName()) == searchLastName) {
                matches.push_back(i);
            }
        }

        if (matches.empty()) {
            cout << "No matching persons found." << endl;
            return;
        }

        if (matches.size() == 1) {
            db.erase(db.begin() + matches[0]);
            cout << "Person removed successfully." << endl;
            return;
        }

        // case dla osob z tymi samymi imionami
        cout << "\nMultiple matches found. Please select which one to remove:\n";
        for (size_t i = 0; i < matches.size(); ++i) {
            cout << i + 1 << ") " << db[matches[i]] << endl;
        }

        size_t choice;
        while (true) {
            cout << "Enter number (1-" << matches.size() << ") or 0 to cancel: ";
            if (cin >> choice && choice <= matches.size()) {
                if (choice == 0) {
                    cout << "Removal cancelled." << endl;
                    return;
                }
                db.erase(db.begin() + matches[choice - 1]);
                cout << "Person removed successfully." << endl;
                break;
            }
            cout << "Invalid choice. Please try again." << endl;
            clearInputBuffer();
        }
    }

    void searchByName(const string& firstName, const string& lastName) const {
        string searchFirstName = toLowerCase(firstName);
        string searchLastName = toLowerCase(lastName);
        bool found = false;

        for (const auto& person : db) {
            if (toLowerCase(person.get_firstName()) == searchFirstName &&
                toLowerCase(person.get_lastName()) == searchLastName) {
                cout << "Found person:\n" << person << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No persons found with this name." << endl;
        }
    }

    void searchByAge(int age) const {
        bool found = false;
        for (const auto& person : db) {
            if (person.get_age() == age) {
                cout << "Found person:\n" << person << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No persons found with age " << age << endl;
        }
    }

    void searchByAgeRange(int minAge, int maxAge) const {
        bool found = false;
        for (const auto& person : db) {
            if (person.get_age() >= minAge && person.get_age() <= maxAge) {
                cout << "Found person:\n" << person << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No persons found in age range " << minAge << "-" << maxAge << endl;
        }
    }

    void searchByCity(const string& city) const {
        string searchCity = toLowerCase(city);
        bool found = false;
        for (const auto& person : db) {
            if (toLowerCase(person.get_adr().get_City()) == searchCity) {
                cout << "Found person:\n" << person << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No persons found in city " << city << endl;
        }
    }

    void searchByCountry(const string& country) const {
        string searchCountry = toLowerCase(country);
        bool found = false;
        for (const auto& person : db) {
            if (toLowerCase(person.get_adr().get_Country()) == searchCountry) {
                cout << "Found person:\n" << person << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No persons found in country " << country << endl;
        }
    }

    void printAll() const {
        if (db.empty()) {
            cout << "Database is empty." << endl;
            return;
        }
        for (const auto& person : db) {
            cout << person << endl;
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening file for writing!" << endl;
            return;
        }
        for (const auto& person : db) {
            file << person.get_firstName() << endl << person.get_lastName() << endl
                << person.get_age() << endl << person.get_adr().get_Country() << endl
                << person.get_adr().get_City() << endl << person.get_adr().get_Street() << endl;
        }
        cout << "Database saved successfully!" << endl;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file for reading!" << endl;
            return;
        }
        db.clear();
        string tempfirst, templast, tempcountry, tempcity, tempstreet;
        int ag;
        while (getline(file, tempfirst)&&getline(file, templast)&&file>>ag && file.ignore()&&getline(file,tempcountry)&&getline(file,tempcity)&&getline(file,tempstreet)) {
            Addr address(tempcountry,tempcity,tempstreet);
            Person person(tempfirst,templast,ag,address);
            db.push_back(person);
        }
        cout << "Database loaded successfully!" << endl;
    }

    // pomocnicza
    void mergeDatabase(const DataBase& other) {
        size_t initialSize = db.size();
        for (const auto& person : other.db) {
            db.push_back(person);
        }
        cout << "Merged " << (db.size() - initialSize) << " records successfully!" << endl;
    }

    // tu sie dzieje cala magia
    bool mergeFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file for reading!" << endl;
            return false;
        }

        DataBase tempDB;
        Person temp("", "", 0, Addr("", "", ""));
        while (file >> temp) {
            tempDB.add(temp);
        }

        if (tempDB.db.empty()) {
            cout << "No valid records found in file!" << endl;
            return false;
        }

        // preview
        cout << "\nPreview of records to be merged:\n";
        tempDB.printAll();

        char confirm;
        cout << "\nDo you want to merge these records? (y/n): ";
        cin >> confirm;
        clearInputBuffer();

        if (tolower(confirm) == 'y') {
            mergeDatabase(tempDB);
            return true;
        }

        cout << "Merge cancelled." << endl;
        return false;
    }
};

void printSearchMenu() {
    cout << "\nSearch Options:\n";
    cout << "1. Search by name\n";
    cout << "2. Search by age\n";
    cout << "3. Search by age range\n";
    cout << "4. Search by city\n";
    cout << "5. Search by country\n";
    cout << "6. Return to main menu\n";
    cout << "Enter your choice: ";
}
void printMenu() {
    cout << "\nDatabase Management System\n";
    cout << "1. Add new person\n";
    cout << "2. Remove person\n";
    cout << "3. Search for person\n";
    cout << "4. Display all records\n";
    cout << "5. Save database to file\n";
    cout << "6. Load database from file\n";
    cout << "7. Merge with another database\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    DataBase database;
    int choice;
    string firstName, lastName, country, city, street;
    int age;

    while (true) {
        printMenu();

        // Validate menu choice input
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 1 and 8.\n";
            clearInputBuffer();
            printMenu();
        }
        clearInputBuffer();

        switch (choice) {
        case 1: {
            firstName = getValidString("Enter first name: ", "First name");
            lastName = getValidString("Enter last name: ", "Last name");
            age = getValidAge();
            country = getValidString("Enter country: ", "Country");
            city = getValidString("Enter city: ", "City");
            street = getValidString("Enter street: ", "Street");

            Addr address(country, city, street);
            Person person(firstName, lastName, age, address);
            database.add(person);
            cout << "Person added successfully!" << endl;
            break;
        }
        case 2: {
            firstName = getValidString("Enter first name to remove: ", "First name");
            lastName = getValidString("Enter last name to remove: ", "Last name");
            database.remove(firstName, lastName);
            cout << "Person removed (if existed)." << endl;
            break;
        }
        case 3: {
            int searchChoice;
            printSearchMenu();

            while (!(cin >> searchChoice) || searchChoice < 1 || searchChoice > 6) {
                cout << "Invalid input. Please try again.\n";
                clearInputBuffer();
                printSearchMenu();
            }
            clearInputBuffer();

            switch (searchChoice) {
            case 1: {
                firstName = getValidString("Enter first name to search: ", "First name");
                lastName = getValidString("Enter last name to search: ", "Last name");
                database.searchByName(firstName, lastName);
                break;
            }
            case 2: {
                age = getValidAge();
                database.searchByAge(age);
                break;
            }
            case 3: {
                int minAge, maxAge;
                cout << "Enter minimum age: ";
                while (!(cin >> minAge) || !isValidAge(minAge)) {
                    cout << "Invalid age. Please try again.\n";
                    clearInputBuffer();
                }
                cout << "Enter maximum age: ";
                while (!(cin >> maxAge) || !isValidAge(maxAge) || maxAge < minAge) {
                    cout << "Invalid age range. Please try again.\n";
                    clearInputBuffer();
                }
                database.searchByAgeRange(minAge, maxAge);
                break;
            }
            case 4: {
                city = getValidString("Enter city to search: ", "City");
                database.searchByCity(city);
                break;
            }
            case 5: {
                country = getValidString("Enter country to search: ", "Country");
                database.searchByCountry(country);
                break;
            }
            case 6:
                break;
            }
            break;
        }
        case 4:
            database.printAll();
            break;
        case 5: {
            string filename;
            cout << "Enter filename to save: ";
            getline(cin, filename);
            if (filename.empty()) {
                cout << "Filename cannot be empty!\n";
                break;
            }
            database.saveToFile(filename);
            break;
        }
        case 6: {
            string filename;
            cout << "Enter filename to load: ";
            getline(cin, filename);
            if (filename.empty()) {
                cout << "Filename cannot be empty!\n";
                break;
            }
            database.loadFromFile(filename);
            break;
        }
        case 7: {
            string filename;
            cout << "Enter filename to merge from: ";
            getline(cin, filename);
            if (filename.empty()) {
                cout << "Filename cannot be empty!\n";
                break;
            }
            database.mergeFromFile(filename);
            break;
        }
        case 8:
            cout << "Exiting program..." << endl;
            return 0;

        default:
            cout << "Invalid choice! Please enter a number between 1 and 9." << endl;
        }
    }
    return 0;
}