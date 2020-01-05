#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class flight{
    struct data{
        int flight_no; 
        string dateTime;
        char dep_airport[20];
        char arr_airport[20];
        struct seat{
            int row;
            char seatClass;
            char seatCode[6];
        }seatArray[10];

    public:
        
    };

};

int main(){
    ifstream myfile("Flights.txt");

    if(myfile.is_open())
    {   
        string line;
        while(getline(myfile, line)){
            if(line == '\0'){

            }
            cout << line << endl;
        }
    }
    else
    {
        cout << "Error while opening the file!" <<endl;
    }
    
}