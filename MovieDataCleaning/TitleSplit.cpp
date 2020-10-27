#include "TitleSplit.h"
string BlankClean(string s)
{
	int beg, end;
	string ans;
	for (beg = 0; beg < s.size(); ++beg)
	{
		if (s[beg] != ' ') break;
	}
	for (end = s.size() - 1; end > beg; --end)
	{
		if (s[end] != ' ') break;
	}
	return s.substr(beg, end - beg + 1);
}
vector<string> BracketSplit(string s,char leftch,char rightch)
{
	int i;
	int preE = -1;
	int leftCnt = 0;
	string temp;
	vector<string> ans;
	for (i = 0; i < s.size(); i++)
	{
		if (i == s.size() - 1)
		{
			if(s[i]==rightch) ans.push_back(BlankClean(s.substr(preE + 1, i - preE-1)));
			else ans.push_back(BlankClean(s.substr(preE + 1, i - preE)));
			continue;
		}
		if (s[i] == leftch)
		{
			if (i - preE == 1)
			{
				leftCnt++;
				continue;
			}
			if (leftCnt == 0)
			{
				ans.push_back(BlankClean(s.substr(preE + 1, i - preE - 1)));
				preE = i;
			}
			leftCnt++;
		}
		if (s[i] == rightch)
		{
			leftCnt--;
			if (leftCnt == 0)
			{
				ans.push_back(BlankClean(s.substr(preE + 1, i - preE-1)));
				preE = i;
			}
		}
	}
	return ans;
}

//需要将以下符号作为分隔符号
//      ,        /       \         |     
vector<string> SeparateSplit(string s, char ch)
{
	vector<string> ans;
	string temp;
	int i;
	for (i = 0; i < s.length(); ++i)
	{
		if (s[i] != ch) temp.push_back(s[i]);
		else
		{
			if (!temp.empty()) ans.push_back(BlankClean(temp));
			temp.clear();
		}
	}
	if (!s.empty())
	{
		ans.push_back(BlankClean(temp));
	}
	return ans;
}

vector<string> MidSplit(string s, char ch)
{
	vector<string> ans;
	string temp;
	int i;
	for (i = 0; i < s.length(); ++i)
	{
		if (s[i] == ch)
		{
			ans.push_back(BlankClean(s.substr(0, i)));
			ans.push_back(BlankClean(s.substr(i+1)));
		}
	}
	return ans;
}

vector<string> NumSplit(string s)
{
	vector<string> ans;
	string temp;
	int i;
	for (i = 0; i < s.length(); ++i)
	{
		if (s[i]<'0'||s[i]>'9')
		{
			temp.push_back(s[i]);
		}
		else
		{
			if (!temp.empty()) ans.push_back(BlankClean(temp));
		}
	}
	return ans;
}
set<string> TotalSplit(set<string> ss)
{
	vector<string> v;
	set<string> tempSet;
	for (auto str : ss)
	{
		v = BracketSplit(str);
		for (auto vstr : v)
		{
			tempSet.insert(vstr);
		}
		v = BracketSplit(str,'[',']');
		for (auto vstr : v)
		{
			tempSet.insert(vstr);
		}
		v = BracketSplit(str, '{', '}');
		for (auto vstr : v)
		{
			tempSet.insert(vstr);
		}
		v = SeparateSplit(str);
		for (auto vstr : v)
		{
			tempSet.insert(vstr);
		}
		v = SeparateSplit(str,'\\');
		for (auto vstr : v)
		{
			tempSet.insert(vstr);
		}
		v = SeparateSplit(str, ';');
		for (auto vstr : v)
		{
			tempSet.insert(vstr);
		}
		v = SeparateSplit(str, '/');
		for (auto vstr : v)
		{
			tempSet.insert(vstr);
		}
		v = SeparateSplit(str, '|');
		for (auto vstr : v)
		{
			tempSet.insert(vstr);
		}
		v = SeparateSplit(str, '&');
		for (auto vstr : v)
		{
			tempSet.insert(vstr);
		}
		v = SeparateSplit(str, '+');
		for (auto vstr : v)
		{
			tempSet.insert(vstr);
		}
		v = MidSplit(str, '-');
		for (auto vstr : v)
		{
			tempSet.insert(vstr);
		}
		v = MidSplit(str, ':');
		for (auto vstr : v)
		{
			tempSet.insert(vstr);
		}
		v = NumSplit(str);
		for (auto vstr : v)
		{
			tempSet.insert(vstr);
		}
	}
	if (tempSet.size() == ss.size())
	{
		ss.erase("");
		return ss;
	}
	return TotalSplit(tempSet);
}
