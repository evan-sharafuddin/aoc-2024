//
// Created by shara on 12/21/2024.
//

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool check_bounds( int, int );
bool check_increasing( int, int, bool );
bool check_invariants( int, int, bool );

int main() {

    ifstream f ( "../inputs/day2.txt" );

    int safe_reports = 0;
    string line;
    int cur, next;
    bool increasing;
    bool safe = true;

    // set param
    #define MIN_DIF 1
    #define MAX_DIF 3

    while ( getline( f, line ) ) {
        istringstream iss( line );

        // start with the first two elements in the list
        // INVARIANT: will always have two or more elements
        iss >> cur >> next;

        // set increasing
        increasing = next > cur;
        if ( !check_invariants( cur, next, increasing ) ) {
            safe = false;
            continue; // do not increment safe counter
        }

        cur = next; // set up for next loop iteration

        // iterate through the rest of the list
        while ( iss >> next ) {
            if ( !check_invariants( cur, next, increasing ) ) {
                safe = false;
                break; // do not increment safe counter
            }

            cur = next; // set up for next loop iteration
        }

        // if we are here, then report is safe
        if ( safe ) ++safe_reports;
        safe = true;
    }

    cout << "Number of safe reports: " << safe_reports << endl;
    return 0;
}

bool check_invariants ( int cur, int next, bool increasing ) {
    if ( !check_bounds( cur, next ) ) {
        cout << "Bounds not satisfied: cur=" << cur << ", next=" << next << endl;
        return false;
    }

    if ( !check_increasing( cur, next, increasing ) ) {
        cout << "Monotonicity not satisfied: cur=" << cur << ", next=" << next << endl;
        return false;
    }

    // cout << "Invariants satisfied: cur=" << cur << ", next=" << next << endl;
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