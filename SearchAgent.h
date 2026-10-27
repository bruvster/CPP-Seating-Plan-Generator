#ifndef _S_A_HEADER_
#define _S_A_HEADER_

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

class Problem {
    public:
    int recursion_max = 0;
    vector<pair<string, string>> together;
    vector<pair<string, string>> apart;
    vector<vector<string>> arrangement;
    vector<vector<string>> domain;
    vector<string> available_values;
    Problem(string guests[], int num_tables, vector<string> t, vector<string> a){ //constructor
        int count = 0;
        while (guests[count] != "\0")
        {
            available_values.push_back(guests[count]);
            count++;
        }
        for (int i = 0; i < num_tables; i++)
        {// each position in domain is its own table, each table has its own domain
        //every table starts off with all available guests as domain
            domain.push_back(available_values);
        }
        //parse out pair names from a (names either side of '-') and put them in vector pair
        size_t pos;
        string first = "";
        string second = "";
        count = 0;
        for (int x = 0; x < (int)t.size(); x++)
        {
            pos = t[x].find('-');
            if (pos != string::npos)
            {
                first = t[x].substr(0, pos);
                second = t[x].substr(pos+1);
                together.push_back(make_pair(first, second));
            }
        }
        for (int y = 0; y < (int)a.size(); y++)
        {
            pos = a[y].find('-');
            if (pos != string::npos)
            {
                first = a[y].substr(0, pos);
                second = a[y].substr(pos+1);
                apart.push_back(make_pair(first, second));
            }
        }
    }
    Problem(const Problem &copy) 
    {
        available_values = copy.available_values;
        arrangement = copy.arrangement;
        domain = copy.domain;
        together = copy.together;
        apart = copy.apart;
        recursion_max = copy.recursion_max;
	}
    ~Problem(){ //destructor
        domain.clear();
        together.clear();
        apart.clear();
        arrangement.clear();
        domain.clear();
        available_values.clear();
    }
    void display_vector(vector<string> v)
    {
        for (int i = 0; i < (int)v.size(); i++)
        {
            cout << v[i] << endl;
        }
    }
    void remove_val(vector<string> &v, string val)
    {
        vector<string>::iterator it;
        for (it = v.begin(); it != v.end(); it++)
        {
            if ((*it == val))
            {
                v.erase(it);
                return;
            }
        }
    }
    void operator= (const Problem& P) 
    { 
        available_values = P.available_values;
        arrangement = P.arrangement;
        domain = P.domain;
        together = P.together;
        apart = P.apart;
        recursion_max = P.recursion_max;
    } 
};

vector<vector<string>> RecursiveBacktracking(Problem &problem, vector<vector<string>> assignment, vector<string> guests, int nt, int ts);

int in_vector(vector<string> v, string val);

bool search(vector<string> g, vector<string> t, vector<string> a, int nt, int ts);

bool is_complete(vector<vector<string>> assignment, vector<string> guests, int nt, int ts);

void display_assignment(Problem problem, int nt);

#endif