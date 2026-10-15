//Eduardo Avila
//COMSC - 210 - 5293
//Lab 23 - Goat Manager 3001

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    list<Goat> trip;
    int choice;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    do {
        choice = main_menu();

        switch (choice) {
            case 1:
                add_goat(trip, names, colors);
                break;
            
            case 2:
                delete_goat(trip);
                break;
            
            case 3:
                display_trip(trip);
                break;
            
            case 4:
                cout << "Exiting Program..." << endl;
                break;
        }

    } while (choice != 4);
    
    return 0;
}

int main_menu(){
    int choice;

    cout << "\n*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Quit" << endl;
    cout << "Choice --> ";

    //edited so key letter input edge case is taken into account
    while (!(cin >> choice) || choice < 1 || choice > 4){
        cout << "ERROR! Please choose 1-4: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return choice;
}

void add_goat(list<Goat> &trip, string names[], string colors[]){
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];

    int age = rand() % (MAX_AGE + 1);

    Goat newGoat(name, age, color);
    trip.push_back(newGoat);

    cout << "\nNew Goat: " << name 
         << " successfully added. Yippee!" << endl; 
}

int select_goat(list<Goat> trip){
    //empty check first
    if (trip.empty()){
        cout << "\nTrip is empty. No goats here buddy." << endl;
        return 0;
    }

    //display submenu to select from
    display_trip(trip);

    int choice;
    cout << "\nSelect goat (1- " << trip.size() << "): ";

    while (!(cin >> choice) || choice < 1 || choice > trip.size()){
        cout << "\nERROR! Please choose 1-" << trip.size()
             << ": ";

        cin.clear();
        cin.ignore(10000, '\n');
    }

    return choice;
}

void delete_goat(list<Goat> &trip){
    //empty check first
    if (trip.empty()){
        cout << "\nTrip empty. Goats ran away." << endl;
        return;
    }

    int choice = select_goat(trip);

    list<Goat>::iterator it = trip.begin();

    for (int i = 1; i < choice; i++){
        it++;
    }

    trip.erase(it);
    
    cout << "\nGoat is GONE. Deletion success!" << endl;
}

void display_trip(list<Goat> trip){
    //empty check first
    if (trip.empty()){
        cout << "\nTrip is empty." << endl;
        return;
    }

    int goatNumber = 1;

    cout << endl;
    for (Goat goat : trip) {
        cout << "[" << goatNumber << "] " << goat.get_name()
             << " (" << goat.get_age() << ", " << goat.get_color()
             << ")" << endl;
        
        goatNumber++;
    }
}
