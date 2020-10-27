#include "MovieDetail.h"
#include "MovieTrie.h"
#include "TitleSplit.h"
#include "TitleExtend.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<set>
#include<map>
using std::getline;
using std::map;
using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;
using std::stringstream;
using std::vector;
using std::set;
MovieTrie MT;
map<MovieDetail*, int> ans;
map<string, MovieDetail*> moviesMap;
void MoviesMapInit(string fileName)
{
	ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		cout << "Error opening file";
		return;
	}
	int count = 0;
	char buffer[1024];
	char subbuf[1024];
	ifs.getline(buffer, 1024);
	while (!ifs.eof())
	{
		ifs.getline(buffer, 1024);
		int i;
		int len = strlen(buffer);
		for (i = 0; i < len; ++i)
		{
			if (buffer[i] < 0 || buffer[i]>256) continue;
			if (buffer[i] >= 'A' && buffer[i] <= 'Z')
			{
				buffer[i] = buffer[i] - 'A' + 'a';
			}
		}
		string s;
		stringstream ss(buffer);
		MovieDetail* temp = new MovieDetail();
		ss.getline(subbuf, 1024, '\t');
		temp->tconst = subbuf;
		ss.getline(subbuf, 1024, '\t');
		temp->titleType = subbuf;
		ss.getline(subbuf, 1024, '\t');
		temp->primaryTitle = subbuf;
		ss.getline(subbuf, 1024, '\t');
		temp->originalTitle = subbuf;
		ss.getline(subbuf, 1024, '\t');
		temp->isAdult = subbuf;
		ss.getline(subbuf, 1024, '\t');
		temp->startYear = subbuf;
		ss.getline(subbuf, 1024, '\t');
		temp->endYear = subbuf;
		ss.getline(subbuf, 1024, '\t');
		temp->runtimeMinutes = subbuf;
		ss >> temp->genres;
		moviesMap[temp->tconst] = temp;
		temp->titles.insert(TotalExtend(temp->primaryTitle));
		temp->titles.insert(TotalExtend(temp->originalTitle));
		count++;
		if (count % 10000 == 0) cout << "MoviesMap Inited:" << count << endl;
	}
}
void MovieTitleInit(string fileName)
{
	ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		cout << "Error opening file";
		return;
	}
	int count = 0;
	char buffer[1024];
	char subbuf[1024];
	ifs.getline(buffer, 1024);
	while (!ifs.eof())
	{
		ifs.getline(buffer, 1024);
		int i;
		int len = strlen(buffer);
		for (i = 0; i < len; ++i)
		{
			if (buffer[i] < 0 || buffer[i]>256) continue;
			if (buffer[i] >= 'A' && buffer[i] <= 'Z')
			{
				buffer[i] = buffer[i] - 'A' + 'a';
			}
		}
		string s;
		stringstream ss(buffer);
		string title;
		string movieId;
		ss.getline(subbuf, 1024, '\t');
		movieId = subbuf;
		ss.getline(subbuf, 1024, '\t');
		ss.getline(subbuf, 1024, '\t');
		title = subbuf;
		moviesMap[movieId]->titles.insert(TotalExtend(title));
		count++;
		if (count % 10000 == 0) cout << "MovieTitle Inited:" << count << endl;
	}
}
void TrieInit()
{
	
	int count = 0;
	for (auto  iter : moviesMap)
	{
		MT.Insert(iter.second);
		count++;
		if (count % 10000 == 0) cout << "MovieTrie Inited:" << count << endl;
	 }
}
void TitleSplit(string fileName)
{
	int i;
	ifstream ifs(fileName);
	ofstream ofs("splitedtitle.txt");
	int count = 1;
	char buffer[1024];
	ifs.getline(buffer, 1024);
	while (!ifs.eof())
	{
		ifs.getline(buffer, 1024);
		string s;
		s = buffer;
		if (s.length() < 18 || s[6] != '=' || s[17] != '=')
		{
			continue;
		}
		string titleId = s.substr(0, 18);
		string temp = s.substr(18);
		for (i = 0; i < temp.size(); ++i)
		{
			if (temp[i] < 0 || temp[i]>256) continue;
			if (temp[i] >= 'A' && temp[i] <= 'Z')
			{
				temp[i] = temp[i] - 'A' + 'a';
			}
		}
		set<string> ss;
		ss.insert(temp);
		ss = TotalSplit(ss);
		ofs << titleId << "\n" << ss.size() << endl;
		for (auto str : ss)
		{
			ofs << str << "\n";
		}
		count++;
		if (count % 10000 == 0) cout << "ProductTitle splited:" << count << endl;
	}
}
void AccSolve(string fileName)
{
	int i;
	int unmatchedCnt = 0;
	ifstream ifs(fileName);
	ofstream ofs("unmatchedtitle.txt");
	if (!ifs.is_open())
	{
		cout << "Error opening file";
		return;
	}
	int count = 1;
	char buffer[1024];
	bool matched = false;
	string titleId;
	while (ifs>>titleId)
	{
		matched = false;
		int subTitleNum = 0;
		ifs >> subTitleNum;
		ifs.get();
		int j;
		set<MovieDetail*> curSet;
		for (j = 0; j < subTitleNum; ++j)
		{
			string s;
			getline(ifs, s);
			s = TotalExtend(s);
			vector<MovieDetail*> v;
			MT.AccQuery(s, v);
			for (i = 0; i < v.size(); ++i)
			{
				curSet.insert(v[i]);
			}
		}
		if (curSet.empty())
		{
			unmatchedCnt++;
			ofs << titleId << endl;
		}
		for (auto ptr : curSet)
		{
			ans[ptr]++;
		}
		count++;
		if (count % 10000 == 0) cout << "ProductTitle solved:" << count << endl;
	}
	ofs << "unmatchedTitleNum:" << unmatchedCnt << endl;
}
void AnsStatistics()
{
	ofstream ofs("matcheddetail.txt");
	ofs << "movieNum:" << ans.size() << endl;
	ofs << "tconst\ttitleType\tprimaryTitle\toriginalTitle\tisAdult	\tstartYear\tendYear\truntimeMinutes\tgenres\tmatchedNum" << endl;
	for (auto it : ans)
	{
			ofs << it.first->tconst<<"\t"<<it.first->titleType<<"\t"<< it.first->primaryTitle<<"\t"<< it.first->originalTitle<< " \t" << it.first->isAdult<<"\t";
			ofs << it.first->startYear << "\t" << it.first->endYear << "\t" << it.first->runtimeMinutes << "\t" << it.first->genres << "\t" << it.second << endl;
	}
}
int main(void)
{
	TitleSplit("titles_all.txt");
	MoviesMapInit("tvmoviedata.tsv");
	MoviesMapInit("moviedata.tsv");
	MovieTitleInit("tvmovietitle.tsv");
	MovieTitleInit("movietitle.tsv");
	TrieInit();
	AccSolve("splitedtitle.txt");
	cout << ans.size() << endl;
	AnsStatistics();
}