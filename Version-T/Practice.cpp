#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void addStudent(){
    string regNo, name, gender, program, section, accountPassword, contact,  emergencyContact, cnic;
    int age;
    std::cout<<"Name of new student (ONLY BLOCK LETTERS!) : ";
    std::cin>>name;
    std::cout<<"Enter Reg No of new student:";
    std::cin>>regNo;
    std::cout<<"Gender of new student: ";
    std::cin>>gender;
};

void adminFunctionality(string *admin, int i){
    int option;
    std::cout<<"Welcome" << *(admin + i * 3 +1)<<" ! Choose an option: "<<endl;
    std::cout<<"1. Add a student"<<endl<< "2. Remove a student"<<endl<< "3. Parcel of a student";
    std::cin>>option;
    switch (option)
    {
    case 1:
        addStudent();
        break;
    
    default:
        break;
    }
    
}

void adminLogin(string* admin, int sizeOfAdminArr){
    std::cout<<sizeOfAdminArr;
    string name,id,auth_id;
    std::cout<<"Enter Your Employee ID: ";
    std::cin>>id;
    std::cout<<"Enter  Authorization ID: ";
    std::cin>>auth_id;
    for(int i=0;i<sizeOfAdminArr;i++){
        if((id == *(admin + i * 3 + 0))  && (auth_id == *(admin + i * 3 + 2))){
            adminFunctionality((string *)admin, i);
            // break;
        }
        else if(i>=sizeOfAdminArr){
            std::cout<<"NO baby"<<i<<endl;
        }
    }

}

void autoRoomAllocation(string studentInfo[700][12], string *hostel, int maxCapacity){
    int i=0;
    while(i<maxCapacity*2){
        *(hostel + i + 0) = studentInfo[i][0];
        *(hostel + i + 1) = studentInfo[i+1][0];
        i+=2;
        }
 for (int i = 0; i < maxCapacity; i++) { // maxCapacity is number of rooms, so divide by 2
         cout<<"\nMembers of room "<<i+1<<"are :\n";
        for (int j = 0; j < 2; j++) {
            cout << *(hostel + i * 2 + j) << endl; // Print both students in the room
        }
    }

}
void hostelMenu(string name, int index, string roomate, string studentInfo[700][12]){
    string labels[12] = {"Name: ", "Registration Number: ", "Gender: ", "Age: ", "Cnic: ", "Program: ",  "Section: ", "Account Password: ", "Contact: ", "Emergency Contact: ", "Hostel: ", "Room: "};
    std::cout<<"\n|\t\tYour Information\t\t|\n"<<endl;
    for(int i=0;i<12;i++){
        cout<<endl<<labels[i]<<studentInfo[index][i]<<endl;
    }
    std::cout<<"\n|\t\tHostel Information\t\t|"<<endl;
    std::cout<<"\nRoom Number: " << (index/2)<<endl << "Your roomate is " << roomate <<endl;
}

void changePassword(string studentInfo[700][12], int i, int sizeOfArr){
    fstream studentData;
    string password, line,_line,  updatedline, lines[sizeOfArr];
    int index = 0;
    std::cout<<"Your current password is : " << studentInfo[i][7]<<endl;
    std::cout<<"Enter new password: ";
    std::cin>>password;
    studentInfo[i][7] = password;
    studentData.open("E:/HACKING/CS-101 Semester Project/First-Sem-CS-Project/Version-T/studentData.txt", ios::in | ios::out);
     while(getline(studentData,line) && index<sizeOfArr){
        if(line == "---"){
            index+=1;
        }
        if(line.find("Name:") == 0 && index==i){
            for(int i=0;i<12;i++){
                getline(studentData,_line);
                if(_line.find("Account Password:")==0){
                    _line = "Account Password:"+ password + "\n";
                    studentData<<_line;
                }
            }
        }
     }
     studentData.close();
     std::cout<<updatedline<<endl;
     index = 0;
     std::cout<<"Password updated!";
}

