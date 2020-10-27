#pragma once
#include<set>
#include<string>
#include<vector>
using std::vector;
using std::string;
using std::set;
string BlankClean(string s);
vector<string> BracketSplit(string s,char leftch='('  ,char rightch=')');
vector<string> SeparateSplit(string s, char ch = ',');
vector<string> MidSplit(string s, char ch = '-');
set<string> TotalSplit(set<string> ss);
