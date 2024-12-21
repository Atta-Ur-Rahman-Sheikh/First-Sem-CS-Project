#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream studentFile("Student_Data.txt");
    if (!studentFile)
    {
        cerr << "ERROR: Student File can't be Opened!";
        return 1;
    }
    string line;
    while (getline(studentFile, line))
    {
        if (line.find("Name: ") == 0)
        {                                   
            cout << line.substr(6) << endl; 
        }
    }
    return 0;
}
