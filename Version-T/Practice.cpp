#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


void autoRoomAllocation(string *autoRooms, string readRegNo[100]){
    for(int i=0;i<100;i++){
        for(int j=0;j<2;j++){
            *(autoRooms + i * j) = readRegNo[i];
        }
    }
}
void hostelMenu(){
    cout<<"Welcome!"<<endl;
    // cout<<"\n\t\t|Select an option|\t\t"<<endl;
    // cout<<"1. Register Complaint"<<endl<<"2.";
}


void login(string regNo[100], string passwords[100]){
    fstream sampleData;
    string reg_No , line ,  password;

    // string r;
    int index = 0;
    // int password;
    cout << "Enter Reg No: ";
    cin >> reg_No;
    sampleData.open("E:/HACKING/CS-101 Semester Project/First-Sem-CS-Project/Version-T/sampleData.txt", ios::in | ios::out);
    while(getline(sampleData, line) && index<100){
        istringstream ss(line);
        string reg, pass;
        getline(ss, reg, ','); 
        getline(ss, pass);      
        regNo[index] = reg;   
        passwords[index] = pass;
        index=index+1;
    }
    for (int i = 0; i < 100; i++){
        if (reg_No == regNo[i]){
            cout << "Enter Password: ";
            cin >> password;
            if (password == passwords[i]){
                cout << "Succesful Login"<<endl;
                hostelMenu();
                break;
            }
            else{
                cout << "Incorrect Password"<<endl;
                break;
            }
        }
        else if (i >= 99){
            cout <<"Either Reg No is incorrect or doesnt exist" << endl;
        }
    }
    sampleData.close();
}
int main(){
    string hostelsInfo[12][2], regNo[100][2] ,readRegNo[100] , passwords[100], autoRooms[50][2];
    fstream sampleData;
    string line;
    // Used trunc as this file contains sample data created during execution , so every time when program runs file is first cleared and then data is written

    sampleData.open("E:/HACKING/CS-101 Semester Project/First-Sem-CS-Project/Version-T/sampleData.txt", ios::in | ios::out  | ios::trunc);

    // Creating a 2D Array containing sample data  to test login functionality

    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 1; j++) {
            regNo[i][j] = to_string(2024000 + i);
            regNo[i][j + 1] = to_string(123000 + i);
            if(sampleData){
                // Writing data to file 

                sampleData << regNo[i][j] << "," << regNo[i][j+1] << endl ;

            }
        }
    }
    sampleData.close();

    // Login Functionality

    login(readRegNo, passwords);
    autoRoomAllocation((string *)autoRooms,readRegNo);
    for(int i=0;i<50;i++){
        cout<<"Members of Room "<<i<<" are ";
        for(int j=0;j<2;j++){
            cout<<autoRooms[i][j]<<",";
        }
        cout<<endl;
    }
    // Outputing sample data created above 

    // for (int i = 0; i < 100; i++){
    //     for (int j = 0; j < 1; j++){
    //         cout << "Reg No: " << regNo[i][j] << endl;
    //         cout << "Password: " << regNo[i][j + 1] << endl;
    //     }
    // }

    return 0;
}
