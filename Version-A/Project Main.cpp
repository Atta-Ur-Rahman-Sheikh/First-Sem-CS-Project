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
void AdminAddStudent(string *, int, int &);
void AdminComplainManagement(string *, int, int &);

string adminMasterKey = "8888";

int main()
{
    // ADMIN MASTER KEY: 8888
    system("");
    cout << "\033[40m\033[1;33m\t=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\t|  GIK HOSTEL MANAGEMENT  |\n\t=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n";

    int maleStudents = 0, femaleStudents = 0, totalStudents = 0;
    const int maxStudents = 800;
    string students[12][maxStudents];
    ReadArray(students, maleStudents, femaleStudents, totalStudents);

    AllotHostels(students, totalStudents);

    int currentAccount = LoginAccount(DisplayLoginChoice(), (string *)students, maxStudents);
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

    // cout << "\nTotal Students: " << totalStudents << endl;
    // cout << "Male Students: " << maleStudents << endl;
    // cout << "Female Students: " << femaleStudents << endl;

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
                cerr << "\033[31m\nNo available rooms for male students.\n\033[0m";
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
        cout << " 2. Admin login\n";
        cout << " 3. Exit\033[0m\n";
        cout << "\nInput (1 - 3): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 3)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
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
                cout << "\033[31m\nInvalid password, please try again.\n\n\033[0m";
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
        cout << "\nInput (1 - 9): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 9)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
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
        DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
        break;
    }
}

