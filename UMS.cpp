#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Base Class for Person (for Teacher and Library User)
class Person {
protected:
    string name;
    int age;
    string id;

public:
    Person()
	{
		name = "";
		age = 0;
		id = ""; 
	}
    Person(string n, int a, string i) 
	{
		name =  n;
		age = a;
		id = i;
	}

    void setPerson(string n, int a, string i) {
        name = n;
        age = a;
        id = i;
    }

    void displayPerson() {
        cout << "Name: " << name << "\nAge: " << age << "\nID: " << id << endl;
    }
};

// Teacher Class: Derived from Person
class Teacher : public Person {
private:
    string classes[5];
    string subjects[5];
    int classCount = 0;
    int subjectCount = 0;
    int selectedClassIndex = -1;

    struct Student {
        string name;
        int rollNumber;
        float marks[5]; // Array for marks (lab reports, assessments, midterm, etc.)
        float totalMarks;
        float percentage;
        char grade;
        float gpa;
    };

    Student students[5];
    int studentCount = 0;
    float weights[5]; // Weights for assessments

public:
    Teacher() {
        for (int i = 0; i < 5; i++) {
            weights[i] = 0;
        }
    }

    void enterClassesAndSubjects() {
        cout << "Enter the number of classes to add (up to 5): ";
        cin >> classCount;
        cin.ignore(); // Clear input buffer
        for (int i = 0; i < classCount; i++) {
            cout << "Enter name for Class " << i + 1 << ": ";
            getline(cin, classes[i]);
        }

        cout << "Enter the number of subjects to add (up to 5): ";
        cin >> subjectCount;
        cin.ignore(); // Clear input buffer
        for (int i = 0; i < subjectCount; i++) {
            cout << "Enter name for Subject " << i + 1 << ": ";
            getline(cin, subjects[i]);
        }
    }

    void selectClass() {
        cout << "\nSelect a class:\n";
        for (int i = 0; i < classCount; i++) {
            cout << i + 1 << ". " << classes[i] << endl;
        }
        cout << "Enter your choice: ";
        cin >> selectedClassIndex;
        selectedClassIndex -= 1; // Adjust for array index
    }

    void addStudents() {
        cout << "\nEnter the number of students to add (up to 5): ";
        cin >> studentCount;
        cin.ignore(); // Clear input buffer

        for (int i = 0; i < studentCount; i++) {
            cout << "Enter name for Student " << i + 1 << ": ";
            getline(cin, students[i].name);
            cout << "Enter roll number for " << students[i].name << ": ";
            cin >> students[i].rollNumber;
            cin.ignore(); // Clear input buffer

            // Initialize marks
            for (int j = 0; j < 5; j++) {
                students[i].marks[j] = 0;
            }
            students[i].totalMarks = students[i].percentage = students[i].gpa = 0;
            students[i].grade = 'F';
        }
    }

    void assignWeights() {
        cout << "\nAssign weights to each assessment type (in percentage):\n";
        cout << "1. Lab Reports: ";
        cin >> weights[0];
        cout << "2. Lab Assessments: ";
        cin >> weights[1];
        cout << "3. Midterm: ";
        cin >> weights[2];
        cout << "4. CEA: ";
        cin >> weights[3];
        cout << "5. Final Term: ";
        cin >> weights[4];

        float totalWeight = weights[0] + weights[1] + weights[2] + weights[3] + weights[4];
        if (totalWeight != 100) {
            cout << "Total weight must be 100%. Please reassign weights.\n";
            assignWeights();
        }
    }

    void enterMarks() {
        if (selectedClassIndex == -1) {
            cout << "No class selected!\n";
            return;
        }

        int category;
        cout << "\nSelect Assessment Category:\n";
        cout << "1. Lab Assessments\n";
        cout << "2. Lab Reports\n";
        cout << "3. Midterm\n";
        cout << "4. CEA\n";
        cout << "5. Final Term\n";
        cout << "Enter your choice: ";
        cin >> category;

        for (int i = 0; i < studentCount; i++) {
            cout << "Enter marks for " << students[i].name << " (Roll No: " << students[i].rollNumber << "): ";
            if (category == 1) {
                cin >> students[i].marks[0]; // Lab Assessments
            } else if (category == 2) {
                cin >> students[i].marks[1]; // Lab Reports
            } else if (category == 3) {
                cin >> students[i].marks[2]; // Midterm
            } else if (category == 4) {
                cin >> students[i].marks[3]; // CEA
            } else {
                cin >> students[i].marks[4]; // Final Term
            }
        }
    }

