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

int main()
{
    // Black background with yellow text
    cout << "\033[40m\033[1;33m\t=-=-=-=-=-=-=-=-=-=-=-=\n\t*  HOSTEL MANAGEMENT  *\n\t=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n";

    int choice;
    while (true)
    {
        cout << "\nSelect an Option:\n\n";
        cout << " 1. Option 1\n";
        cout << " 2. Option 2\n";
        cout << " 3. Option 3\n";
        cout << "\nInput (1 - 3):  ";
        cin >> choice;

        if (choice < 1 || choice > 3)
        {
            cout << "\nInvalid input, please try again.\n";
        }
        else
        {
            break; 
        }
    }

    int maleStudents = 0, femaleStudents = 0, totalStudents = 0;
    const int maxStudents = 750;
    string students[12][maxStudents];
    ReadArray(students, maleStudents, femaleStudents, totalStudents);

    // [0 = Name] [1 = Reg] [2 = Gender] [3 = Age] [4 = CNIC] [5 = Program] [6 = Section]
    // [7 = Password] [8 = Contact] [9 = Emergency Contact] [10 = Hostel] [11 = Room Number]

    cout << "Total Students: " << totalStudents << endl;
    cout << "Male Students: " << maleStudents << endl;
    cout << "Female Students: " << femaleStudents << endl;

    return 0;
}
