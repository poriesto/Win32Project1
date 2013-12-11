#include "stdafx.h"
#include "OptionsModule.h"

void WriteToFile(list<string> cfg, char *filename)
{
	ofstream data;
	data.open(filename);
	if(!data.is_open() && !data.fail())
	{
	}
}

void CreateOptions(HWND hwnd, list<string>cfg)
{
	list<string>::iterator iter = cfg.begin();
	while(iter != cfg.end())
	{
		SendMessage(hwnd, LB_ADDSTRING, 0, (LPARAM)(LPSTR)iter->c_str());
		iter++;
	}
}

list<string>ReadConfigFromFile(char *filename)
{
	list<string> list;
	ifstream data;
	string tmp;
	data.open(filename);
	if(data.is_open() && !data.fail())
	{
		while(!data.eof())
		{
			getline(data, tmp);
			list.push_back(tmp);
		}
		data.close();
		return list;
	}
}