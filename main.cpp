#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int count = 0, line_count = 0;
struct seat{
        string flightRow;
        string flightClass;
        string seatNames;
    };

class Flight{
    private:
    string flight_no;
    string dateTime;
    string dep_airport;
    string arr_airport;
    struct seat dataSet[60];
    int eCount;
    int bCount;

    public:
    void setFlight(string flight);
    string getFlight();
    void setDate(string date);
    string getDate();
    void setDep(string dep);
    string getDep();
    void setArr(string arr);
    string getArr();
    void setRow(string frow, int x);
    void setClass(string fclass, int x);
    void setName(string fname, int x);
    string getFlightRow(int x);
    string getFlightClass(int x);
    string getFlightSeatName(int x);
    void bookSeat(string x, int y);
    void setCount();
    int getCount();
    int getEclass();
    int getBclass();
    void displayFlights();
};

void Flight::setFlight(string flight){
    flight_no = flight;
}

string Flight::getFlight(){
    return flight_no;
}

void Flight::setDate(string date){
    dateTime = date;
}

string Flight::getDate(){
    return dateTime;
}

void Flight::setDep(string dep){
    dep_airport = dep;
}

string Flight::getDep(){
    return dep_airport;
}

void Flight::setArr(string arr){
    arr_airport = arr;
}

string Flight::getArr(){
    return arr_airport;
}

void Flight::setRow(string frow, int x){
    dataSet[x].flightRow = frow;
}

void Flight::setClass(string fclass, int x){
    dataSet[x].flightClass = fclass;
}

void Flight::setName(string fname, int x){
    dataSet[x].seatNames = fname;
}

string Flight::getFlightRow(int x){
    return dataSet[x].flightRow;
}

string Flight::getFlightClass(int x){
    return dataSet[x].flightClass;
}

string Flight::getFlightSeatName(int x){
    return dataSet[x].seatNames;
}

void Flight::bookSeat(string x, int y){
    dataSet[y].seatNames = x;
}

void Flight::setCount(){
    int eClassCount = 0, bClassCount = 0, totalCount = 0;
    for(int i = 0; i < 60; ++i){
        if(dataSet[i].flightRow != "\0"){
            if(dataSet[i].flightClass == "E"){
                eClassCount += dataSet[i].seatNames.size();
                this->eCount = eClassCount;
            }
            else if(dataSet[i].flightClass == "B"){
                bClassCount += dataSet[i].seatNames.size();
                this->bCount = bClassCount;
            }
        }
    }
}

int Flight::getCount(){
    int x = 0;
        x = this->bCount + this->eCount; 
    return x;
}

int Flight::getEclass(){
    return eCount;
}

int Flight::getBclass(){
    return bCount;
}

void Flight::displayFlights(){
    cout << "Flight Name            : " << flight_no << endl;
    cout << "Departure Date & Time  : " << dateTime << endl;
    cout << "Departure Airport      : " << dep_airport << endl;
    cout << "Arrival Airport        : " << arr_airport << endl;
    setCount(); 
}

