#include <iostream>
#include <string>
using namespace std;
void identify(int* matrixarr, int row, int colum) {
    int zerocounter = 0, onecounter = 0, scalarcounter = 0, allzerocount = 0;
    int temp = *(matrixarr + (row - 1) * colum + (colum - 1));

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < colum; j++) {
            int currentElement = *(matrixarr + i * colum + j);
            if (currentElement == 0) {
                allzerocount++;
            }

            if (i != j) {
                if (currentElement == 0) {
                    zerocounter++;
                }
            } else {
                if (currentElement == 1) {
                    onecounter++;
                } else if (currentElement == temp) {
                    scalarcounter++;
                }
            }
        }
    }

    if (zerocounter == (row * colum - row)) {
        if (allzerocount == row * colum)
            cout << "two many attemp" << endl;
        else if (onecounter == row)
            cout << "enter new password" << endl;
        else if (scalarcounter == row)
            cout << "Scalar Matrix" << endl;
        else
            cout << "your account doesnot " << endl;
    }

    if (row == colum)
        cout << "suuccessful" << endl;
}

void transport(int* matrixarr, int row, int colum) {
    cout << "Transport" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = i + 1; j < colum; j++) {
            int temp = *(matrixarr + i * colum + j);
            *(matrixarr + i * colum + j) = *(matrixarr + j * colum + i);
            *(matrixarr + j * colum + i) = temp;
        }
    }
int main() {
    string username, age, cnic_no, password;
    // Header design for the program's welcome screen
    cout << "\t\t\t\t\t\t=============================================================" << endl;
    cout << "\t\t\t\t\t\t\t\t      GIKI HOSTEL MANAGEMENT" << endl;
    cout << "\t\t\t\t\t\t=============================================================" << endl;
    cout<<"\n\n\n\n";
	// Login page design using a loop to create a box-like structure
    for(int i=0;i<21; i++){
    	cout<<"\t\t\t\t\t\t\t";
    	for(int j=0; j<21; j++){
			// Check conditions to print the border of the box
			if(j==0||i==0||i==20||j==19){
				if(i==0||i==20){
					cout<<" *";	// Top and bottom border of the box
				}
				else
					cout<<" ||";// Left and right border of the box
				}
			else
				cout<<"  "; // Empty space inside the box
		}
		cout<<"\n";
	}
//bool decide;
//do{
//	int decideloginorsign;
//	cout<<"Enter 1 for sign up and 2 for login\n";
//	cin>>decideloginorsign;
//	decide=true;
//}
//while(!decide)
	// Predefined login information stored as a 2D array
	string logininformation[1000][4]={{"u2024286","2003/12/15","3333338521881","Mazhar Guftar"}
									  ,{"u2024287","2004/12/15","3333338521882","Talal Iqbal"}
									  ,{"u2024288","2004/12/15","3333338521883","Atta Rahman"}};
bool login; // variable for used for again input
do{
	
	  // Input prompt for login details
	cout << "Enter username: ";
    getline(cin, username); // Read the username
    cout << "Enter password: ";
    getline(cin, password); // Read the password
    cout << "Enter CNIC: ";
    getline(cin, cnic_no);  // Read the CNIC number
	for(int i=0;i<1000;i++){
		// Check the entered credentials against the stored login information
        if (logininformation[i][0] == username && 
            logininformation[i][1] == password && 
            logininformation[i][2] == cnic_no){
            cout << "Login successful! Welcome " << logininformation[i][3] << "!" << endl;  // Successful login message
        	login=true;
			break;
			}
		}	
	if(!login)
		cout << "Login Failed!\n"; //  login Filled message  
}
while(!login);
	
    return 0;
}