void DisplayStudentProfile(string *students, int maxStudents, int currentAccount)
{
    string name = "\033[1;36m" + *(students + 0 * maxStudents + currentAccount) + "\033[0m";
    cout << "\nThis is your profile, " << name << ".\n";
    cout << "If there is an error or you need to update your info, contact the IT Department for assistance.";

    cout << "\n\n\033[40m\033[1;33mMY PROFILE: \033[0m\n\n";
    cout << " Name: \033[1;36m" << *(students + 0 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Reg: \033[1;36m" << *(students + 1 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Program: \033[1;36m" << *(students + 5 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Section: \033[1;36m" << *(students + 6 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Gender: \033[1;36m" << *(students + 2 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Age: \033[1;36m" << *(students + 3 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " CNIC: \033[1;36m" << *(students + 4 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Contact: \033[1;36m" << *(students + 8 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Emergency Contact : \033[1;36m" << *(students + 9 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Email: \033[1;36mu" << *(students + 1 * maxStudents + currentAccount) << "@giki.edu.pk\033[0m\n";
    cout << " Account Password: \033[1;36m" << *(students + 7 * maxStudents + currentAccount) << "\033[0m\n";

    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
}

void DisplayStudentHostelOverview(string *students, int maxStudents, int currentAccount)
{
    cout << "\n\n\033[40m\033[1;33mHOSTEL OVERVIEW: \033[0m\n\n";

    cout << " Hostel: \033[1;36m" << *(students + 10 * maxStudents + currentAccount) << "\033[0m\n";
    cout << " Room Number: \033[1;36m" << *(students + 11 * maxStudents + currentAccount) << "\033[0m\n";

    string currentHostel = *(students + 10 * maxStudents + currentAccount);
    string currentRoom = *(students + 11 * maxStudents + currentAccount);

    bool single = true;

    for (int i = 0; i < maxStudents; i++)
    {
        if (*(students + 10 * maxStudents + i) == currentHostel && *(students + 11 * maxStudents + i) == currentRoom && i != currentAccount)
        {
            cout << "\n\n\033[40m\033[1;33mROOMMATE DETAILS: \033[0m\n\n";
            cout << " Name: \033[1;36m" << *(students + 0 * maxStudents + i) << "\033[0m\n";
            cout << " Reg No: \033[1;36m" << *(students + 1 * maxStudents + i) << "\033[0m\n";
            cout << " Program: \033[1;36m" << *(students + 5 * maxStudents + i) << "\033[0m\n";
            cout << " Contact: \033[1;36m" << *(students + 8 * maxStudents + i) << "\033[0m\n";
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
        cout << " Hostel 11 Warden: \033[1;36m0311-0011011\033[0m\n";
        cout << " Email: \033[1;36mhostel11@giki.edu.pk\033[0m\n";
        cout << " Emergency Contact: \033[1;36m0300-1108011\033[0m\n";
    }
    else if (currentHostel == "H12")
    {
        cout << " Hostel 12 Warden: \033[1;36m0312-0012012\033[0m\n";
        cout << " Email: \033[1;36mhostel12@giki.edu.pk\033[0m\n";
        cout << " Emergency Contact: \033[1;36m0300-1208012\033[0m\n";
    }
    else
    {
        cout << " Girls Hostel Warden: \033[1;36m0353-0053053\033[0m\n";
        cout << " Email: \033[1;36mgirlshostel@giki.edu.pk\033[0m\n";
        cout << " Emergency Contact: \033[1;36m0300-5308053\033[0m\n";
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
        cout << "\033[31m\nIncorrect password. Returning to main menu.\033[0m\n";
        DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
    }
    else
    {
        cout << "Enter new password: ";
        cin >> newPass;
        if (newPass.empty())
        {
            cout << "\033[31mPassword cannot be empty.\033[0m\n";
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
    cout << "\n\n\033[40m\033[1;33mROOM TRANSFER REQUEST: \033[0m\n\n";

    // CODE

    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
}

void StudentParcelAlerts(string *students, int maxStudents, int currentAccount)
{
    cout << "\n\n\033[40m\033[1;33mPARCEL ALERTS: \033[0m\n\n";

    // CODE

    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
}

void StudentNotifications(string *students, int maxStudents, int currentAccount)
{
    string notifications[10];
    int numNotifications = 0;

    // Placeholder Notifications for testing
    notifications[numNotifications++] = "\033[32m [22-12-24 10:00 AM]\033[0m Your parcel has arrived and is received by Hostel Warden.";
    notifications[numNotifications++] = "\033[32m [22-12-24 11:15 AM]\033[0m You have a room swap request from another student. Contact the Hostel Warden for more information.";
    notifications[numNotifications++] = "\033[32m [22-12-24 06:45 PM]\033[0m Your fee for internet service is due by the end of the week.";

    cout << "\n\033[40m\033[1;33mNOTIFICATIONS: \033[0m\n\n";

    if (numNotifications == 0)
    {
        cout << "\nNo new notifications.\n";
    }
    else
    {
        for (int i = 0; i < numNotifications; ++i)
        {
            cout << notifications[i] << endl;
        }
    }

    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
}

void StudentReadsAdminAnnouncements(string *students, int maxStudents, int currentAccount)
{

    string announcements[10];
    int numAnnouncements = 0;

    announcements[numAnnouncements++] = "\033[32m [22-12-24 10:00 AM]\033[0m Laundry will be available from 9 AM to 6 PM every Saturday.";
    announcements[numAnnouncements++] = "\033[32m [22-12-24 11:15 AM]\033[0m Hot water will be available from 6 AM to 9 AM.";
    announcements[numAnnouncements++] = "\033[32m [22-12-24 06:45 PM]\033[0m There will be a scheduled electricity outage on 24th December from 2 PM to 4 PM.";
    announcements[numAnnouncements++] = "\033[32m [22-12-25 08:00 AM]\033[0m Hostel maintenance will be carried out on the 30th of December.";
    announcements[numAnnouncements++] = "\033[32m [22-12-25 09:00 AM]\033[0m Reminder: All hostel fees must be paid by the end of the month to avoid late fees.";

    cout << "\n\033[40m\033[1;33mADMIN ANNOUNCEMENTS: \033[0m\n\n";

    if (numAnnouncements == 0)
    {
        cout << "No new announcements.\n";
    }
    else
    {
        for (int i = 0; i < numAnnouncements; ++i)
        {
            cout << announcements[i] << endl;
        }
    }

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
        cout << "1: Track your old Complaint\n";
        cout << "2: Submit new Complaint\n";
        cout << "3: Exit\n";
        cin >> choice;
        string reg = *(students + 1 * maxStudents + currentAccount);
        if (choice == 1)
        {
            cout << "\n\n\033[40m\033[1;33mCOMPLAIN TRACKER: \033[0m\n\n";
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
                    cout << "Your pending complaint: " << complain << endl;
                    found = found + 1;
                }
                getline(file, complain);
            }

            if (found == 0)
            {
                cout << "No pending complaints found for user: " << reg << endl;
            }

            file.close();
        }
        else if (choice == 2)
        {
            cout << "\n\n\033[40m\033[1;33mNEW COMPLAINT Submit: \033[0m\n\n";
            string complain;
            ofstream file("complaint.txt", ios::app);
            if (!file.is_open())
            {
                cout << "Error the file is not loaded" << endl;
                return;
            }
            cout << "Enter your Complain:\n";
            cin.ignore();
            getline(cin, complain);
            cin.ignore();
            file << reg << " " << complain << "\n";
            file.close();
            cin.ignore();
            cin.get();
        }
        else if (choice == 3)
            break;
    } while (true);
    cout << "\nPress Enter to return to Main Menu.";
    cin.ignore();
    cin.get();
    DisplayStudentFeatures((string *)students, maxStudents, currentAccount);
}

void DisplayAdminFeatures(string *students, int maxStudents, int &totalStudents)
{
    string name = "\033[1;36mAdmin\033[0m";
    // cout << "\033[1;36mCYAN\033[0m\n";
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
        AdminChangePassword(students, maxStudents, totalStudents);
        break;
    case 2:
        AdminAddStudent(students, maxStudents, totalStudents);
        break;
    case 5:
        AdminComplainManagement(students, maxStudents, totalStudents);
    default:
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
        cout << "\033[31mPassword cannot be empty.\033[0m\n";
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
}

void AdminComplainManagement(string *students, int maxStudents, int &totalStudents)
{
}