int main(){

    int opt, dataBlock = 0;
    bool flag = true;

    ifstream file("flights.txt");

    string line;

    if(file.is_open()){
        while(getline(file, line)){
            if(line == "\0")
            count++;
            else
            line_count++;
        }
    }
    else
    {
        cout << "ERROR: Unable to open the file !" << endl;
    }
    
    file.close();
    
    Flight obj[count];
    
    int dataBlockLineCounter = 0, dataBlockSeatLineCounter = 0, dataBlockCounter = 0;

    ifstream file1("flights.txt");
        if(file1.is_open()){
        while(getline(file1, line)){

            if(line != "\0"){
                ++dataBlockLineCounter;

                if(dataBlockLineCounter == 1)
                obj[dataBlockCounter].setFlight(line); 
                else if(dataBlockLineCounter == 2)
                obj[dataBlockCounter].setDate(line);
                else if(dataBlockLineCounter == 3)
                obj[dataBlockCounter].setDep(line);
                else if(dataBlockLineCounter == 4)
                obj[dataBlockCounter].setArr(line);
                else{
                istringstream xxx(line);
                string row, sclass, number;
                xxx >> row >> sclass >> number;
                if(line != "\0"){
                    obj[dataBlockCounter].setRow(row, dataBlockSeatLineCounter);
                    obj[dataBlockCounter].setClass(sclass, dataBlockSeatLineCounter);
                    obj[dataBlockCounter].setName(number, dataBlockSeatLineCounter);
                    ++dataBlockSeatLineCounter;
                }
                }
            } 
            else{
                ++dataBlockCounter;
                dataBlockLineCounter = 0;
                dataBlockSeatLineCounter = 0;
            }           
        }

        file1.close();
    }
    else cout << "ERROR: Unable to open the file !" << endl;

    do{
        cout << endl << "1: Display available flights." << endl;
        cout << "2: View flights" <<endl;
        cout << "3: Seat availability" << endl;
        cout << "4: Seat Booking" << endl;
        cout << "5: Exit" << endl << endl;
        cout << "Choose your option: ";
        cin >> opt;
        cout << endl;

        switch (opt)
        {
        case 1:
            for(int i = 0; i < count; ++i){ 
            obj[i].setCount();
            if(obj[i].getFlight() != "\0" && obj[i].getCount() >= 1){
                obj[i].displayFlights();
                cout << "Available B Class seats: " << obj[i].getBclass() << endl;
                cout << "Available E Class seats: " << obj[i].getEclass() << endl << endl;
                }
			}
            break;
        case 2:{
            string search;
            cout << "Enter Flight name           :  ";
            cin >> search;
        	cout << endl;
            bool flag;
            for(int i = 0; i < count; ++i){
                obj[i].setCount();
                if(obj[i].getFlight() == search){
                    {flag = true;
                    for(int j = 0; j < 60; ++j){
                        if(obj[i].getFlightRow(j) != "\0"){
                        if(obj[i].getFlightSeatName(j) != "\0")
                        cout << "Available seats in " << obj[i].getFlightRow(j) << "th Row: " << " " << obj[i].getFlightClass(j) << " " << obj[i].getFlightSeatName(j) << endl;}
                        }
                        cout << endl << "Available E Class seats    : " << obj[i].getEclass() << endl;
                        cout << "Available B Class seats    : " << obj[i].getBclass() << endl;
                        cout << "Arrival airport            : " << obj[i].getArr() << endl;
                        cout << "Departure airport          : " << obj[i].getDep() << endl;
                        cout << "Departure Date & Time      : " << obj[i].getDate() << endl << endl;
                        break;
                    }
                }
                    else flag = false;
                }
                if(!flag) cout << "ERROR: Keyword does not match!" << endl;
            }
            break;
        case 3:{
            string search;
            int seat;
            bool flag;
            cout << "Enter Flight name         : ";
            cin >> search;
            cout << "How many seats do you want? ";
            cin >> seat;
            for(int i = 0; i < count; ++i){
                if(obj[i].getFlight() == search){
                    flag = true;
                    obj[i].setCount();
                    if(obj[i].getCount() >= seat){
                        cout << "Available seats: " << endl;
                        for(int j = 0; j < 60; ++j){
                            if(obj[i].getFlightRow(j) != "\0"){
                                cout << "                 " << obj[i].getFlightRow(j) << " " << obj[i].getFlightClass(j) << " " << obj[i].getFlightSeatName(j) << endl;
                                }
                            }
                        break;   
                        }
                    else cout << endl << "Sorry!" << endl << "Only " << obj[i].getCount() << " seats available for you." << endl;
                    break;
                    }
                    else flag = false;
                }
                if(!flag) cout << "ERROR: Keyword does not match!" << endl;
            }
            break;
        case 4:{
                string search, UseatName, Urow;
                cout << "Enter the flight name: ";
                cin >> search;
                cout << "Enter the Row no     : ";
                cin >> Urow;
                cout << "Enter the Seat name  : ";
                cin >> UseatName;

                for(int i = 0; i < count; i++){
                    if(obj[i].getFlight() == search){
                        obj[i].setCount();
                        bool flag = false;
                        for(int j = 0; j < 60; ++j){
                            if(obj[i].getFlightRow(j) == Urow){
                                int found = (obj[i].getFlightSeatName(j)).find(UseatName);
                                if(found != string::npos){
                                    int x = (obj[i].getFlightRow(j)).size(), y = (obj[i].getFlightClass(j)).size();
                                    string seat = obj[i].getFlightSeatName(j);
                                    seat.erase(found,1);
                                    obj[i].bookSeat(seat, j);
                                    if(seat.size() == 0){
                                        obj[i].setRow("\0", j);
                                    }
                                    cout << "Seat allocation successfull" << endl;
                                    obj[i].setCount();
                                    break;
                                }
                                else cout << "ERROR: Seat is unavailable !" << endl;
                            }
                            if(flag)
                                break;
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
                    if(obj[i].getFlight() != "\0"){
                    out = obj[i].getFlight();
                    myfile << out << endl;;
                    out = obj[i].getDate();
                    myfile << out << endl;
                    out = obj[i].getDep();
                    myfile << out << endl;
                    out = obj[i].getArr();
                    myfile << out << endl;
                    for(int j = 0; j < 60; ++j){
                            if(obj[i].getFlightSeatName(j) != "\0"){
                                    myfile << obj[i].getFlightRow(j) << " " << obj[i].getFlightClass(j) << " " << obj[i].getFlightSeatName(j) << endl;
                            }
                    }
                    myfile << endl;}   
                    }
                    myfile.close();
                    return 0;
                }
                else cout << "ERROR: Unable to create the file" << endl;
        }
        break;

        default:
        	flag = false;
            break;
        }
    }
    while(flag);
}
