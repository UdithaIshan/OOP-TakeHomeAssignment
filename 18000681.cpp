#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int count = 0;
int line_count = 0;

class flight{
    struct data{
        string flight_no;
        string dateTime;
        char dep_airport[20];
        char arr_airport[20];
        char seat[60][50];
    };

    public:
    void ReadDataFromFile(int x);
};

void flight::ReadDataFromFile(int x){

    ifstream file("Flights.txt");

    string line;
    int dataBlockCounter = 0;
    int dataBlockLineCounter = 0;
    int dataBlockSeatLineCounter = 0;

    if(file.is_open()){
        while(getline(file, line)){
            if(line == "\0")
            count++;            //5
            else
            line_count++; //60

        }
        
    file.close();

    ifstream file("Flights.txt");

       struct data dataSet[count];

        while(getline(file, line)){
            

            if(line != "\0"){

                ++dataBlockLineCounter;

                if(dataBlockLineCounter == 1)
                    dataSet[dataBlockCounter].flight_no = line;
                else if(dataBlockLineCounter == 2)
                    dataSet[dataBlockCounter].dateTime = line;
                else if(dataBlockLineCounter == 3)
                    line.copy(dataSet[dataBlockCounter].dep_airport, line.size()+1);
                else if(dataBlockLineCounter == 4)
                    line.copy(dataSet[dataBlockCounter].arr_airport, line.size()+1);
                else{
                   // strncpy(dataSet[dataBlockCounter].seat[dataBlockSeatLineCounter], line, line.size()+1);
                    line.copy(dataSet[dataBlockCounter].seat[dataBlockSeatLineCounter], line.size()+1);
                    dataBlockSeatLineCounter++;
                }
            } 
            else{
                ++dataBlockCounter;
                dataBlockLineCounter = 0;
                dataBlockSeatLineCounter = 0;
            }           
        }

        file.close();

        switch(x){
            case 1:
                for(int i = 0, j = 0; i < count; ++i){
                    if(dataSet[i].seat[j] != '\0'){
                        cout << endl << dataSet[i].flight_no << endl;
                        cout << dataSet[i].dateTime << endl;
                        cout << dataSet[i].dep_airport << endl;
                        cout << dataSet[i].arr_airport << endl;
                        //int rows =  sizeof dataSet[i].seat / sizeof dataSet[i].seat[0];
                        //cout << rows << endl;
                        for(j = 0; j < 60; ++j){
                        	if(dataSet[i].seat[j][0] != '\0')
                            cout << dataSet[i].seat[j] << endl;
                            else
                            	break;
                        }
                    }
                    j = 0;
                }
                break;
            case 2:{
                string search;
                bool flag = true;
                cout << "Enter the flight no: ";
                cin >> search;
                for(int i = 0, j = 0; i < count; ++i){
                    if(dataSet[i].flight_no == search){
                        cout << "Available seats      : " <<endl; 
                        for(j = 0; j < 50; ++j){
                        	if(dataSet[i].seat[j][0] != '\0')
                            cout << "                       " << dataSet[i].seat[j] << endl;
                            else
                            	break;
                        }
                        cout << "Departure Airport    : " << dataSet[i].dep_airport << endl;
                        cout << "Arrival Airport      : " << dataSet[i].arr_airport << endl;
                        cout << "Departure Date & Time: " << dataSet[i].dateTime << endl;
                        flag = false;
                    }
                }

                if(flag)
                    cout << "ERROR: Flight not found!" << endl;}
                break;
            case 3:{
                string search;
                bool flag = true;
                cout << "Enter the flight no: ";
                cin >> search;
                for(int i = 0,j = 0; j < 60; ++j){
                        	if(dataSet[i].seat[j][0] != '\0')
                            cout << dataSet[i].seat[j] << endl;
                            else
                            	break;
                        }
				break;
			}
                
        }
    }
    else
        cout << "Error: Can't open the 'Flight.txt' file!" << endl;
}


int main(){
    int opt;
    bool flag = true;
    flight obj;

    do{
        cout << endl << "1: Display available flights." << endl;
        cout << "2: View flights" <<endl;
        cout << "3: Seat availability" << endl;
        cout << "4: Seat Booking" << endl;
        cout << "5: Exit" << endl;
        cout << "Choose your option: ";
        cin >> opt;
        cout << endl;
        obj.ReadDataFromFile(opt);
    }
    while(flag);
}
