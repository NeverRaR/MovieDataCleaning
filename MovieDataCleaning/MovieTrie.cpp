#include "MovieTrie.h"
#include "MovieDetail.h"
MovieTrie::MovieTrie()
{
	root = new MovieTrieNode();
}
void MovieTrie::Insert(MovieDetail* m)
{
	MovieTrieNode* curNode;
	for (auto str : m->titles)
	{
		curNode = root;
		string movieName = str;
		int i;
		for (i = 0; i < movieName.length(); ++i)
		{
			char ch = movieName[i];
			if (curNode->child[ch] == nullptr) curNode->child[ch] = new MovieTrieNode();
			curNode = curNode->child[ch];
		}
		if (curNode->matchedMovies == nullptr) curNode->matchedMovies = new set<MovieDetail*>();
		curNode->matchedMovies->insert(m);
	}	
}
void MovieTrie::AccQuery(const string& s, vector<MovieDetail*>& ans)
{
	MovieTrieNode* curNode = root;
	string movieName = s;
	int i;
	for (i = 0; i < movieName.length(); ++i)
	{

		char ch = movieName[i];
		curNode = curNode->child[ch];
		if (curNode == nullptr) return;
		if (i == movieName.length() - 1)
		{
			if (curNode->matchedMovies != nullptr )
			{
				for (auto ptr : *(curNode->matchedMovies))
				{
					ans.push_back(ptr);
				}
			}
		}
	}
}