    void calculateResults() {
        for (int i = 0; i < studentCount; i++) {
            float totalMarks = 0;
            for (int j = 0; j < 5; j++) {
                totalMarks += students[i].marks[j];
            }
            students[i].totalMarks = totalMarks;
            students[i].percentage = (totalMarks / 500) * 100;

            // Assign Grade and GPA based on percentage
            if (students[i].percentage >= 85) {
                students[i].grade = 'A';
                students[i].gpa = 4.0;
            } else if (students[i].percentage >= 80) {
                students[i].grade = 'A';
                students[i].gpa = 3.7;
            } else if (students[i].percentage >= 70) {
                students[i].grade = 'B';
                students[i].gpa = 3.0;
            } else {
                students[i].grade = 'F';
                students[i].gpa = 0.0;
            }
        }
    }

    void displayResults() {
        cout << "\nResults for Class: " << classes[selectedClassIndex] << "\n";
        cout << "Name\tRoll No\tMarks\tPercentage\tGrade\tGPA\n";
        for (int i = 0; i < studentCount; i++) {
            cout << students[i].name << "\t" << students[i].rollNumber << "\t"
                 << students[i].totalMarks << "\t" << students[i].percentage << "\t"
                 << students[i].grade << "\t" << students[i].gpa << endl;
        }
    }
};

// Cafe Class
class Cafe {
private:
    string menuItems[7][5] = {
        {"Burger", "Pizza", "Pasta", "Coffee", "Sandwich"},  // Monday
        {"Salad", "Fries", "Juice", "Burger", "Taco"},       // Tuesday
        {"Pizza", "Pasta", "Soda", "Wrap", "Sandwich"},      // Wednesday
        {"Pasta", "Burger", "Soup", "Coffee", "Cake"},       // Thursday
        {"Burger", "Pizza", "Fries", "Ice Cream", "Smoothie"}, // Friday
        {"Sandwich", "Pizza", "Salad", "Coffee", "Brownie"}, // Saturday
        {"Pasta", "Burger", "Tacos", "Smoothie", "Cake"}     // Sunday
    };
    float menuPrices[7][5] = {
        {5.0, 8.0, 7.5, 2.5, 4.0},  // Monday
        {4.5, 3.0, 2.5, 5.0, 3.5},  // Tuesday
        {6.0, 7.5, 3.0, 4.0, 3.5},  // Wednesday
        {6.5, 5.0, 4.5, 2.5, 3.0},  // Thursday
        {5.0, 8.0, 4.0, 3.0, 3.5},  // Friday
        {4.0, 6.0, 3.5, 2.5, 4.0},  // Saturday
        {5.5, 7.0, 3.0, 3.5, 2.5}   // Sunday
    };
    float gstRate = 4.0;
    // Rest of the Cafe code remains the same

public:
    void displayMenu(int day) {
        cout << "\nCafe Menu for ";
        switch(day) {
            case 0: cout << "Monday"; break;
            case 1: cout << "Tuesday"; break;
            case 2: cout << "Wednesday"; break;
            case 3: cout << "Thursday"; break;
            case 4: cout << "Friday"; break;
            case 5: cout << "Saturday"; break;
            case 6: cout << "Sunday"; break;
            default: cout << "Invalid Day"; return;
        }

        cout << ":\n";
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << menuItems[i][day] << " - $" << fixed << setprecision(2) << menuPrices[i][day] << endl;
        }
    }

    void placeOrder() {
        int order[10], orderCount = 0;
        int choice;
        char cont;
        int day;

        // Get the current day of the week (0 = Monday, 1 = Tuesday, ..., 6 = Sunday)
        cout << "Enter the day of the week (0 for Monday, 6 for Sunday): ";
        cin >> day;

        do {
            displayMenu(day);  // Display the menu based on the current day
            cout << "Enter item number to order: ";
            cin >> choice;

            // Check if the user selects a valid menu item
            if (orderCount < 10 && choice >= 1 && choice <= 5) {
                order[orderCount++] = choice - 1;  // Store the item index (0-4)
            } else {
                cout << "Invalid choice or order limit reached. Try again.\n";
            }

            // Ask if the user wants to add more items or delete an item
            cout << "Do you want to order more or delete an item? (Enter 'y' to buy more, 'd' to delete an item, 'b' for bill): ";
            cin >> cont;

            if (cont == 'd' || cont == 'D') {
                int deleteItem;
                cout << "Enter the item number to delete from your order: ";
                cin >> deleteItem;

                if (deleteItem >= 1 && deleteItem <= 5) {
                    bool found = false;
                    for (int i = 0; i < orderCount; i++) {
                        if (order[i] == deleteItem - 1) {
                            for (int j = i; j < orderCount - 1; j++) {
                                order[j] = order[j + 1];  // Shift the items to delete the selected item
                            }
                            orderCount--;
                            cout << "Item removed from your order.\n";
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Item not found in your order.\n";
                    }
                } else {
                    cout << "Invalid item number.\n";
                }
            }

        } while (cont == 'y' || cont == 'Y');

        // Calculate and show the bill
        calculateBill(order, orderCount, day);
    }

    void calculateBill(int order[], int count, int day) {
        float total = 0;
        cout << "\nYour Order:\n";
        for (int i = 0; i < count; i++) {
            cout << menuItems[order[i]][day] << " - $" << fixed << setprecision(2) << menuPrices[order[i]][day] << endl;
            total += menuPrices[order[i]][day];
        }
        total += (total * gstRate / 100);  // Adding GST
        cout << "Total (including 4% GST): $" << fixed << setprecision(2) << total << endl;
    }
};

