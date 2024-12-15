#include <iostream>
using namespace std;

void hostelMenu(){
    cout<<"Welcome!"<<endl;
}

int main(){
    int regNo[100][2];
    // Creating a 2D Array containing sample data  to test login functionality

    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 1; j++) {
            regNo[i][j] = 2024000 + i;
            regNo[i][j + 1] = 123000 + i;
        }
        cout << "\n";
    }

    // Outputing sample data created above 

    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 1; j++){
            cout << "Reg No: " << regNo[i][j] << endl;
            cout << "Password: " << regNo[i][j + 1] << endl;
        }
    }

    // Login Functionality
    
    int reg_No, password;
    cout << "Enter Reg No: ";
    cin >> reg_No;
    for (int i = 0; i < 100; i++){
        if (reg_No == regNo[i][0]){
            cout << "Enter Password: ";
            cin >> password;
        if (password == regNo[i][1]){
            cout << "Succesful Login"<<endl;
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

    hostelMenu();

    return 0;
}
