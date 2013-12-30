#ifndef StatModule
#define StatModule
#include <list>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef struct
{
	string name;
	int score;
}Stat;

list<Stat> ReadFromFile(char *filename);
Stat CreateStat(string str);
string PrintToTextField(list<Stat>::iterator iter);
string WriteToFile(char *filename, string score);
#endif //StatModule