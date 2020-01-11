#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ifstream file("Flights.txt");
    int count =0, line_count = 0;
    string line;
    if(file.is_open()){
        while(getline(file, line)){
            if(line == "\0")
            count++;
            else
            {
                line_count++;
            }
            
        }
    }

    file.close();

    cout << count << endl;
    cout << line_count <<endl;

}