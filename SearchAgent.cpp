#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include "SearchAgent.h"
using namespace std;

int main(int argc, char* argv[])
{
    vector<string> guests;
    vector<string> together;
    vector<string> apart;
    ifstream infile;
    int numtables = 0;
    int tablesize = 0;
    size_t pos;
    string temp = "";
    string first = "";
    string second = "";
    //**********************************OPENING GUEST FILE************************************//
    if (argc > 1)
    {
        infile.open(argv[1]);
        if (!infile.is_open())
        {
            cout << "Error: Could not open provided guest file: " << argv[1] << endl;
            cout << "Terminating program." << endl;
            return 0;
        } else { //file opened successfully
            do {
                if (infile.eof()) break;
                getline(infile, temp);
                if (temp != "") guests.push_back(temp);
                temp = "";
            } while (!infile.eof());
        }
    } else {
        cout << "Error: Incorrect number of arguments provided." << endl;
        cout << "Please enter a single guestfile name after the executable." << endl;
        cout << "Terminating program." << endl;
        return 0;
    } //finished reading file
    infile.close();
    cout << endl << endl;
    //*********************************BEGIN USER INPUT PROCESSING****************************//
    cout << "This is the guest list: " << endl << endl;
    for (int i = 0; i < (int)guests.size(); i++)
    {
        cout << guests[i] << endl ;
    }
    cout << endl << endl;
    cout << "I have recorded " << guests.size() << " guests, Is this correct? (enter yes or no): ";
    cin >> temp;
    if (temp == "yes") cout << endl;
    else {
        cout << "Ok, please make the required adjustments to " << argv[1] << " and try again";
        cout << endl;
        cout << "Terminating program." << endl;
        return 0;
    }
    cout << "How many tables will there be at this event?" << endl;
    cin >> numtables;
    cout << "How many people per table will there be at this event?" << endl;
    cin >> tablesize;
    cout << endl;
    cout << "OK! So we have " << numtables << " tables seating " << tablesize << " people each.";
    cout << endl << endl;
    if (numtables*tablesize < (int)guests.size())
    {
        cout << "Error: You do not have enough seating for all of your guests, either adjust";
        cout << "your guestlist, or adjust your table numbers or table size" << endl;
        cout << "Terminating program." << endl;
        return 0;
    }
    cout << "Are there any guests who must sit together? (enter yes or no)" << endl;
    cin >> temp;
    if (temp == "yes")
    {
        cout << "\nPlease enter each pair of guests with a hyphen inbetween their names. Ex : ";
        cout << "Bob-Mary" << endl;
        cout << "Hit enter after each pair, enter 'done' when finished." << endl;
        while (temp != "done")
        {
            cin >> temp;
            if (temp == "done") break;
            //check that entered people exist in guestlist
            pos = temp.find('-');
            if (pos != string::npos)
            {
                first = temp.substr(0, pos);
                second = temp.substr(pos + 1);
                if (first == second)
                {
                    cout << "\nError: You entered the same guest twice" << endl;
                    cout << "Try entering the guests again:" << endl;
                    continue;
                }
            } else{
                cout << "Error: No hyphen detected, try again" << endl;
            }
            if ((in_vector(guests, first) == -1 )|| (in_vector(guests, second) == -1))
            {
                cout << "\nError: One of those guests doesn't appear in the guestlist." << endl;
                cout << "Try entering them again:" << endl;
            } else 
            {
                together.push_back(temp);
            }
        }
        cout << endl;
        cout << "The following guest pairs must be seated together: " << endl;
        for (int i = 0; i < (int)together.size(); i++)
        {
            cout << together[i] << endl;
        }
    }
    cout << endl;
    temp = "";
    cout << "Are there any guests who cannot sit together? (enter yes or no)" << endl;
    cin >> temp;
    if (temp == "yes")
    {
        cout << "\nPlease enter each pair of guests with a hyphen inbetween their names. Ex : ";
        cout << "Bob-Mary" << endl;
        cout << "Hit enter after each pair, enter 'done' when finished." << endl;
        while (temp != "done")
        {
            cin >> temp;
            if (temp == "done") break;
            //check that entered people exist in guestlist
            pos = temp.find('-');
            if (pos != string::npos)
            {
                first = temp.substr(0, pos);
                second = temp.substr(pos + 1);
                if (first == second)
                {
                    cout << "\nError: You entered the same guest twice" << endl;
                    cout << "Try entering the guests again:" << endl;
                    continue;
                }
            } else{
                cout << "Error: No hyphen detected, try again" << endl;
            }
            if ((in_vector(guests, first) == -1 )|| (in_vector(guests, second) == -1))
            {
                cout << "\nError: One of those guests doesn't appear in the guestlist." << endl;
                cout << "Try entering them again:" << endl;
            } else 
            {
                apart.push_back(temp);
            }
        }
        cout << endl;
        cout << "The following guest pairs must not be seated apart: " << endl;
        for (int i = 0; i < (int)apart.size(); i++)
        {
            cout << apart[i] << endl;
        }
    } else if (temp == "no"){
        cout << "Ok, proceeding with program" << endl;
    
    }
    //*****************************DONE USER INPUT PROCESSING*********************************//
    search(guests, together, apart, numtables, tablesize);
    //clean up!
    guests.clear();
    together.clear();
    apart.clear();
    return 0;
}

