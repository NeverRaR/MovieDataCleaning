#pragma once
#include<vector>
#include<string>
#include<map>
#include<set>
using std::set;
using std::vector;
using std::string;
using std::map;
class MovieDetail;
class MovieTrieNode
{
public:
    MovieTrieNode()
    {
    }
    map<int,MovieTrieNode*> child;
    set<MovieDetail*>* matchedMovies=nullptr;
};
class QueryNode
{
public:
    string name;
    MovieDetail* m;
};
class MovieTrie
{
public:
    MovieTrie();
    void  Insert(MovieDetail* m);
    void AccQuery(const string& s, vector<MovieDetail*>& ans);
private:
    MovieTrieNode* root;
};