void login(string studentInfo[700][12], int sizeOfArr){
    bool cond = false;
    fstream studentData;
    string reg_No, line, password;

    do {
        std::cout << "\nEnter Reg No: ";
        std::cin >> reg_No;
        bool found = false, exit = false;
        for (int i = 0; i < sizeOfArr; i++) {
            if (reg_No == studentInfo[i][1]) {
                std::cout << "\nEnter Password: ";
                std::cin >> password;
                if (password == studentInfo[i][7]) {
                    std::cout << "\nSuccessful Login" << endl;
                    int option;
                    do{
                    std::cout << "\nSelect an option: " << endl;
                    std::cout << "1. View Information" << endl << "2. Change Password" << endl << "3. Other Details"<<endl << "4. Exit"<< endl;
                    std::cin >> option;
                    switch (option) {
                        case 1:
                            std::cout<<"\nWelcome "<< studentInfo[i][0] <<endl;
                            if (i % 2 == 0) {
                                hostelMenu(studentInfo[i][0], i, studentInfo[i - 1][0], studentInfo);
                            } else {
                                hostelMenu(studentInfo[i][0], i, studentInfo[i + 1][0], studentInfo);
                            }
                            break;
                        case 2:
                            changePassword(studentInfo, i, sizeOfArr);
                            break;
                        case 4:
                            exit = true;
                            break;
                        default:
                            std::cout<<"\nInvalid Option! Enter again!"<<endl;
                    }
                } while (exit == false);
                    cond = true;
                    found = true;
                    break;
                } else {
                    std::cout << "Incorrect Password" << endl;
                    break;
                }
            }
        }
        if (!found) {
            std::cout << "Either Reg No is incorrect or doesn't exist" << endl;
        }

    } while (!cond);

    studentData.close();


}
int main(){
    int index = 0, sizeOfArr=0, sizeOfAdminArr=0, option, maxHostelCapacity=250;
    fstream studentData, adminData;
    string line, studentInfo[700][12], hostelsInfo[3][2], hostelEleven[maxHostelCapacity][2];
    studentData.open("E:/HACKING/CS-101 Semester Project/First-Sem-CS-Project/Version-T/studentData.txt", ios::in);
    while(getline(studentData,line)){
        if(line=="---"){
            sizeOfArr+=1;
        }
    }
    studentData.close();
    string  regToPass, pass, gender,lines[sizeOfArr];
    studentData.open("E:/HACKING/CS-101 Semester Project/First-Sem-CS-Project/Version-T/studentData.txt", ios::in);
    int fieldNo =0;
    while(getline(studentData,line)){
        lines[index] = line;
        istringstream ss(line);
        string label, value;
        if(line == "---"){
            index++;
            continue;
        }
        if (getline(ss, label, ':')) {
            if (ss.peek() == ' ' || ss.peek() == '\t' || ss.peek() == '\n' || ss.peek() == EOF) {
                value = "";
            } 
            else {
                getline(ss, value);
            }
            studentInfo[index][fieldNo] = value; 
            fieldNo++;
        }
        if (fieldNo == 12) {
            fieldNo = 0;
        }
    }
    studentData.close();
    index = 0;

    autoRoomAllocation(studentInfo, (string *)hostelEleven, maxHostelCapacity);
    std::cout<<"Select an option: "<<endl;
    std::cout<<"1. Student Login"<<endl<<"2. Admin Login"<<endl;
    std::cout<<"\nEnter option number: ";
    std::cin>>option;

    if(option ==1){
        login(studentInfo, sizeOfArr);
    }
    else if(option ==2){
        int i=0;
        adminData.open("E:/HACKING/CS-101 Semester Project/First-Sem-CS-Project/Version-T/adminData.txt", ios::out | ios::in);
        while(getline(adminData,line)){
            sizeOfAdminArr+=1;
        }
        adminData.close();
        string admin[sizeOfAdminArr][3];
        adminData.open("E:/HACKING/CS-101 Semester Project/First-Sem-CS-Project/Version-T/adminData.txt", ios::out | ios::in);
        while(getline(adminData, line) && i<sizeOfAdminArr){
            istringstream ss(line);
            string id, name, auth_id;
            getline(ss, id, ',');
            getline(ss, name, ','); 
            getline(ss, auth_id);
            admin[i][0] = id;   
            admin[i][1] = name;   
            admin[i][2] = auth_id;   
            i++;
        }
        adminData.close();
        adminLogin((string*)admin, sizeOfAdminArr);
    }
    return 0;
}