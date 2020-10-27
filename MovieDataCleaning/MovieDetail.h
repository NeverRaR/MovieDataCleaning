#pragma once
#include <string>
#include<set>
using std::set;
using std::string;
class MovieDetail
{
public:
	string tconst;
	string titleType;
	string primaryTitle;
	string originalTitle;
	set<string> titles;
	string isAdult;
	string startYear;
	string endYear;
	string runtimeMinutes;
	string genres;
};

