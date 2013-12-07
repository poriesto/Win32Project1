#ifndef StatModule
#define StatModule
#include <vector>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <stdio.h>
using namespace std;

typedef struct
{
	string name;
	int score;
}Stat;

vector<Stat> ReadFromFile(char *filename);
Stat CreateStat(string str);
string PrintToTextField(vector<Stat>::iterator iter);
string WriteToFile(char *filename, string score);
#endif //StatModule