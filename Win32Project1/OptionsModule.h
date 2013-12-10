#ifndef OptionsModule
#define OptionsModule
#include <list>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void WriteToFile(list<string> cfg, char *filename);
void CreateOptions(HWND hwnd, list<string>cfg);
list<string>ReadConfigFromFile(char *filename);
#endif //OptionsModule