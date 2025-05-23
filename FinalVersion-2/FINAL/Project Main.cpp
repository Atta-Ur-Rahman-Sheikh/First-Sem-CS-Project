#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int StringToInt(string);
string IntToString(int);
void ReadArray(string[][800], int &, int &, int &);
void AllotHostels(string[][800], int);
int DisplayLoginChoice();
int LoginAccount(int, string *, int);
void DisplayStudentFeatures(string *, int, int);
void DisplayStudentProfile(string *, int, int);
void DisplayStudentHostelOverview(string *, int, int);
void StudentChangePassword(string *, int, int);
void StudentRoomTransferRequest(string *, int, int);
void StudentParcelAlerts(string *, int, int);
void StudentNotifications(string *, int, int);
void StudentReadsAdminAnnouncements(string *, int, int);
void StudentComplainTracker(string *, int, int);
void DisplayAdminFeatures(string *, int, int &);

void AdminChangePassword(string *, int, int &);
void AdminComplainManagement(string *, int, int &);
void AdminNotifications(string *, int, int &);
void AdminAnnouncements(string *, int, int &);
void AdminRoomSwapRequests(string *, int, int &);
void AdminAddStudent(string *, int, int &);
void SearchStudent(string *, int, int &);
void GenerateReport(string *, int, int &, int, int);

string adminMasterKey = "8888";
int maleStudents = 0, femaleStudents = 0;

int main()
{
    // ADMIN MASTER KEY: 8888
    system("");
    cout << "\033[1;33m\t=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\t|  GIK HOSTEL MANAGEMENT  |\n\t=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n";

    int totalStudents = 0;
    const int maxStudents = 800;
    string students[12][maxStudents];
    ReadArray(students, maleStudents, femaleStudents, totalStudents);

    AllotHostels(students, totalStudents);

    int currentAccount = LoginAccount(DisplayLoginChoice(), (string *)students, maxStudents);
    system("cls");

    if (currentAccount == -100)
    {
        return 0;
    }
    else if (currentAccount == -5)
    {
        DisplayAdminFeatures((string *)students, maxStudents, totalStudents);
    }
    else
    {
        DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
    }

    // [0 = Name] [1 = Reg] [2 = Gender] [3 = Age] [4 = CNIC] [5 = Program] [6 = Section]
    // [7 = Password] [8 = Contact] [9 = Emergency Contact] [10 = Hostel] [11 = Room Number]

    return 0;
}

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
    const int peoplePerRoom = 2;

    int maleCount = 0, femaleCount = 0;

    ofstream studentFile("Updated_Student_Data.txt");
    if (!studentFile)
    {
        cerr << "\033[1;31m\nUnable to write to the file!\033[0m";
        return;
    }

    for (int i = 0; i < totalStudents; i++)
    {
        if (students[2][i] == "M")
        {
            if (maleCount < maleHostelCapacity)
            {
                string hostel;
                if (maleCount < 163 * peoplePerRoom)
                {
                    hostel = "H11";
                }
                else
                {
                    hostel = "H12";
                }
                int roomNumber = (maleCount / peoplePerRoom) % 163 + 1;
                students[10][i] = hostel;
                students[11][i] = IntToString(roomNumber);
                maleCount++;
            }
            else
            {
                cerr << "\033[1;31m\nNo available rooms for male students.\n\033[0m";
            }
        }
        else if (students[2][i] == "F")
        {
            if (femaleCount < femaleHostelCapacity)
            {
                students[10][i] = "GH";
                students[11][i] = IntToString(femaleCount / peoplePerRoom + 1);
                femaleCount++;
            }
            else
            {
                cerr << "\033[1;31m\nNo available rooms for female students.\n\033[0m";
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
        cout << " 2. Admin login\n";
        cout << " 3. Exit\033[0m\n";
        cout << "\nInput (1 - 3): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 3)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "\033[1;31m\nInvalid input, please try again.\n\033[0m";
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
                            cout << "\033[1;31m\nInvalid password, please try again.\n\n\033[0m";
                        }
                    } while (true);
                }
            }
            cout << "\033[1;31m\nInvalid registration number, please try again.\n\033[0m";
        } while (!reg);
    }
    else if (choice == 2)
    {
        string pass;
        do
        {
            cout << "\nEnter Password: ";
            cin >> pass;
            if (pass == adminMasterKey)
            {
                return -5;
            }
            else
            {
                cout << "\033[1;31m\nInvalid password, please try again.\n\033[0m";
            }

        } while (true);
    }
    else if (choice == 3)
    {
        return -100;
    }
}

