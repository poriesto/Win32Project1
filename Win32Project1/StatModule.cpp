#include "stdafx.h"
#include "StatModule.h"
#define LENGTH_SCORE 10

vector<Stat> ReadFromFile(char *filename)
{
	ifstream data;
	vector<Stat> V;
	string str;
	Stat temp;
	data.open(filename);

	if(data.is_open() && !data.fail())
	{
		while(!data.eof())
		{
			getline(data, str);
			temp = CreateStat(str);
			V.push_back(temp);
		}
		data.close();
		return V;
	}
	else
	{
		throw(data.bad()); 
	}
}
//True alg
/*
Stat CreateStat(string str){
	Stat stat;
	int pos = 0, cpos = 0, last;
	string word, score;
	int tmp;
	cpos = str.find(" ", pos);
	word = str.substr(pos, cpos - pos);
	pos = str.find(word);
	score = str.substr(pos);
	tmp = atoi(score.c_str());
	stat.name = word;
	stat.score = tmp;
	return stat;
}*/
//not true alg
Stat CreateStat(string str){
	Stat stat;
	int pos = 0, cpos = 0, last;
	string word, score;
	int tmp;
	cpos = str.find(" ", pos);
	word = str.substr(pos, cpos - pos);
	score = str.substr(cpos, LENGTH_SCORE);
	tmp = atoi(score.c_str());
	stat.name = word;
	stat.score = tmp;
	return stat;
}

string PrintToTextField(vector<Stat>::iterator iter)
{
		string tmpName(iter->name);
		int tmpScore(iter->score);
		char tmp2[10];
		_itoa_s(tmpScore, tmp2, 10, 10);
		string tmp = tmpName + " " + tmp2;
		return tmp;
}