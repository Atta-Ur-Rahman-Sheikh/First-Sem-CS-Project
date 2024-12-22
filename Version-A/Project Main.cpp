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

string IntToString(int n)
{
    stringstream ss;
    ss << n;
    return ss.str();
}

void ReadArray(string students[][800], int &maleStudents, int &femaleStudents, int &totalStudents)
{
    ifstream studentFile("Student_Data.txt");
    if (!studentFile)
    {
        cerr << "Student File can't be Opened!";
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

void AllotHostels(string students[][800], int totalStudents)
{
    const int maleHostelCapacity = 650;
    const int femaleHostelCapacity = 150;
    const int roomCapacity = 2;

    int maleCount = 0, femaleCount = 0;

    ofstream studentFile("Updated_Student_Data.txt");
    if (!studentFile)
    {
        cerr << "\033[31m\nUnable to write to the file!\033[0m";
        return;
    }

    for (int i = 0; i < totalStudents; i++)
    {
        if (students[2][i] == "M")
        {
            if (maleCount < maleHostelCapacity)
            {
                string hostel;
                if (maleCount < 325 * roomCapacity)
                {
                    hostel = "H11";
                }
                else
                {
                    hostel = "H12";
                }
                int roomNumber = (maleCount / roomCapacity) % 325 + 1;
                students[10][i] = hostel;
                students[11][i] = IntToString(roomNumber);
                maleCount++;
            }
            else
            {
                cerr << "\033[31m\nNo available rooms for male students.\n\033[0m";
            }
        }
        else if (students[2][i] == "F")
        {
            if (femaleCount < femaleHostelCapacity)
            {
                students[10][i] = "GH";
                students[11][i] = IntToString(femaleCount / roomCapacity + 1);
                femaleCount++;
            }
            else
            {
                cerr << "\033[31m\nNo available rooms for female students.\n\033[0m";
            }
        }
        studentFile << "Name: " << students[0][i] << "\n";
        studentFile << "Reg: " << students[1][i] << "\n";
        studentFile << "Gender: " << students[2][i] << "\n";
        studentFile << "Age: " << students[3][i] << "\n";
        studentFile << "CNIC: " << students[4][i] << "\n";
        studentFile << "Program: " << students[5][i] << "\n";
        studentFile << "Section: " << students[6][i] << "\n";
        studentFile << "Account Password: " << students[7][i] << "\n";
        studentFile << "Contact: " << students[8][i] << "\n";
        studentFile << "Emergency Contact: " << students[9][i] << "\n";
        studentFile << "Hostel: " << students[10][i] << "\n";
        studentFile << "Room Number: " << students[11][i] << "\n";
        studentFile << "---\n";
    }

    studentFile.close();
    cout << "\033[32m\nHostel allocation completed successfully!\033[0m\n";
}

int DisplayLoginChoice()
{
    int choice;
    while (true)
    {
        cout << "\nSelect an option:\n\n\033[40m\033[1;33m";
        cout << " 1. Student login\n";
        cout << " 2. Admin login\033[0m\n";
        cout << "\nInput (1 - 2): ";
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
        bool reg = false;
        do
        {
            cout << "\nEnter Registration Number: ";
            cin >> regNo;
            for (int i = 0; i < maxStudents; i++)
            {
                if (*(students + 1 * maxStudents + i) == regNo)
                {
                    reg = true;
                    do
                    {
                        cout << "Enter Password: ";
                        cin >> password;
                        if (*(students + 7 * maxStudents + i) == password)
                        {
                            return i;
                        }
                        else
                        {
                            cout << "\033[31m\nInvalid password, please try again.\n\n\033[0m";
                        }
                    } while (true);
                }
            }
            cout << "\033[31m\nInvalid registration number, please try again.\n\033[0m";
        } while (!reg);
    }
    else if (choice == 2)
    {
        cout << "\n[ADMIN LOGIN]\n";
    }
}

void DisplayStudentProfile(string *students, int maxStudents, int currentAccount)
{
    string name = "\033[1;36m" + *(students + 0 * maxStudents + currentAccount) + "\033[0m";
    cout << "This is your profile, "<<name<<".\n";
    cout << "If there is an error or you need to update your info, contact the IT Department for assistance." ;

    cout "MY PROFILE"
}

void DispayStudentFeatures(string *students, int maxStudents, int currentAccount)
{
    string name = "\033[1;36m" + *(students + 0 * maxStudents + currentAccount) + "\033[0m";
    // cout << "\033[1;36mCYAN\033[0m\n";
    cout << "\nWelcome, " << name << "! Explore the features below to manage your hostel life easily and efficiently.\n";

    int choice;
    while (true)
    {
        cout << "\nSelect an option:\n\n\033[40m\033[1;33m";
        cout << " 1. My Profile\n";
        cout << " 2. Hostel Overview\n";
        cout << " 3. Change Password\n";
        cout << " 4. Room Transfer Request\n";
        cout << " 5. Parcel Alerts\n";
        cout << " 6. My Notifications\n";
        cout << " 7. Admin Announcements\n";
        cout << " 8. Complaint Tracker\n";
        cout << " 9. Log Out\033[0m\n";
        cout << "\nInput (1 - 9):  ";
        cin >> choice;

        if (choice < 1 || choice > 9)
        {
            cout << "\033[31m\nInvalid input, please try again.\n\033[0m";
        }
        else
        {
            break;
        }
    }
    switch (choice)
    {
    case 1:
        DisplayStudentProfile((string *)students, maxStudents, currentAccount);
        break;

    default:
        break;
    }
}

void printColors()
{
    cout << "\033[1;30mBLACK\033[0m\n";
    cout << "\033[1;31mRED\033[0m\n";
    cout << "\033[1;32mGREEN\033[0m\n";
    cout << "\033[1;33mYELLOW\033[0m\n";
    cout << "\033[1;34mBLUE\033[0m\n";
    cout << "\033[1;35mMAGENTA\033[0m\n";
    cout << "\033[1;36mCYAN\033[0m\n";
    cout << "\033[1;37mWHITE\033[0m\n\n";

    cout << "\033[40m\033[1;30mBLACK ON BLACK\033[0m\n";
    cout << "\033[41m\033[1;31mRED ON RED\033[0m\n";
    cout << "\033[42m\033[1;32mGREEN ON GREEN\033[0m\n";
    cout << "\033[43m\033[1;33mYELLOW ON YELLOW\033[0m\n";
    cout << "\033[44m\033[1;34mBLUE ON BLUE\033[0m\n";
    cout << "\033[45m\033[1;35mMAGENTA ON MAGENTA\033[0m\n";
    cout << "\033[46m\033[1;36mCYAN ON CYAN\033[0m\n";
    cout << "\033[47m\033[1;37mWHITE ON WHITE\033[0m\n\n";

    cout << "\033[100m\033[1;30mBLACK ON BRIGHT BLACK\033[0m\n";
    cout << "\033[101m\033[1;31mRED ON BRIGHT RED\033[0m\n";
    cout << "\033[102m\033[1;32mGREEN ON BRIGHT GREEN\033[0m\n";
    cout << "\033[103m\033[1;33mYELLOW ON BRIGHT YELLOW\033[0m\n";
    cout << "\033[104m\033[1;34mBLUE ON BRIGHT BLUE\033[0m\n";
    cout << "\033[105m\033[1;35mMAGENTA ON BRIGHT MAGENTA\033[0m\n";
    cout << "\033[106m\033[1;36mCYAN ON BRIGHT CYAN\033[0m\n";
    cout << "\033[107m\033[1;37mWHITE ON BRIGHT WHITE\033[0m\n";
}

int main()
{
    printColors();
    cout << "\033[40m\033[1;33m\t=-=-=-=-=-=-=-=-=-=-=-=\n\t|  HOSTEL MANAGEMENT  |\n\t=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n";

    // cout << "\033[1;32mGREEN\033[0m\n";
    // cout << "\033[1;36mCYAN\033[0m\n";
    // cout << "\033[1;34mBLUE\033[0m\n\n";

    int maleStudents = 0, femaleStudents = 0, totalStudents = 0;
    const int maxStudents = 800;
    string students[12][maxStudents];
    ReadArray(students, maleStudents, femaleStudents, totalStudents);

    AllotHostels(students, totalStudents);

    int currentAccount = LoginAccount(DisplayLoginChoice(), (string *)students, maxStudents);
    DispayStudentFeatures((string *)students, maxStudents, currentAccount);

    // [0 = Name] [1 = Reg] [2 = Gender] [3 = Age] [4 = CNIC] [5 = Program] [6 = Section]
    // [7 = Password] [8 = Contact] [9 = Emergency Contact] [10 = Hostel] [11 = Room Number]

    cout << "\nTotal Students: " << totalStudents << endl;
    cout << "Male Students: " << maleStudents << endl;
    cout << "Female Students: " << femaleStudents << endl;

    return 0;
}