void DisplayStudentFeatures(string *students, int maxStudents, int currentAccount)
{
    system("cls");
    string name = "\033[1;3;36m" + *(students + 0 * maxStudents + currentAccount) + "\033[0m";
    // cout << "\033[1;3;36mCYAN\033[0m\n";
    cout << "\nWelcome, " << name << "! Explore the features below to manage your hostel life easily and efficiently.\n";
    int totalStudents = 697;
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
        cout << "\nInput (1 - 9): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 9)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "\033[1;31m\nInvalid input, please try again.\n\033[0m";
        }
        else
        {
            break;
        }
    }
    system("cls");

    switch (choice)
    {
    case 1:
        DisplayStudentProfile((string *)students, maxStudents, currentAccount);
        break;
    case 2:
        DisplayStudentHostelOverview((string *)students, maxStudents, currentAccount);
        break;
    case 3:
        StudentChangePassword((string *)students, maxStudents, currentAccount);
        break;
    case 4:
        StudentRoomTransferRequest((string *)students, maxStudents, currentAccount);
        break;
    case 5:
        StudentParcelAlerts((string *)students, maxStudents, currentAccount);
        break;
    case 6:
        StudentNotifications((string *)students, maxStudents, currentAccount);
        break;
    case 7:
        StudentReadsAdminAnnouncements((string *)students, maxStudents, currentAccount);
        break;
    case 8:
        StudentComplainTracker((string *)students, maxStudents, currentAccount);
        break;
    case 9:
        int currentAccount = LoginAccount(DisplayLoginChoice(), (string *)students, maxStudents);
        if (currentAccount == -100)
        {
            break;
        }
        else if (currentAccount == -5)
        {
            DisplayAdminFeatures((string *)students, maxStudents, totalStudents);
        }
        else
        {
            DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
        }
        break;
    }
}

