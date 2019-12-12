#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<boost/lexical_cast.hpp>
using namespace std;

struct Journal
{
	string title;
	vector<string> entries;
	
	//declare an explicit constructor to avoid 
	//implicit conversion
	explicit Journal(const string &title)
		:title{title}
	{
	
	}

	void add(const string & entry);

	//persistence is a seperate concern
	void save(const string &filename);
};

void Journal::add(const string &entry)
{
	static int count = 1;
	entries.push_back(boost::lexical_cast<string>(count++)+": " + entry);
}

//not a good idea
void Journal::save(const string &filename)
{
	ofstream ofs(filename);
	for(auto &s : entries){
		ofs<<s<<endl;
	}
}

//a good idea
struct PersistenceManager
{
	static void save(const Journal &j, const string &filename)
	{
		ofstream ofs(filename);
		for( auto &s : j.entries)
		{
			ofs<<s<<endl;
		}
	}

};

int main()
{
	Journal journal{"Dear Diary"};
	journal.add("I ate a bug");
	journal.add("I cired today");

	PersistenceManager pm;
	pm.save(journal, "diary.txt");

}