//initializes the domain (all possible guests) using the guest vector, g .
//pre process guestlist by ordering based on if guests appear in constraints or not
//guests that are present in both together (t) and apart (a) will be at the front of the 
//list, Guests in one of t or a will be in the middle, Guests that arent present at all 
//in the constraints will be at the back
bool search(vector<string> g, vector<string> t, vector<string> a, int nt, int ts)
{

    string guestlist[g.size()];
    vector<string> prioritized;
    vector<string> no_constraints;
    int found = 0;
    string temp = "";

    for (int i = 0; i < (int)g.size(); i++)
    {
        for (int x = 0; x < (int)t.size(); x++)
        { //first see if a match in together contraints
            temp = t[x];
            if (temp.find(g[i]) != string::npos) 
            {
                found++;            }
        } //then see if a match in apart constraints
        for (int y = 0; y < (int)a.size(); y++)
        {
            temp = a[y];
            if (temp.find(g[i]) != string::npos)
            {
                found++;
            }
        }
        if (found == 0) 
        {
            no_constraints.push_back(g[i]);
        } else if (found == 1) 
        {
            prioritized.push_back(g[i]); //medium priority goes to back
        } else if (found == 2) 
        {
            prioritized.insert(prioritized.begin(), g[i]); //top priority to front
        }
        found = 0; //reset found for the next guest
    }
    //append the no_constraints to the back of the prioritized vector
    prioritized.insert(prioritized.end(), no_constraints.begin(), no_constraints.end());
    for (int i = 0; i < (int)prioritized.size(); i++)
    {
        guestlist[i] = prioritized[i];
    }
    Problem init(guestlist, nt, t, a);
    
    //opening up arrangement to have numtable vectors, intializing assign vector to hold result
    init.arrangement.resize(nt);
    vector<vector<string>> assign;
    assign.resize(nt);
    init.arrangement = RecursiveBacktracking(init, assign, g, nt, ts);
    if(is_complete(init.arrangement, g, nt, ts)) 
    {
        cout << "\n****************************SOLUTION FOUND***************************" << endl;
        display_assignment(init, nt);
    }
    //cleanup
    assign.clear();
    prioritized.clear();
    no_constraints.clear();
    return true;
}

