#include <iostream>
#include <string>
#include <fstream>
using namespace std;
void changepassword(string username, string cnic_no){
					    string age,password, file_pass, file_user, file_cnic, name, next_line, new_pass,
						phone_no,floor_no,room_no,facilty,hostel_no,warden_name,warden_phone_no;
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
            				file.seekg(0, ios::beg);  // Reset to the start of the file before writing
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
                
                 //Check if the current user is the one that logged in and update the password
                		if (file_user == username && file_cnic == cnic_no) {
                    		updated_data += file_user + "\n" + new_pass + "\n" + file_cnic + "\n" + name + "\n" 
							+ hostel_no + "\n"+ room_no + "\n"+ floor_no + "\n"+ facilty + "\n"+ phone_no + "\n"
							+ warden_name + "\n"+ warden_phone_no + "\n"+ next_line + "\n";
                		}
						else {
                			updated_data += file_user + "\n" + file_pass + "\n" + file_cnic + "\n" + name + "\n" 
							+ hostel_no + "\n"+ room_no + "\n"+ floor_no + "\n"+ facilty + "\n"+ phone_no + "\n"
							+ warden_name + "\n"+ warden_phone_no +"\n"+ next_line + "\n";
                		}
					}

            		file.close();
           	 		file.open("student_login.txt", ios::out);
            		file << updated_data; // Write updated data back to the file
            		cout << "Password updated successfully.\n";
           			pass = true;
        }
        
    	} while (!pass);

    file.close();

	
	
}
void complaintbox(string username){
	string complain;
	cin.ignore();
	ofstream file("complaint.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error the file is not loaded" << endl;
        return;
    }
    cout<<"Enter your Complain :\n";
	getline(cin,complain);
    file<<username<<" "<<complain<<"\n";
}
int main() {
    string username, age, cnic_no, password, file_pass, file_user, file_cnic, name, next_line, new_pass,
	phone_no,floor_no,room_no,facilty,hostel_no,warden_name,warden_phone_no;
    int storepasswordplace,complain;

    fstream file("student_login.txt", ios::in | ios::out);

    if (!file.is_open()) {
        cout << "Error the file is not loaded" << endl;
        return 1;
    }

    bool login;

    do {
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);
        cout << "Enter CNIC: ";
        getline(cin, cnic_no);

        file.seekg(0, ios::beg);

        login = false; // Reset login flag before each login attempt

        while (file.good()) {
            getline(file, file_user);
            storepasswordplace = file.tellg(); // Store password position, should be adjusted later
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
                int chose;
                cout<<"1: Information\n";
                cout<<"2: Change Password\n";
                cout<<"3: complain and any other issue\n";
                cin>>chose;
                login = true;
                if(chose==1){
                	cout<<name<<endl;
                	cout<< hostel_no << "\n";
                	cout<< floor_no<<"\n"<<"Room No :"<<room_no<<"\n"<<facilty<<endl;
                	cout<<phone_no<<endl;
                	cout<<warden_name<<endl;
                	cout<<warden_phone_no<<endl;
                	cout<<"Password : "<<file_pass<<endl;
                	cout<<"Cnic_NO : "<<file_cnic<<endl;
                	}
                	else if(chose==2){
                		changepassword(username, cnic_no);
                	
                		
                }

				else if (chose==3){
                	complaintbox(username);
				}
				
                break;
            }
        }

        if (!login)
            cout << "Login Failed!\n";

    } while (!login);


    return 0;
}