// Library Class
class Library {
private:
    string books[5];
    bool issued[5] = {false, false, false, false, false};

public:
    void addBooks() {
        for (int i = 0; i < 5; i++) {
            cout << "Enter name of Book " << i + 1 << ": ";
            getline(cin, books[i]);
        }
    }

    void issueBook() {
        int bookChoice;
        cout << "Available Books:\n";
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << books[i] << " - " << (issued[i] ? "Issued" : "Available") << endl;
        }
        cout << "Enter the number of the book you want to issue: ";
        cin >> bookChoice;
        bookChoice -= 1;  // Adjust for index

        if (bookChoice < 0 || bookChoice >= 5) {
            cout << "Invalid choice!\n";
            return;
        }

        if (issued[bookChoice]) {
            cout << "Sorry, this book is already issued.\n";
        } else {
            issued[bookChoice] = true;
            cout << "Book issued successfully.\n";
        }
    }

    void returnBook() {
        int bookChoice;
        cout << "Issued Books:\n";
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << books[i] << " - " << (issued[i] ? "Issued" : "Available") << endl;
        }
        cout << "Enter the number of the book you want to return: ";
        cin >> bookChoice;
        bookChoice -= 1;  // Adjust for index

        if (bookChoice < 0 || bookChoice >= 5) {
            cout << "Invalid choice!\n";
            return;
        }

        if (!issued[bookChoice]) {
            cout << "This book is not issued.\n";
        } else {
            issued[bookChoice] = false;
            cout << "Book returned successfully.\n";
        }
    }
};

int main() {
    Teacher teacher;
    Cafe cafe;
    Library library;

    int choice;
    do {
        cout << "\nUniversity Management System\n";
        cout << "1. Teacher Portal\n";
        cout << "2. University Cafe\n";
        cout << "3. Library\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int teacherChoice;
                cout << "\nTeacher Portal\n";
                cout << "1. Enter Classes and Subjects\n";
                cout << "2. Select Class\n";
                cout << "3. Add Students\n";
                cout << "4. Assign Weights\n";
                cout << "5. Enter Marks\n";
                cout << "6. Calculate Results\n";
                cout << "7. Display Results\n";
                cout << "Enter your choice: ";
                cin >> teacherChoice;

                switch (teacherChoice) {
                    case 1: teacher.enterClassesAndSubjects(); break;
                    case 2: teacher.selectClass(); break;
                    case 3: teacher.addStudents(); break;
                    case 4: teacher.assignWeights(); break;
                    case 5: teacher.enterMarks(); break;
                    case 6: teacher.calculateResults(); break;
                    case 7: teacher.displayResults(); break;
                    default: cout << "Invalid choice!\n"; break;
                }
                break;
            }
            case 2:
                cafe.placeOrder();
                break;
            case 3: {
                int libraryChoice;
                cout << "\nLibrary\n";
                cout << "1. Add Books\n";
                cout << "2. Issue Book\n";
                cout << "3. Return Book\n";
                cout << "Enter your choice: ";
                cin >> libraryChoice;

                switch (libraryChoice) 
				{
                    case 1: library.addBooks(); break;
                    case 2: library.issueBook(); break;
                    case 3: library.returnBook(); break;
                    default: cout << "Invalid choice!\n"; break;
                }
                break;
            }
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}

