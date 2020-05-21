// DiaryApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
// A simple console application that allows you to save, lead and delete diary entries. Currently unfinished.
// Ryan Wheatley
// 05/2020
#include <iostream>
#include <ctime>
#include <fstream>
#include <limits>
#include <thread>
#include <chrono>
#include <string>
#include<sstream>
#include <vector>
#include "Header.h"
int main() {
    loadFile();
    while (true) {
        system("CLS");
        std::cout << "WELCOME TO YOUR CONSOLE DIARY" << std::endl;
        std::cout << '\n';
        std::cout << "Enter 1 to make a new entry." << std::endl;
        std::cout << "Enter 2 to read or delete a past entry." << std::endl;
        std::cout << '\n';
        char answer;
        std::cin >> answer;
        if (answer == '1') {
            createEntry();
        }
        else if (answer == '2') {
            displayEntries();
            openEntry();
        }
        saveFile();
    }
    return 0;
}
//getTime function returns current day, month, year.
std::unique_ptr<std::string[]> getTime() {
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    std::unique_ptr<std::string[]> time = std::unique_ptr<std::string[]>(new std::string[3]());
    time[0] = std::to_string(timeinfo->tm_mday);
    time[1] = "0" + std::to_string(timeinfo->tm_mon + 1);
    time[2] = "20" + std::to_string(timeinfo->tm_year - 100);
    return time;
}
struct Entries {
    std::string day;
    std::string month;
    std::string year;
    std::string entry;
    //Entries() { time = getTime(); }
    Entries(std::string d, std::string m, std::string y, std::string e) { day = d; month = m, year = y; entry = e; };
    ~Entries() {};
};
std::vector<Entries>EntriesVec;
void loadFile() {
    std::string entry[4];
    std::ifstream myfile("example.txt");
    if (myfile.is_open())
    {
        std::string empty;
        int lineNo = 0;
        while (std::getline(myfile, empty)) {
            lineNo++;
        }
        if (lineNo > 0) {
            std::string entryNo;
            std::fstream file("example.txt");
            entryNo = GotoLine(file, 1);
            int n = std::stoi(entryNo);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 4; j++) {
                    entry[j] = GotoLine(file, 4 * i + j + 2);
                }
                std::shared_ptr<Entries> ent = std::make_shared<Entries>(entry[0], entry[1], entry[2], entry[3]);
                EntriesVec.push_back(*ent);
            }
            myfile.close();
        }
    }
}
std::string GotoLine(std::fstream& file, unsigned int num) {
    file.seekg(std::ios::beg);
    std::string line;
    for (int i = 0; i < num - 1; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::getline(file, line);
    return line;
}
void openEntry() {
    //Gets selection from menu
    int entryNo;
    std::cout << '\n';
    std::cout << "Enter the number of the entry you wish to open:";
    std::cin >> entryNo;
    system("CLS");
    entryNo--;
    //Displays date 
    std::cout << EntriesVec[entryNo].day << ' ' << EntriesVec[entryNo].month << ' ' << EntriesVec[entryNo].year << std::endl;
    std::cout << '\n';
    //Print the entry to the console
    int charecter = 0;
    int pause;
    while (EntriesVec[entryNo].entry[charecter] != '\0') {
        if (EntriesVec[entryNo].entry[charecter] == '.') { pause = 400; }
        else { pause = 50; }
        std::cout << EntriesVec[entryNo].entry[charecter];
        std::this_thread::sleep_for(std::chrono::milliseconds(pause));
        charecter++;
    }
    //delete entry option
    std::cout << '\n';
    std::cout << '\n';
    std::cout << "Delete this Entry: Y/N?";
    char answer;
    std::cin >> answer;
    if (toupper(answer) == 'Y') {
        EntriesVec.erase(EntriesVec.begin() + entryNo);
    }
}
//Gets a new diary entry from the user, adds it to vector of entries
void createEntry() {
    system("CLS");
    auto date = getTime();
    std::cout << date[0] << ' ' << date[1] << ' ' << date[2] << "        (Press enter to save)" << std::endl;
    std::cout << '\n';
    std::string bug;                  //for some reason if this isnt here, the enrter key from the previous
    std::getline(std::cin, bug);      //  input triggers the nect cin and creates a blank entry 
    std::string entry;
    std::getline(std::cin, entry);
    std::unique_ptr<Entries> ent = std::make_unique<Entries>(date[0], date[1], date[2], entry);
    EntriesVec.push_back(*ent);
}
void saveFile() {
    std::string entry[4];
    std::ifstream myfile("example.txt");
    if (myfile.is_open())
    {
        std::fstream File;
        File.open("example.txt");
        std::string empty;
        int n = EntriesVec.size();
        File << n << '\n';
        for (int i = 0; i < n; i++) {
            File << EntriesVec[i].day + '\n';
            File << EntriesVec[i].month + '\n';
            File << EntriesVec[i].year + '\n';
            File << EntriesVec[i].entry + '\n';
        }
        myfile.close();
    }
}
void displayEntries() {
    system("CLS");
    int EntryNo = 0;
    for (auto i : EntriesVec) {
        EntryNo++;
        std::cout << EntryNo << ". " << i.day << ' ' << i.month << ' ' << i.year << std::endl;
    }
}