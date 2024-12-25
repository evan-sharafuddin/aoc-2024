//
// Created by shara on 12/24/2024.
//
//
// Created by shara on 12/21/2024.
//

#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <vector>

using namespace std;

// declare helper functions
void print_line( vector<int> & );
bool check_bounds( int, int );
bool check_increasing( int, int, bool );
bool check_invariants( vector<int> & );

// set param
#define MIN_DIF 1
#define MAX_DIF 3

int main() {

    ifstream f( "../inputs/day2.txt" );

    int safe_reports = 0;
    string line;

    // iterate through each line in the file
    while( getline( f, line ) ) {

        // load line into a vector
        istringstream iss ( line );
        int temp;

        vector<int> linev;
        while ( iss >> temp ) {
            linev.push_back( temp );
        }

        // check if reports are safe
        if ( !check_invariants( linev ) ) {

            // check if removing one element renders the report safe
            // current implementation is not efficent, but robust

            for ( int i = 0; i < linev.size(); i++ ) {
                auto linev_temp = linev;
                linev_temp.erase( linev_temp.begin() + i );
                if ( check_invariants( linev_temp ) ) {
                    // then the problem dampener worked!
                    ++safe_reports;
                    break;
                }
            }
        }
        else {
            ++safe_reports;
        }
    }

    cout << "Number of safe reports: " << safe_reports << endl;
    return 0;
}

bool check_invariants ( vector<int> & levels ) {

    auto cur = levels.begin();
    auto next = cur + 1;

    // check initial case
    // determine whether levels are increasing or decreasing
    bool increasing = *next - *cur > 0;
    // check bounds
    if ( !check_bounds( *cur, *next ) ) {
        // cout << "Bounds not satisfied: cur=" << *cur << ", next=" << *next << endl;
        return false;
    }

    // iterate through the rest of the levels
    ++cur;
    ++next;

    while( next != levels.end() ) {
        if ( !check_bounds( *cur, *next ) ) {
            // cout << "Bounds not satisfied: cur=" << *cur << ", next=" << *next << endl;
            return false;
        }

        if ( !check_increasing( *cur, *next, increasing ) ) {
            // cout << "Monotonicity not satisfied: cur=" << *cur << ", next=" << *next << endl;
            return false;
        }

        ++cur;
        ++next;
    }

    // if we are here, then entire vector satisfied conditions
    return true;
}


bool check_bounds( int cur, int next ) {
    int diff = abs( cur - next );
    return diff >= MIN_DIF && diff <= MAX_DIF; // will be true if this condition is satisfied
}

bool check_increasing( int cur, int next, bool increasing ) {
    if ( increasing ) return next > cur; // check increasing
    else return cur > next; // check decreasing
}

