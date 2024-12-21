#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int StringToInt(string str)
{
    int n;
    stringstream ss(str);
    ss >> n;
    return n;
}

void ReadArray(string students[][750], int &maleStudents, int &femaleStudents, int &totalStudents)
{
    ifstream studentFile("Student_Data.txt");
    if (!studentFile)
    {
        cerr << "ERROR: Student File can't be Opened!";
        return;
    }
    // [0 = Name] [1 = Reg] [2 = Gender] [3 = Age] [4 = CNIC] [5 = Program] [6 = Section]
    // [7 = Password] [8 = Contact] [9 = Emergency Contact] [10 = Hostel] [11 = Room Number]
    string line;

    int i = -1;
    while (getline(studentFile, line))
    {
        if (line.find("Name: ") == 0)
        {
            i++;
            students[0][i] = line.substr(6);
        }
        else if (line.find("Reg: ") == 0)
        {
            students[1][i] = line.substr(5);
        }
        else if (line.find("Gender: ") == 0)
        {
            students[2][i] = line.substr(8);
            if (students[2][i] == "M")
            {
                maleStudents++;
            }
            else if (students[2][i] == "F")
            {
                femaleStudents++;
            }
        }
        else if (line.find("Age: ") == 0)
        {
            students[3][i] = line.substr(5);
        }
        else if (line.find("CNIC: ") == 0)
        {
            students[4][i] = line.substr(6);
        }
        else if (line.find("Program: ") == 0)
        {
            students[5][i] = line.substr(9);
        }
        else if (line.find("Section: ") == 0)
        {
            students[6][i] = line.substr(9);
        }
        else if (line.find("Account Password: ") == 0)
        {
            students[7][i] = line.substr(18);
        }
        else if (line.find("Contact: ") == 0)
        {
            students[8][i] = line.substr(9);
        }
        else if (line.find("Emergency Contact: ") == 0)
        {
            students[9][i] = line.substr(19);
        }
        else if (line.find("Hostel: ") == 0)
        {
            students[10][i] = line.substr(8);
        }
        else if (line.find("Room Number: ") == 0)
        {
            students[11][i] = line.substr(13);
        }
        else if (line == "---")
        {
            totalStudents++;
        }
    }
    studentFile.close();
}

int DisplayLoginChoice()
{
    int choice;
    while (true)
    {
        cout << "\nSelect an option:\n\n";
        cout << " 1. Student login\n";
        cout << " 2. Admin login\n";
        cout << "\nInput (1 - 2):  ";
        cin >> choice;

        if (choice < 1 || choice > 2)
        {
            cout << "\033[31m\nInvalid input, please try again.\n\033[0m";
        }
        else
        {
            return choice;
        }
    }
}

int LoginAccount(int choice, string *students, int maxStudents)
{

    if (choice == 1)
    {
        string regNo, password;
        cout << "\nEnter Registration Number: ";
        cin >> regNo;
        for (int i = 0; i < maxStudents; i++)
        {
            if (*(students + 1 * maxStudents + i) == regNo)
            {
                cout << "Enter Password: ";
                cin >> password;
                if (*(students + 7 * maxStudents + i) == password)
                {
                    return StringToInt(regNo);
                }
                else
                {
                    cout << "\033[31m\nInvalid password, please try again.\n\033[0m";
                    LoginAccount(choice, students, maxStudents);
                }
            }
        }
        cout << "\033[31m\nInvalid registration number, please try again.\n\033[0m";
        LoginAccount(choice, students, maxStudents);
    }
    else if (choice == 2)
    {
        cout << "\n[ADMIN LOGIN]\n";
    }
}

int DispayFeatures()
{
    int choice;
    while (true)
    {
        cout << "\nSelect an option:\n\n";
        cout << " 1. Student login\n";
        cout << " 2. Admin login\n";
        cout << "\nInput (1 - 2):  ";
        cin >> choice;

        if (choice < 1 || choice > 2)
        {
            cout << "\033[31m\nInvalid input, please try again.\n\033[0m";
        }
        else
        {
            return choice;
        }
    }
}

int main()
{
    cout << "\033[40m\033[1;33m\t=-=-=-=-=-=-=-=-=-=-=-=\n\t|  HOSTEL MANAGEMENT  |\n\t=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n";

    int maleStudents = 0, femaleStudents = 0, totalStudents = 0;
    const int maxStudents = 750;
    string students[12][maxStudents];
    ReadArray(students, maleStudents, femaleStudents, totalStudents);
    int currentAccount = LoginAccount(DisplayLoginChoice(), (string *)students, maxStudents);
    int p = DispayFeatures();

    // [0 = Name] [1 = Reg] [2 = Gender] [3 = Age] [4 = CNIC] [5 = Program] [6 = Section]
    // [7 = Password] [8 = Contact] [9 = Emergency Contact] [10 = Hostel] [11 = Room Number]

    cout << "Total Students: " << totalStudents << endl;
    cout << "Male Students: " << maleStudents << endl;
    cout << "Female Students: " << femaleStudents << endl;

    return 0;
}