// We are not allowing inconsistent assignments, so as long as the assignment is complete, we are
// done
//recursively searches for a complete assignment while only making consistant moves according
//to the constraints.
//Uses two heuristics, Minimum Remaining Values (Assigns variable to the table with the lowest 
//amount of empty seats) and Most Constraining Variable (Assigns new variables by popping the 
//top one off the problem.available_values vector, which has been pre sorted by most to least
//constraints)
vector<vector<string>> RecursiveBacktracking(Problem &problem, vector<vector<string>> assignment, vector<string> guests, int nt, int ts)
{
    problem.recursion_max++;
    if (problem.recursion_max >= 200)
    {
        cout << endl;
        cout << "NO SOLUTION" << endl;
        exit(0);
    }

    bool complete = false;
    if (is_complete(assignment, guests, nt, ts))
    {
        complete = true;
        problem.arrangement = assignment;
        return assignment;
    }
    int pos = 0;
    vector<vector<string>> result;
    vector<string>::iterator it;
    if (complete == false)
    {
        for (it = problem.available_values.begin(); it != problem.available_values.end(); it++)
        {
            string var = *it;
            // make a copy of the problem before we make changes so we can revert back
            Problem pcopy = problem;
            int assign_table = 0;
            // checking which table we can place var at. Check : in domain + table isnt full
            int can_place = 0; // if 1, we can place, if 0 we cannot
            int LRV = -1;      // used to find out which table has the least remaining values
            for (assign_table = 0; assign_table < nt; assign_table++)
            { // if table isnt full, we can consider it
                // of all possible tables, we want to select the one that has the least remaining
                // values as a heuristic
                if ((int)assignment[assign_table].size() < ts)
                {
                    pos = in_vector(problem.domain[assign_table], var);
                    if (pos != -1)
                    {
                        can_place = 1;
                        if (LRV == -1)
                        {
                            LRV = assign_table;
                        }
                        else if ((int)assignment[assign_table].size() > (int)assignment[LRV].size())
                        {
                            LRV = assign_table;
                        }
                    }
                }
            }
            assign_table = LRV;
            // if position returned -1, we never found an assignable table, NO SOLUTION
            if (can_place == 0)
            {
                cout << endl;
                cout << "NO SOLUTION" << endl;
                problem = pcopy;
                exit(0);
            }
            // we can proceed to assign this variable to assign_table because its in the domain
            assignment[assign_table].push_back(var);
            // check constraints, assign together pair to same table (by making sure pair are 
            // in domain together) remove apart pair from domain of table
            vector<pair<string, string>>::iterator constraints_it;
            for (constraints_it = problem.together.begin(); constraints_it != problem.together.end(); constraints_it++)
            {
                if (constraints_it->first.find(var) != string::npos)
                {
                    // remove its partner from all other domains aside from the one we just assigned it to
                    for (int r = 0; r < nt; r++)
                    {
                        if (r != assign_table)
                            problem.remove_val(problem.domain[r], constraints_it->second);
                    }
                }
                if (constraints_it->second.find(var) != string::npos)
                {
                    // remove its partner from all other domains aside from the one we just assigned it to
                    for (int r = 0; r < nt; r++)
                    {
                        if (r != assign_table)
                            problem.remove_val(problem.domain[r], constraints_it->first);
                    }
                }
            }
            // if var has a person they cannot sit with, we will remove them from this tables
            // domain that we placed var at
            for (constraints_it = problem.apart.begin(); constraints_it != problem.apart.end(); constraints_it++)
            {
                // cout << "!! " << var << endl;
                if (constraints_it->first.find(var) != string::npos)
                {
                    problem.remove_val(problem.domain[assign_table], constraints_it->second);
                }
                if (constraints_it->second.find(var) != string::npos)
                {
                    problem.remove_val(problem.domain[assign_table], constraints_it->first);
                }
            }
            // remove var from availablevalues and domain for all tables
            problem.available_values.erase(it);
            vector<vector<string>>::iterator it2;
            for (it2 = problem.domain.begin(); it2 != problem.domain.end(); it2++)
            {
                problem.remove_val(*it2, var);
            }
            result = RecursiveBacktracking(problem, assignment, guests, nt, ts);
            if (is_complete(result, guests, nt, ts))
            {
                problem.arrangement = assignment;
                return result;
            }
            // remove assignment
            assignment[assign_table].pop_back();
            problem = pcopy; // restoring back to before
        }
    }
    return assignment;
}

//checks and assignment against the original guest list to make sure all of the guests have been
//seated. Rertuns true if the assignment is complete (assumes the assignment is consistent).
//false otherwise
bool is_complete(vector<vector<string>> assignment, vector<string> guests, int nt, int ts)
{
    //for every position in the final arrangement, pop off the corresponding
    //guestist entry. The guestlist should be empty after going through the whole arrangement
    vector<string>::iterator it = guests.begin();
    //first check to make sure there are the same number of guests in the final arrangement
    //as the initial guestlist
    int sum = 0;
    int filled_tables = assignment.size();
    if (filled_tables == 0) return false;
    for (int s = 0; s < filled_tables; s++)
    {
        sum += assignment[s].size();
    }
    if (sum < (int)guests.size()) return false;
    for (int i = 0; i < nt; i++)
    {
        for (int j = 0; j < ts; j++)
        {
            for (int x = 0; x < (int)guests.size(); x++)
            {
                if(guests[x] == assignment[i][j]) guests.erase(it);
                it++;
            }
            it = guests.begin();
        }
    }
    if (guests.empty()) 
    {
        return true;
    } else {
        return false;
    }
}

//displays an assignment (a vector of vectors of strings, or a 2D array) by calling on Problem 
//member function display_vector()
void display_assignment(Problem problem, int nt)
{
    for (int i = 0; i < nt; i++)
    {
        cout << endl;
        cout << "*******************************Table " << i+1 << "*******************************" << endl;
        problem.display_vector(problem.arrangement.at(i));
        cout << "*********************************************************************" << endl;
        cout << endl;
    }
}

//returns position in vector that val is found, or -1 if not
int in_vector(vector<string> v, string val)
{
    int count = 0;
    vector<string>::iterator it;
    for (it = v.begin(); it != v.end(); it++)
    {
        if (*it == val) return count;
        count++;
    }
    return -1;
}


