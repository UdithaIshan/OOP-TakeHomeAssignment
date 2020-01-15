#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

int count = 0;
int line_count = 0;

class flight{
    struct data{
        string flight_no;
        string dateTime;
        char dep_airport[20] = {'\0'};
        char arr_airport[20] = {'\0'};
        char seat[60][50] = {{'\0'}};
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
                    if(dataSet[i].seat[j][0] != '\0'){
                        cout << endl << dataSet[i].flight_no << endl;
                        cout << dataSet[i].dateTime << endl;
                        cout << dataSet[i].dep_airport << endl;
                        cout << dataSet[i].arr_airport << endl;
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
                string search, seatData;
                int c0 = 0, c1 = 0, c2 = 0, seatCount, user;
                cout << "Enter the flight no: ";
                cin >> search;
                cout << "How many seats do you want? ";
                cin >> user;
                for(int i = 0; i < count; ++i){
                    if(dataSet[i].flight_no == search){
                        for(int j = 0; j < 60; ++j){
                            if(dataSet[i].seat[j][0] != '\0'){
                                    seatData = dataSet[i].seat[j];
                                    for(int i = 0; c0 < 2; i++){
                                        if(seatData[i] == ' ')
                                            ++c0;
                                        ++c1;    
                                    }
                                    c2 = seatData.size() - c1;
                            }
                            seatCount += c2;
                            c2 = 0;
                            c0 = 0;
                            c1 = 0;
                        }
                        if(seatCount >= user)
                            cout << " Available seat count :" << seatCount << endl;
                        else
                            cout << "Sorry!" << endl << "Seats are already booked." << endl;
                    }
                }
				break;
			}
            break;
            case 4:{
                string search, UseatName, Urow;
                cout << "Enter the flight no: " << endl;
                cin >> search;
                cout << "Enter the Row no:" << endl;
                cin >> Urow;
                cout << "Enter the Seat Name:" << endl;
                cin >> UseatName;

                for(int i = 0; i < count; i++){
                    if(dataSet[i].flight_no == search){
                        for(int j = 0; j < 60; ++j){
                            bool flag = false;
                            if(dataSet[i].seat[j][0] != '\0'){
                                string seatdata = dataSet[i].seat[j];
                                istringstream buffer(seatdata);
                                string row, sclass, number;
                                char seats[11];
                                int size, r,s, n;
                                
                                buffer >> row >>sclass >> number;
                                size = seatdata.size();
                                r = row.size();
                                s = sclass.size();
                                if(row == Urow){
                                    int found = number.find(UseatName);
                                    if(found != string::npos){
                                        seatdata.erase(seatdata.begin() + (found + r + s + 2));
                                        cout << seatdata << endl;
                                        for(int k = 0; k < 50; ++k)
                                        dataSet[i].seat[j][k] = '\0';
                                        seatdata.copy(dataSet[i].seat[j], seatdata.size()+1);
                                        cout << dataSet[i].seat[j] << endl;
                                        cout << "Seat allocation successfull" << endl;
                                        flag = true;
                                    }
                                    else
                                        cout << "ERROR: Seat is unavailable !" << endl;
                                }

                            }
                            if(flag){
                                break;
                            }
                        }
                    }
                }
                }
                break;
            case 5:{
                ofstream myfile ("flights.dat", ios::app);
                if (myfile.is_open()){
                    string out;
                    for(int i = 0, j = 0; i < count; ++i){
                    out = dataSet[i].flight_no;
                    myfile << out << endl;;
                    out = dataSet[i].dateTime;
                    myfile << out << endl;
                    out = dataSet[i].dep_airport;
                    myfile << out << endl;
                    out = dataSet[i].arr_airport;
                    myfile << out << endl;
                    for(int j = 0; j < 60; ++j){
                            if(dataSet[i].seat[j][0] != '\0'){
                                    out = dataSet[i].seat[j];
                                    myfile << out << endl;
                            }
                    }
                    myfile << endl;   
                    }
                    myfile.close();
                }
                else cout << "Unable to open file" << endl;

            }
            break;    
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
