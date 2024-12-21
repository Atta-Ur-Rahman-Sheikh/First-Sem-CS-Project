#include <iostream>
#include <string>
#include <fstream>
using namespace std;
void complaint(string username) {
    string file_user, complain;
    fstream file("complaint.txt", ios::in);

    if (!file.is_open()) {
        cout << "Error: The file is not loaded." << endl;
        return;
    }
    int found = 0;
    while (file.good()) {
        file >> file_user; // Read the username
        if (file_user == username) {
            getline(file, complain); // Read the complaint
            cout << "Your pending complaint: " << complain << endl;
            found = found+1;
        } else {
            getline(file, complain); // Skip the complaint for other users
        }
    }

    if (found==0) {
        cout << "No pending complaints found for user: " << username << endl;
    }

    file.close();
}
void changepassword(string username, string cnic_no) {
    string age, password, file_pass, file_user, file_cnic, name, next_line, new_pass,
           phone_no, floor_no, room_no, facilty, hostel_no, warden_name, warden_phone_no;
    fstream file("student_login.txt", ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Error the file is not loaded" << endl;
        return;
    }
    bool pass = false;

    do {
        cout << "You must enter a password with a minimum of 8 characters: ";
        getline(cin, new_pass);
        if (new_pass.length() > 7) {
            file.seekg(0, ios::beg);
            string line;
            string updated_data = "";

            while (getline(file, file_user)) {
                getline(file, file_pass);
                getline(file, file_cnic);
                getline(file, name);
                getline(file, hostel_no);
                getline(file, room_no);
                getline(file, floor_no);
                getline(file, facilty);
                getline(file, phone_no);
                getline(file, warden_name);
                getline(file, warden_phone_no);
                getline(file, next_line);

                if (file_user == username && file_cnic == cnic_no) {
                    updated_data += file_user + "\n" + new_pass + "\n" + file_cnic + "\n" + name + "\n"
                                    + hostel_no + "\n" + room_no + "\n" + floor_no + "\n" + facilty + "\n" + phone_no + "\n"
                                    + warden_name + "\n" + warden_phone_no + "\n" + next_line + "\n";
                } else {
                    updated_data += file_user + "\n" + file_pass + "\n" + file_cnic + "\n" + name + "\n"
                                    + hostel_no + "\n" + room_no + "\n" + floor_no + "\n" + facilty + "\n" + phone_no + "\n"
                                    + warden_name + "\n" + warden_phone_no + "\n" + next_line + "\n";
                }
            }

            file.close();
            file.open("student_login.txt", ios::out);
            file << updated_data;
            cout << "Password updated successfully.\n";
            pass = true;
        }
    } while (!pass);

    file.close();
}
void complaintbox(string username) {
    string complain;
    ofstream file("complaint.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error the file is not loaded" << endl;
        return;
    }
    cout << "Enter your Complain:\n";
    cin.ignore();
    getline(cin, complain);
    cin.ignore();
    file << username << " " << complain << "\n";
    file.close();
}

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    int chose;
    string username, age, cnic_no, password, file_pass, file_user, file_cnic, name, next_line, new_pass,
           phone_no, floor_no, room_no, facilty, hostel_no, warden_name, warden_phone_no;
    int storepasswordplace, complain;

    fstream file("student_login.txt", ios::in | ios::out);

    if (!file.is_open()) {
        cout << "Error the file is not loaded" << endl;
        return 1;
    }

    bool login;
     file.seekg(0, ios::beg);

    do {
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);
        cout << "Enter CNIC: ";
        getline(cin, cnic_no);

        file.seekg(0, ios::beg);
        login = false;

        while (file.good()) {
            getline(file, file_user);
            storepasswordplace = file.tellg();
            getline(file, file_pass);
            getline(file, file_cnic);
            getline(file, name);
            getline(file, hostel_no);
            getline(file, room_no);
            getline(file, floor_no);
            getline(file, facilty);
            getline(file, phone_no);
            getline(file, warden_name);
            getline(file, warden_phone_no);
            getline(file, next_line);

            if (file_user == username &&
                file_pass == password &&
                file_cnic == cnic_no) {
                cout << "Login successful! Welcome " << name << "!\n";

                int choice;
                do {
                    cout << "1: Change Password\n";
                    cout << "2: View Information\n";
                    cout << "3: Submit a Complaint\n";
                    cout << "4: Your Pending Complaint\n";
                    cout << "5: Notification\n";
                    cout << "6: Logout the account\n";
                    cout << "Enter your choice: ";
                    cin >> choice;
                    cin.ignore();

                    switch (choice) {
                        case 1:
							changepassword(username, cnic_no);
                            break;

                        case 2:
                            cout << "Name: " << name << endl;
                            cout << hostel_no << "\n";
                            cout << floor_no << "\n";
                            cout << "Room No: " << room_no << "\n";
                            cout << facilty << endl;
                            cout << phone_no << endl;
                            cout << warden_name << endl;
                            cout << warden_phone_no << endl;
                            cout << "CNIC: " << file_cnic << endl;
                            if (password == file_pass)
                                cout << "Password: " << file_pass << endl;
                            else
                                cout << "Password: " << new_pass << endl;
                            break;

                        case 3:
                            cin.ignore();
                            complaintbox(username);
                            break;

                        case 4:
                            complaint(username);
                            break;

                        case 5:
                            cout << "No new notifications at the moment.\n";
                            break;

                        case 6:
                            cout << "Logging out...\n";
                            break;

                        default:
                            cout << "Invalid option. Please try again.\n";
                            break;
                    }
                } while (choice != 6); 
                break; 
            }
        }

        if (!login) {
            cout << "Login Failed!\n";
        }

    } while (!login); // End do-while loop

    return 0;
}

