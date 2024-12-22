#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void addStudent(string studentInfo[700][12]){
    bool cond;
    fstream studentData;
    string regNo, name, gender, program, section, accountPassword, contact,  emergencyContact, cnic;
    int age;
    accountPassword = "1";
    do{
        cond = true;
        std::cout<<"\nName of new student (ONLY BLOCK LETTERS!) : ";
        cin>>name;
        for(int i=0;i<name.length();i++){
            if((name[i] < 65 || name[i] > 90)){
                cout<<"\nBLOCK LETTERS ONLY!!"<<endl;
                cond = false;
                break;
            }
        }
        if (cond ==false) continue;
        std::cout<<"\nEnter Reg No of new student: ";
        std::cin>>regNo;
        for(int i=0;i<700;i++){
            if(regNo == studentInfo[i][1]){
                cout<<"\nThis Registration number already exists"<<endl;
                cond = false;
                break;
            }
        }
        if (cond==false) continue;;
        std::cout<<"\nGender of new student (M/F) : ";
        std::cin>>gender;
        if(gender != "M" && gender !="F"){
            cout<<"\nInvalid Entry!!"<<endl;
            cond = false;
            continue;
        }
        std::cout<<"\nAge of student: ";
        std::cin>>age;
        cnic = "55889-3735446-9";
        std::cout<<"\nProgram of student: ";
        std::cin>>program;
        std::cout<<"\nSection student: ";
        std::cin>>section;
        if((section[0] < 65 || section[0] > 90)){
                cout<<"\nBLOCK LETTERS ONLY!!"<<endl;
                cond = false;
                continue;
        }
        for(int i=0;i<regNo.length();i++){
            if(i<3){
                accountPassword += regNo[i];
            }
        }
        contact = "+923535267049";
        emergencyContact = "+923535267049";
    }while(cond==false);
    
    studentData.open("E:/HACKING/CS-101 Semester Project/First-Sem-CS-Project/Version-T/studentData.txt", ios::app);
    studentData << "\nName:" << name << endl;
    studentData << "Reg No:" << regNo << endl;
    studentData << "Gender:" << gender << endl;
    studentData << "Program:" << program << endl;
    studentData << "Section:" << section << endl;
    studentData << "Age:" << age << endl;
    studentData << "Account Password:" << accountPassword << endl;
    studentData << "Contact:" << contact << endl;
    studentData << "Emergency Contact:" << emergencyContact << endl;
    studentData << "CNIC:" << cnic << endl;
    studentData << "---" << endl; // 
    studentData.close();

};

void adminFunctionality(string *admin, int i, string studentInfo[700][12]){
    bool exit = false;
    int option;
    std::cout<<"Welcome" << *(admin + i * 3 +1)<<" ! Choose an option: "<<endl;
    do
    {
        std::cout<<"1. Add a student"<<endl<< "2. Remove a student"<<endl<< "3. Parcel of a student"<<endl<<"4. Exit"<<endl;
        std::cin>>option;
        switch (option)
        {
        case 1:
            addStudent(studentInfo);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            exit = true;
            break;
        
        default:
            break;
        }
    } while (exit == false);
    
    
}

void adminLogin(string* admin, int sizeOfAdminArr, string studentInfo[700][12]){
    bool cond = true;
    string name,id,auth_id;
    do {
        std::cout<<"\nEnter Your Employee ID: ";
        std::cin>>id;
        for(int i=0;i<sizeOfAdminArr;i++){
            if((id == *(admin + i * 3 + 0))){
                std::cout<<"Enter  Authorization ID: ";
                std::cin>>auth_id;
                if((auth_id == *(admin + i * 3 + 2))){
                    adminFunctionality((string *)admin, i, studentInfo);
                } else{
                    std::cout<<"Wrong Authorization ID!!"<<endl;
                    cond = false;
                    break;
                }
            }
            else if (i>= sizeOfAdminArr-1){
                std::cout<<"Wrong ID!!"<<endl;
                cond = false;
                break;
            }
        }
    } while (cond ==false);
    
   

}

void autoRoomAllocation(string studentInfo[700][12], string *hostel, string hostelsInfo[3][3], int maxCapacity){
    int i=0;
    while(i<maxCapacity*2){
        if(i>maxCapacity){
            hostelsInfo[1][0] = "Twelve";
        }
        else{
            hostelsInfo[0][0] = "Eleven";
        }
        if((studentInfo[i][2] =="M") && (studentInfo[i+1][2]=="M")){
            *(hostel + i + 0) = studentInfo[i][0];
            *(hostel + i + 1) = studentInfo[i+1][0];
        }
        else if((studentInfo[i][2] =="F") && (studentInfo[i+1][2]=="F")){
            cout<<studentInfo[i][2]<<endl<<studentInfo[i+1][2]<<endl;
        }
            i+=2;
        }
//  for (int i = 0; i < maxCapacity; i++) { // maxCapacity is number of rooms, so divide by 2
//          cout<<"\nMembers of room "<<i+1<<"are :\n";
//         for (int j = 0; j < 2; j++) {
//             cout << *(hostel + i * 2 + j) << endl; // Print both students in the room
//         }
//     }
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
    string line, studentInfo[700][12], hostelsInfo[3][3], hostelEleven[maxHostelCapacity][2];
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

    autoRoomAllocation(studentInfo, (string *)hostelEleven, hostelsInfo, maxHostelCapacity);
    cout<<hostelsInfo[0][0]<<endl;
    cout<<hostelsInfo[1][0]<<endl;
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
        adminLogin((string*)admin, sizeOfAdminArr, studentInfo);
    }
    return 0;
}