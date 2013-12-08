#ifndef OptionsModule
#define OptionsModule
#include <list>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <stdio.h>
using namespace std;

void WriteToFile(list<string> cfg, char *filename);
list<string>ReadConfigFromFile(char *filename);
#endif //OptionsModule