void DisplayStudentProfile(string *students, int maxStudents, int currentAccount)
{
    string name = "\033[1;3;36m" + *(students + 0 * maxStudents + currentAccount) + "\033[0m";
    cout << "\nThis is your profile, " << name << ".\n";
    cout << "If there is an error or you need to update your info, contact the IT Department for assistance.";

    cout << "\n\n\033[40m\033[1;33mMY PROFILE: \033[0m\n\n";
    cout << " Name: \033[1;3;36m" << *(students + 0 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Reg: \033[1;3;36m" << *(students + 1 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Program: \033[1;3;36m" << *(students + 5 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Section: \033[1;3;36m" << *(students + 6 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Gender: \033[1;3;36m" << *(students + 2 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Age: \033[1;3;36m" << *(students + 3 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " CNIC: \033[1;3;36m" << *(students + 4 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Contact: \033[1;3;36m" << *(students + 8 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Emergency Contact : \033[1;3;36m" << *(students + 9 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Email: \033[1;3;36mu" << *(students + 1 * maxStudents + currentAccount) << "@giki.edu.pk\033[0m\n";
    cout << " Account Password: \033[1;3;36m" << *(students + 7 * maxStudents + currentAccount) << "\033[0m\n";

    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
}

void DisplayStudentHostelOverview(string *students, int maxStudents, int currentAccount)
{
    cout << "\n\033[40m\033[1;33mHOSTEL OVERVIEW: \033[0m\n\n";

    cout << " Hostel: \033[1;3;36m" << *(students + 10 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Room Number: \033[1;3;36m" << *(students + 11 * maxStudents + currentAccount) << "\033[0m\n";

    string currentHostel = *(students + 10 * maxStudents + currentAccount);
    string currentRoom = *(students + 11 * maxStudents + currentAccount);

    bool single = true;

    for (int i = 0; i < maxStudents; i++)
    {
        if (*(students + 10 * maxStudents + i) == currentHostel && *(students + 11 * maxStudents + i) == currentRoom && i != currentAccount)
        {
            cout << "\n\n\033[40m\033[1;33mROOMMATE DETAILS: \033[0m\n\n";
            cout << " Name: \033[1;3;36m" << *(students + 0 * maxStudents + i) << "\033[0m\n";
            cout << " Reg No: \033[1;3;36m" << *(students + 1 * maxStudents + i) << "\033[0m\n";
            cout << " Program: \033[1;3;36m" << *(students + 5 * maxStudents + i) << "\033[0m\n";
            cout << " Contact: \033[1;3;36m" << *(students + 8 * maxStudents + i) << "\033[0m\n";
            single = false;
        }
    }
    if (single)
    {
        cout << " No Roommate\n";
    }

    cout << "\n\n\033[40m\033[1;33mCONTACT INFORMATION: \033[0m\n\n";

    if (currentHostel == "H11")
    {
        cout << " Hostel 11 Warden: \033[1;3;36m0311-0011011\033[0m\n";
        cout << " Email: \033[1;3;36mhostel11@giki.edu.pk\033[0m\n";
        cout << " Emergency Contact: \033[1;3;36m0300-1108011\033[0m\n";
    }
    else if (currentHostel == "H12")
    {
        cout << " Hostel 12 Warden: \033[1;3;36m0312-0012012\033[0m\n";
        cout << " Email: \033[1;3;36mhostel12@giki.edu.pk\033[0m\n";
        cout << " Emergency Contact: \033[1;3;36m0300-1208012\033[0m\n";
    }
    else
    {
        cout << " Girls Hostel Warden: \033[1;3;36m0353-0053053\033[0m\n";
        cout << " Email: \033[1;3;36mgirlshostel@giki.edu.pk\033[0m\n";
        cout << " Emergency Contact: \033[1;3;36m0300-5308053\033[0m\n";
    }

    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
}

void StudentChangePassword(string *students, int maxStudents, int currentAccount)
{
    cout << "\n\n\033[40m\033[1;33mCHANGE PASSWORD: \033[0m\n\n";

    string pass = *(students + 7 * maxStudents + currentAccount);
    string inputPassword, newPass;

    cout << "Enter current password: ";
    cin >> inputPassword;

    if (inputPassword != pass)
    {
        cout << "\033[1;31m\nIncorrect password. Returning to main menu.\033[0m\n";
        DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
    }
    else
    {
        cout << "Enter new password: ";
        cin >> newPass;
        if (newPass.empty())
        {
            cout << "\033[1;31mPassword cannot be empty.\033[0m\n";
        }
        else
        {
            *(students + 7 * maxStudents + currentAccount) = newPass;
            cout << "\033[32m\nPassword changed successfully!\033[0m\n";
        }

        cout << "\nPress Enter to return to Main Menu.";
        cin.ignore();
        cin.get();
        DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
    }
}

void StudentRoomTransferRequest(string *students, int maxStudents, int currentAccount)
{
    cout << "\n\033[40m\033[1;33mROOM TRANSFER REQUEST: \033[0m\n\n";

    string reg;
    string request = *(students + 1 * maxStudents + currentAccount) + " wants to swap rooms with you.";
    cout << "Enter registration number of the student you want to swap rooms with: ";
    cin >> reg;
    ofstream file("notification.txt", ios::app);
    file<<reg<<" "<<request<<"\n";
    file.close();

    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
}

void StudentParcelAlerts(string *students, int maxStudents, int currentAccount)
{
    cout << "\n\033[40m\033[1;33mPARCEL ALERTS: \033[0m\n\n";

    string reg = *(students + 1 * maxStudents + currentAccount);
    string file_user, complain;
    fstream file("parasal.txt", ios::in);

    if (!file.is_open())
    {
        cout << "Error: The file is not loaded." << endl;
        return;
    }
    int found = 0;
    while (file.good())
    {
        file >> file_user;
        if (file_user == reg)
        {
            getline(file, complain);
            cout << complain << endl;
            found = found + 1;
        }
        getline(file, complain);
    }

    if (found == 0)
    {
        cout << "\033[32mNo Parcels.\033[0m" << endl;
    }

    file.close();
    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
}

void StudentNotifications(string *students, int maxStudents, int currentAccount)
{
    string reg = *(students + 1 * maxStudents + currentAccount);
    cout << "\n\033[40m\033[1;33mNOTIFICATIONS: \033[0m\n\n";
    string file_user, complain;
    fstream file("notification.txt", ios::in);

    if (!file.is_open())
    {
        cout << "Error: The file is not loaded." << endl;
        return;
    }
    int found = 0;
    while (file.good())
    {
        file >> file_user;
        if (file_user == reg)
        {
            getline(file, complain);
            cout << complain << endl;
            found = found + 1;
        }
        getline(file, complain);
    }

    if (found == 0)
    {
        cout << "\033[32mNo Notifications.\033[0m" << endl;
    }

    file.close();
    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
}

void StudentReadsAdminAnnouncements(string *students, int maxStudents, int currentAccount)
{

    cout << "\n\033[40m\033[1;33mCOMPLAINT MANAGEMENT: \033[0m\n";

    string announcements;
    fstream file("announcements.txt", ios::in);

    if (!file.is_open())
    {
        cout << "Error: The file is not loaded." << endl;
        return;
    }

    int found = 0;
    cout << "\033[1;3;36m" << endl;

    while (getline(file, announcements))
    {
        if (!announcements.empty())
        {
            cout << announcements << endl;
            found++;
        }
    }
    cout << "\033[0m";
    if (found == 0)
    {
        cout << "\033[0m\033[32m\n No Announcement.\n\033[0m" << endl;
    }

    file.close();
    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
}

void StudentComplainTracker(string *students, int maxStudents, int currentAccount)
{
    int choice;
    do
    {
        cout << "\n\033[40m\033[1;33mCOMPLAINT MANAGER: \033[0m\n\n";

        cout << " 1: Track your old Complaint\n";
        cout << " 2: Submit new Complaint\n";
        cout << " 3: Exit\n";
        cout << "\nInput (1 - 3): ";
        cin >> choice;
        string reg = *(students + 1 * maxStudents + currentAccount);
        if (choice == 1)
        {
            cout << "\n\n\033[40m\033[1;33mCOMPLAINT TRACKING: \033[0m\n\n";
            string file_user, complain;
            fstream file("complaint.txt", ios::in);

            if (!file.is_open())
            {
                cout << "Error: The file is not loaded." << endl;
                return;
            }
            int found = 0;
            while (file.good())
            {
                file >> file_user;
                if (file_user == reg)
                {
                    getline(file, complain);
                    cout << "Pending Complaint: \033[1;3;36m" << complain << "\033[0m" << endl;
                    found = found + 1;
                }
                getline(file, complain);
            }

            if (found == 0)
            {
                cout << "\033[32mNo pending complaints.\033[0m" << endl;
            }

            file.close();
        }
        else if (choice == 2)
        {
            cout << "\n\033[40m\033[1;33mNEW COMPLAINT: \033[0m\n\n";
            string complain;
            ofstream file("complaint.txt", ios::app);
            if (!file.is_open())
            {
                cout << "Error the file is not loaded" << endl;
                return;
            }
            cout << "Enter Complaint: ";
            cin.ignore();
            getline(cin, complain);
            file << reg << " " << complain << "\n";
            file.close();
        }
        else if (choice == 3)
            break;
    } while (true);
    DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
}

void DisplayAdminFeatures(string *students, int maxStudents, int &totalStudents)
{
    system("cls");

    string name = "\033[1;3;36mAdmin\033[0m";
    // cout << "\033[1;3;36mCYAN\033[0m\n";
    cout << "\nWelcome, " << name << "! Please choose an action from the menu below.\n";

    int choice;
    while (true)
    {
        cout << "\nSelect an option:\n\n\033[40m\033[1;33m";
        cout << " 1. Change Password\n";
        cout << " 2. Add New Student\n";
        cout << " 3. Search Students\n";
        cout << " 4. Manage Room Swap Requests\n";
        cout << " 5. Complaint Management\n";
        cout << " 6. Send Notifications to Students\n";
        cout << " 7. Make Announcements\n";
        cout << " 8. Generate Reports\n";
        cout << " 9. Log Out\033[0m\n";
        cout << "\nInput (1 - 9): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 9)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "\033[1;31m\nInvalid input, please try again.\n\033[0m";
        }
        else
        {
            break;
        }
    }
    system("cls");

    switch (choice)
    {
    case 1:
        AdminChangePassword(students, maxStudents, totalStudents);
        break;
    case 2:
        AdminAddStudent(students, maxStudents, totalStudents);
        break;
    case 3:
        SearchStudent(students, maxStudents, totalStudents);
        break;
    case 4:
        AdminRoomSwapRequests(students, maxStudents, totalStudents);
        break;
    case 5:
        AdminComplainManagement(students, maxStudents, totalStudents);
        break;
    case 6:
        AdminNotifications(students, maxStudents, totalStudents);
        break;
    case 7:
        AdminAnnouncements(students, maxStudents, totalStudents);
        break;
    case 8:
        GenerateReport(students, maxStudents, totalStudents, maleStudents, femaleStudents);
        break;
    case 9:
        int currentAccount = LoginAccount(DisplayLoginChoice(), (string *)students, maxStudents);
        if (currentAccount == -100)
        {
            break;
        }
        else if (currentAccount == -5)
        {
            DisplayAdminFeatures((string *)students, maxStudents, totalStudents);
        }
        else
        {
            DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
        }
        break;
    }
}

void AdminChangePassword(string *students, int maxStudents, int &totalStudents)
{
    cout << "\n\033[40m\033[1;33mCHANGE PASSWORD: \033[0m\n";
    string newPass;
    cout << "\nEnter New Passwaord: ";
    cin >> newPass;
    if (newPass.empty())
    {
        cout << "\033[1;31mPassword cannot be empty.\033[0m\n";
    }
    else
    {
        adminMasterKey = newPass;
        cout << "\033[32m\nPassword changed successfully!\033[0m\n";
    }
    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayAdminFeatures(students, maxStudents, totalStudents);
}

void AdminAddStudent(string *students, int maxStudents, int &totalStudents)
{
    cout << "\n\033[40m\033[1;33mADD STUDENT: \033[0m\n";

    bool cond;
    fstream studentFile;
    string regNo, name, gender, age, program, section, accountPassword, contact, emergencyContact, cnic;
    accountPassword = "1";
    do
    {
        cond = true;
        cout << "\nName of new student (ONLY BLOCK LETTERS!) : ";
        cin.ignore();
        getline(cin, name);
        for (int i = 0; i < name.length(); i++)
        {
            if ((name[i] < 65 || name[i] > 90) && name[i] != 32)
            {
                cout << "\nBLOCK LETTERS ONLY!!" << endl;
                cond = false;
                break;
            }
        }
        if (cond == false)
            continue;
        cout << "Enter Reg No of new student: ";
        cin >> regNo;
        for (int i = 0; i < maxStudents; i++)
        {
            if (regNo == *(students + 1 * maxStudents + i))
            {
                cout << "\nThis Registration number already exists" << endl;
                cond = false;
                break;
            }
        }
        if (cond == false)
            continue;
        ;
        cout << "Gender of new student (M/F) : ";
        cin >> gender;
        if (gender != "M" && gender != "F")
        {
            cout << "\nInvalid Entry!!" << endl;
            cond = false;
            continue;
        }
        cout << "Age of student: ";
        cin >> age;
        cnic = "55889-3735446-9";
        cout << "Program of student: ";
        cin >> program;
        cout << "Section student: ";
        cin >> section;
        if ((section[0] < 65 || section[0] > 90))
        {
            cout << "\nBLOCK LETTERS ONLY!!" << endl;
            cond = false;
            continue;
        }
        for (int i = 0; i < regNo.length(); i++)
        {
            if (i < 3)
            {
                accountPassword += regNo[i];
            }
        }
        contact = "+923535267049";
        emergencyContact = "+923535267049";
        string data[12] = {regNo, name, gender, age, program, section, accountPassword, contact, emergencyContact, cnic, "Empty", "Empty"};
        for (int j = 0; j < 12; j++)
        {
            *(students + j * maxStudents + (totalStudents + 1)) = data[j];
        }
    } while (cond == false);
    studentFile.open("Student_Data.txt", ios::app);
    studentFile << "Name: " << name << endl;
    studentFile << "Reg No: " << regNo << endl;
    studentFile << "Gender: " << gender << endl;
    studentFile << "Program: " << program << endl;
    studentFile << "Section: " << section << endl;
    studentFile << "Age :" << age << endl;
    studentFile << "Account Password :" << accountPassword << endl;
    studentFile << "Contact: " << contact << endl;
    studentFile << "Emergency Contact: " << emergencyContact << endl;
    studentFile << "CNIC: " << cnic << endl;
    studentFile << "Hostel: " << cnic << endl;
    studentFile << "Room: " << cnic << endl;
    studentFile << "---" << endl; //
    studentFile.close();

    totalStudents += 1;

    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayAdminFeatures(students, maxStudents, totalStudents);
}

void AdminComplainManagement(string *students, int maxStudents, int &totalStudents)
{
    cout << "\n\033[40m\033[1;33mCOMPLAINT MANAGEMENT: \033[0m\n";

    string complain;
    fstream file("complaint.txt", ios::in);

    if (!file.is_open())
    {
        cout << "Error: The file is not loaded." << endl;
        return;
    }

    int found = 0;
    cout << "\nPending complaints:\n\033[1;3;36m" << endl;

    while (getline(file, complain))
    {
        if (!complain.empty())
        {
            cout << complain << endl;
            found++;
        }
    }
    cout << "\033[0m";
    if (found == 0)
    {
        cout << "\033[0m\033[32m\nNo pending complaints found for the user.\n\033[0m" << endl;
    }

    file.close();
    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayAdminFeatures(students, maxStudents, totalStudents);
}

void AdminNotifications(string *students, int maxStudents, int &totalStudents)
{
    cout << "\n\033[40m\033[1;33mNEW NOTIFICATION \033[0m\n\n";
    string complain;
    string reg;
    cout << "Enter you Rsgister No: ";
    cin.ignore();
    getline(cin, reg);
    ofstream file("notification.txt", ios::app);
    if (!file.is_open())
    {
        cout << "Error the file is not loaded" << endl;
        return;
    }
    cout << "Enter your Notification: ";
    getline(cin, complain);
    file << reg << " " << complain << "\n";
    file.close();
    cout << "\nPress Enter to return to Main Menu.";
    cin.get();
    DisplayAdminFeatures(students, maxStudents, totalStudents);
}

void AdminRoomSwapRequests(string *students, int maxStudents, int &totalStudents)
{
    string regNo1, regNo2;
    cout << "\n\033[40m\033[1;33mROOM SWAP REQUEST: \033[0m\n";

    // Get the registration numbers of the two students who want to swap rooms
    cout << "\nEnter Registration Number of the first student: ";
    cin >> regNo1;
    cout << "Enter Registration Number of the second student: ";
    cin >> regNo2;

    int student1Index = -1, student2Index = -1;

    // Find the indices of the two students in the data array
    for (int i = 0; i < totalStudents; i++)
    {
        if (*(students + 1 * maxStudents + i) == regNo1)
        {
            student1Index = i;
        }
        else if (*(students + 1 * maxStudents + i) == regNo2)
        {
            student2Index = i;
        }

        if (student1Index != -1 && student2Index != -1)
            break;
    }

    if (student1Index == -1 || student2Index == -1)
    {
        cout << "\033[1;31mOne or both registration numbers not found. Returning to menu.\033[0m\n";
        return;
    }

    // Swap the room data between the two students
    string tempRoom = *(students + 10 * maxStudents + student1Index);  // Room of student 1
    *(students + 10 * maxStudents + student1Index) = *(students + 10 * maxStudents + student2Index); // Room of student 2
    *(students + 10 * maxStudents + student2Index) = tempRoom;  // Room of student 1 now in student 2

    // Update the data in the text file
    fstream file("Student_Data.txt", ios::in | ios::out);
    if (!file.is_open())
    {
        cout << "\033[1;31mError opening file.\033[0m\n";
        return;
    }

    string line;
    string updatedData1, updatedData2;

    // Find the student 1's and student 2's information and swap their room info
    int count = 0;
    while (getline(file, line))
    {
        if (line.find("Reg No: " + regNo1) != string::npos)
        {
            updatedData1 = line;
            for (int i = 0; i < 10; i++)
            {
                getline(file, line);
                if (i == 9)  // This is the Room line
                {
                    line = "Room: " + *(students + 10 * maxStudents + student2Index);
                }
                updatedData1 += "\n" + line;
            }
        }
        else if (line.find("Reg No: " + regNo2) != string::npos)
        {
            updatedData2 = line;
            for (int i = 0; i < 10; i++)
            {
                getline(file, line);
                if (i == 9)  // This is the Room line
                {
                    line = "Room: " + *(students + 10 * maxStudents + student1Index);
                }
                updatedData2 += "\n" + line;
            }
        }
        count++;
    }

    // Close the file and write the new data
    file.clear();  // Clear EOF flag
    file.seekg(0, ios::beg);  // Rewind the file pointer

    // Rewriting the file with the swapped room information
    ofstream outFile("Student_Data.txt", ios::trunc);
    outFile << updatedData1 << "\n" << updatedData2;
    outFile.close();

    cout << "\n\033[32mRoom swap successful.\033[0m\n";
    cout << "\nPress Enter to return to Main Menu.";
    cin.get();
    DisplayAdminFeatures(students, maxStudents, totalStudents);
}


void AdminAnnouncements(string *students, int maxStudents, int &totalStudents)
{
    cout << "\n\033[40m\033[1;33mANNOUNCEMENT: \033[0m\n\n";
    string announcement;
    ofstream file("announcements.txt", ios::app);
    if (!file.is_open())
    {
        cout << "Error the file is not loaded" << endl;
        return;
    }
    cout << "Enter your Announcement: ";
    cin.ignore();
    getline(cin, announcement);
    file << announcement << "\n";
    file.close();
    DisplayAdminFeatures(students, maxStudents, totalStudents);
}

void GenerateReport(string *students, int maxStudents, int &totalStudents, int maleStudents, int femaleStudents)
{
    cout << "\n\033[40m\033[1;33mREPORT: \033[0m\n";

    int hostelEleven = 0, hostelTwelve = 0, maxCapacity = 325;
    cout << "\n Total Number of Students are: \033[1;3;36m" << totalStudents << "\033[0m" << endl;
    cout << " Number of Male Students are: \033[1;3;36m" << maleStudents << "\033[0m" << endl;
    cout << " Number of Female Students are: \033[1;3;36m" << femaleStudents << "\033[0m" << endl;
    cout << " \n Maximum Hostel Capacity: \033[1;3;36m" << maxStudents << "\033[0m" << endl;
    for (int i = 0; i < totalStudents; i++)
    {
        if (*(students + 10 * maxStudents + i) == "H11")
        {
            hostelEleven += 1;
        }
        else if (*(students + 10 * maxStudents + i) == "H12")
        {
            hostelTwelve += 1;
        }
    }
    cout << " \n Hostel 11 Maximum Capacity: \033[1;3;36m" << maxCapacity << "\033[0m" << endl;
    cout << " No. of Students in Hotel 11: \033[1;3;36m" << hostelEleven << "\033[0m" << endl;
    cout << " \n Hostel 12 Maximum Capacity: \033[1;3;36m" << maxCapacity << "\033[0m" << endl;
    cout << " No. of Students in Hotel 12: \033[1;3;36m" << hostelTwelve << "\033[0m" << endl;

    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayAdminFeatures(students, maxStudents, totalStudents);
}

void SearchStudent(string *students, int maxStudents, int &totalStudents)
{
    string data[12] = {"Name: ", "Reg: ", "Gender: ", "Age: ", "CNIC: ", "Program: ", "Section: ", "Account Password: ", "Contact: ", "Emergency Contact: ", "Hostel: ", "Room: "};
    int option, index;
    bool display = false;
    string regNo, roomNumber;
    int i;
    cout << "\nEnter Registration Number: ";
    cin >> regNo;
    for (i = 0; i < totalStudents; i++)
    {
        if (*(students + 1 * maxStudents + i) == regNo)
        {
            cout << "\n\033[40m\033[1;33mDETAILS: \033[0m"
                 << endl;
            for (int j = 0; j < 12; j++)
            {
                cout << endl
                     << data[j] << "\033[1;3;36m" << *(students + j * maxStudents + i) << "\033[0m";
            }
            break;
        }
        else if (i >= totalStudents - 1)
        {
            cout << "\nNo student found with matching registration number!!";
        }
    }
    cout << "\n\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayAdminFeatures(students, maxStudents, totalStudents);
}
