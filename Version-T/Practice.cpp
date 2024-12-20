#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


// void sort(string info[2][50], int sizeOfArr){
//         for(int i=0;i<sizeOfArr;i++){
//         for(int j=i+1;j<sizeOfArr;j++){
//             string status= info[1][i];
//             if(status < info[1][j]){
//                 string temp = info[1][j];
//                 info[1][j] = status;
//                 info[1][i] = temp;
//             }
//         }
//     }
// }
void autoRoomAllocation(string autoRooms[25][2], string readRegNo[50]){
    int i=0 ,  x=0;
    while(i<50  && x<25){
        for(int j=0;j<2;j++){
            if(j==0){
            autoRooms[x][j] = readRegNo[i];
            }
            else if(j==1){
                autoRooms[x][j] = readRegNo[i+1];
            } 
        }
        x+=1;
        i+=2;
    }
}
void hostelMenu(string name, int index, string roomate){
    cout<<"Welcome "<<name<<endl;
    cout<<"|\t\tHostel Information\t\t|"<<endl;
    cout<<"Room Number: " << (index/2)<<endl << "Your roomate is " << roomate <<endl;
    // cout<<"\n\t\t|Select an option|\t\t"<<endl;
    // cout<<"1. Register Complaint"<<endl<<"2.";
}

void login(string *regNo, string *passwords, string info[2][50]){
    bool cond = false;
    fstream sampleData;
    string reg_No , line ,  password;

    int index = 0;
    do
    {
        cout << "Enter Reg No: ";
    cin >> reg_No;

    for (int i = 0; i < 50; i++){
         if (reg_No == regNo[i]){
            cout << "Enter Password: ";
            cin >> password;
            if (password == passwords[i]){
                cout << "Succesful Login"<<endl;
                if(i%2==0){
                    hostelMenu(info[0][i],i, info[0][i+1]);
                } 
                else{
                    hostelMenu(info[0][i],i, info[0][i-1]);
                }
                cond = true;
                break;
            }
            else{
                cout << "Incorrect Password"<<endl;
                break;
            }
        }
        else if (i >= 49){
            cout <<"Either Reg No is incorrect or doesnt exist" << endl;
        }
         }
    } while (cond == false);
    
    
    sampleData.close();
}
int main(){
    int index = 0, sizeOfArr=0;
    fstream sampleData;
    string line , regToPass, pass, gender,lines[50];
    sampleData.open("E:/HACKING/CS-101 Semester Project/First-Sem-CS-Project/Version-T/sampleData.txt", ios::in);
    while(getline(sampleData,line)){
        sizeOfArr+=1;
    }
    sampleData.close();
    cout<<sizeOfArr<<endl;
    string hostelsInfo[12][2], readRegNo[sizeOfArr] , passwords[sizeOfArr], autoRooms[25][2], info[2][50];

     sampleData.open("E:/HACKING/CS-101 Semester Project/First-Sem-CS-Project/Version-T/sampleData.txt", ios::in);

     while(getline(sampleData,line) && index<50){
        lines[index] = line;
        istringstream ss(line);
        string name, reg;
        getline(ss, reg, ','); 
        getline(ss, name, ',');
        getline(ss, gender);      
        info[0][index] = name;
        info[1][index]  = gender;
        readRegNo[index] = reg;   
        index++;
     }
     sampleData.close();
     index = 0;

    sampleData.open("E:/HACKING/CS-101 Semester Project/First-Sem-CS-Project/Version-T/sampleData.txt", ios::out | ios::in);
    while(index<sizeOfArr){
        pass = "123";
        regToPass = readRegNo[index];
        for(int i=0;i<regToPass.length();i++){
            if(i>3){
                pass += regToPass[i];
            }   
        }
        passwords[index] = pass;
        lines[index] += "," + passwords[index];
        // cout<<lines[index]<<endl;
        sampleData << lines[index]<<endl;
        index+=1;
    }


    sampleData.close();

    // Login Functionality

    // sort(info,sizeOfArr);
    // for(int i=0;i<sizeOfArr;i++){
    //     cout<<info[1][i]<<endl;
    // }
    login(readRegNo, passwords , info);
    autoRoomAllocation(autoRooms,readRegNo);
    for(int i=0;i<25;i++){
    cout<<"Members of Room "<<i<<" are ";
    for(int j=0;j<2;j++){
        cout<<autoRooms[i][j]<<",";
    }
    cout<<endl;
    }

    return 0;
}