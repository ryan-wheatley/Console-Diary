#pragma once

std::string GotoLine(std::fstream& file, unsigned int num);
void loadFile();
void openEntry();
std::unique_ptr<std::string[]> getTime();
void createEntry();
void saveFile();
void displayEntries();