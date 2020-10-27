#include "TitleExtend.h"
#include "TitleSplit.h"
string StringRelpace(string s, string x, string y)
{
    string temp = "";
    int i, j;
    for (i = 0; i < s.length(); ++i)
    {
        for (j = 0; j < x.length(); ++j)
        {
            if (s[i + j] != x[j])
            {
                temp.push_back(s[i]);
                break;
            }
            if (j == x.length() - 1)
            {
                temp += y;
                i = i + j;
            }
        }
    }
    return temp;
}

string PunctuationRemove(string s)
{
    int i;
    string temp;
    for (i = 0; i < s.length(); ++i)
    {
        if (s[i] >= 0 && s[i] <= 256 && ispunct(s[i]))
        {
            continue;
        }
        else
        {
            temp.push_back(s[i]);
        }
    } 
    return temp;
}

string TotalExtend(string s)
{
    s = StringRelpace(s, "and", "&");
    s = StringRelpace(s, "the", "");
    s = PunctuationRemove(s);
    s = BlankClean(s);
    return s;
}
