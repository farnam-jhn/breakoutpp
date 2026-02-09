#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include "getchar.h"
using namespace std;

extern string trCorner ;
extern string tlCorner ;
extern string brCorner ;
extern string blCorner ;
extern string paddeleLine ;
extern string horizontalLine ;
extern string verticalLine ;

/*
    history format:
    PlayerName, Best socre, Best socre time, Last score, Last score time
*/

void saveData(string name, int score){

    ifstream history_reader("src/history.txt");
    if(!history_reader.is_open()){
        cout << "ERROR OPENNING HISTORY!";
        return;
    }

    time_t now = time(nullptr);
    string date = ctime(&now);
    date.pop_back(); // delete \n at the end

    string output = "";
    bool new_player = true;

    string line;

    while(getline(history_reader, line)){

        int splitter[4];
        splitter[0] = line.find(",");
        splitter[1] = line.find(",", splitter[0] + 1);
        splitter[2] = line.find(",", splitter[1] + 1);
        splitter[3] = line.find(",", splitter[2] + 1);

        string player_name = line.substr(0, splitter[0]);
        int best_score = stoi(line.substr(splitter[0] + 1, splitter[1] - splitter[0] - 1));
        string best_score_date = line.substr(splitter[1] + 1, splitter[2] - splitter[1] - 1);
        int last_score = stoi(line.substr(splitter[2] + 1, splitter[3] - splitter[2] - 1));
        string last_score_date = line.substr(splitter[3] + 1);

        if(player_name == name){
            new_player = false;

            if(score >= best_score){
                best_score = score;
                best_score_date = date;
            }

            last_score = score;
            last_score_date = date;
        }

        output += player_name + "," +
                  to_string(best_score) + "," +
                  best_score_date + "," +
                  to_string(last_score) + "," +
                  last_score_date + "\n";
    }

    history_reader.close();

    if(new_player){
        output += name + "," +
                  to_string(score) + "," +
                  date + "," +
                  to_string(score) + "," +
                  date + "\n";
    }

    ofstream history_write("src/history.txt", ios::trunc);
    history_write << output;
    history_write.close();
}

void showHistory(){
    ifstream history("src/history.txt");
    if(!history.is_open()){
        cout << "ERROR OPENNING HISTORY!";
        return;
    }

    system("clear");
    const int tableWidth = 100;
    // Top border
    cout << endl << endl;
    cout << tlCorner;
    for(int i = 0; i < tableWidth; i++) cout << horizontalLine;
    cout << trCorner << endl;
    // Title
    cout << verticalLine
         << "\033[33m"  // yellow
         << setw(tableWidth) << left << "                                            GAME HISTORY"
         << "\033[0m" // reset
         << verticalLine << endl;
    // Separator
    cout << verticalLine;
    for(int i = 0; i < tableWidth; i++) cout << horizontalLine;
    cout << verticalLine << endl;
    // Header
    cout << verticalLine << " "
         << "\033[36m" // cyan
         << setw(15) << left << "Player"
         << setw(12) << "Best Score"
         << setw(25) << "Best Date"
         << setw(14) << "Last Score"
         << setw(32) << "Last Date"
         << "\033[0m" // reset
         << " " << verticalLine << endl;
    // Header separator
    cout << verticalLine;
    for(int i = 0; i < tableWidth; i++) cout << horizontalLine;
    cout << verticalLine << endl;
    string line;
    while(getline(history, line)){

        int splitter[4];
        splitter[0] = line.find(",");
        splitter[1] = line.find(",", splitter[0] + 1);
        splitter[2] = line.find(",", splitter[1] + 1);
        splitter[3] = line.find(",", splitter[2] + 1);

        string player_name = line.substr(0, splitter[0]);
        string best_score = line.substr(splitter[0] + 1, splitter[1] - splitter[0] - 1);
        string best_score_date = line.substr(splitter[1] + 1, splitter[2] - splitter[1] - 1);
        string last_score = line.substr(splitter[2] + 1, splitter[3] - splitter[2] - 1);
        string last_score_date = line.substr(splitter[3] + 1);

        cout << verticalLine << " "
             << "\033[32m" << setw(15) << left << player_name << "\033[0m" // green - reset
             << "\033[35m" << setw(12) << best_score << "\033[0m" // purple - reset
             << setw(16) << best_score_date << " "
             << "\033[35m" << setw(14) << last_score << "\033[0m" // purple - reset
             << setw(32) << last_score_date
             << " " << verticalLine << endl;
    }
    // Bottom border
    cout << blCorner;
    for(int i = 0; i < tableWidth; i++) cout << horizontalLine;
    cout << brCorner << endl;

    // escape
    getch();
}
