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
        char seat[50];
    };

    public:
    void ReadDataFromFile(int x);
};

void flight::ReadDataFromFile(int x){

    ifstream file("Flights.txt");

    string line;
    int dataBlockCounter = 0;
    int dataBlockLineCounter = 0;

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

                if(dataBlockLineCounter == 1){
                    dataSet[dataBlockCounter].flight_no = line;
                    //cout << dataSet[dataBlockCounter].flight_no << endl;
                   }
                else if(dataBlockLineCounter == 2)
                    dataSet[dataBlockCounter].dateTime = line;
                else if(dataBlockLineCounter == 3)
                    line.copy(dataSet[dataBlockCounter].dep_airport, line.size()+1);
                else if(dataBlockLineCounter == 4)
                    line.copy(dataSet[dataBlockCounter].arr_airport, line.size()+1);
                else
                    line.copy(dataSet[dataBlockCounter].seat, line.size()+1);
            } 
            else{
                 ++dataBlockCounter;
                 dataBlockLineCounter = 0;
            }           
        }

        file.close();

        switch(x){
            case 1:
                for(int i = 0; i < count; ++i){
                   // if(dataSet[i].flight_no != "\0"){
                        cout << dataSet[i].flight_no << endl;
                   // }
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
        cout << "1: Display available flights." << endl;
        cout << "2: View flights" <<endl;
        cout << "3: Seat availability" << endl;
        cout << "4: Seat Booking" << endl;
        cout << "5: Exit" << endl;
        cout << "Choose your option: ";
        cin >> opt;
        obj.ReadDataFromFile(opt);
    }
    while(flag);
}
