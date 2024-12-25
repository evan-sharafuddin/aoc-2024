//
// Created by shara on 12/21/2024.
//

#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <vector>

using namespace std;

bool check_bounds( int, int );
bool check_increasing( int, int, bool );
bool check_invariants( int, int, bool );
bool check_all_invariants ( vector<int> &, int );

int main() {

    ifstream f ( "../test_inputs/day2.txt" );

    int safe_reports = 0;
    string line;

    int prev, cur, next, next_next;
    bool increasing;
    bool safe = true;
    bool dampener_used = false; // can only use this once!

    // set param
    #define MIN_DIF 1
    #define MAX_DIF 3

    while ( getline ( f, line ) ) {
        istringstream iss ( line );
        int temp;

        vector<int> linev;
        while ( iss >> temp ) {
            linev.push_back( temp );
        }

        // go through each element in the vector
        // if invariants fail, check if removing cur or next will fix the issue

        // index through, current is at i, next at i+1

        // CASE 1
        cout << "new line" << endl;
        for ( auto it = linev.begin(); it != linev.end(); it++ ) {
            cout << *it << " ";
        }
        cout << endl;

        cur = linev[0];
        next = linev[1];
        next_next = linev[2];

        increasing = next - cur > 0;
        // increasing doesn't matter here, so we should only check bounds
        if ( !check_bounds( cur, next ) ) {
            // check if returning cur or next works. If not, then there is nothing we can do
            if ( check_all_invariants( linev, cur ) ) {
                // works when remove next
                linev.erase( std::next( linev.begin(), 1)); // get rid of the next element
                increasing = next_next - cur > 0;
                safe_reports++;
                break;
            }
            else if ( check_all_invariants( linev, next ) ) {
                // works when remove cur
                linev.erase( std::next( linev.begin(), 1)); // get rid of the cur element
                increasing = next_next - next > 0;
                safe_reports++;
                break;
            }
            else {
                // out of luck, don't increment safe_reports
                break;
            }
        }

        // CASE 2
        cout << "case 2" << endl;
        auto it = std::next( linev.begin(), 1 );

        while ( it != linev.end() - 1 ) {

            for ( auto it = linev.begin(); it != linev.end(); it++ ) {
                cout << *it << " ";
            }
            cout << endl;

            cur = *it;
            next = *(it + 1);
            prev = *(it - 1);
            next_next = *(it + 2);

            // check invariants
            if ( !check_invariants( cur, next, increasing ) ) {
                // print vector

                // invariants not satisfied
                // check invariants with removing cur
                if ( check_invariants( prev, next, increasing ) && !dampener_used ) {
                    dampener_used = true;
                    linev.erase( it ); // get rid of cur
                }
                else if ( check_invariants( cur, next_next, increasing ) && !dampener_used ) {
                    dampener_used = true;
                    linev.erase( it + 1 ); // get rid of next
                }
                else {
                    // cannot fix
                    cout << "done" << endl;
                    goto here;
                }

            }
            ++it; // move to the next element
        }

        // CASE 3
        cout << "case 3" << endl;
        for (auto it = linev.begin(); it != linev.end(); it++ ) {
            cout << *it << " ";
        }
        cout << endl;

        it = linev.end() - 2; // get second to last element
        cur = *it;
        cout << cur << endl;
        next = *(it + 1);
        prev = *(it - 1);

        if ( !check_invariants( cur, next, increasing ) ) {
            cout << "stuff " << cur << " " << next << endl;
            if ( check_invariants( prev, next, increasing ) && !dampener_used ) {
                // nothing to do
            }
            else if ( check_invariants( cur, next_next, increasing ) && !dampener_used ) {
                // nothing to do
            }
            else {
                continue;
            }
        }

        // if you get here, then report must be safe
        ++safe_reports;
    here:
        cout << "label" << endl;
    }

    cout << "Number of safe reports: " << safe_reports << endl;
    return 0;

    // while ( getline( f, line ) ) {
    //     istringstream iss( line );
    //
    //     // start with the first two elements in the list
    //     // INVARIANT: will always have two or more elements
    //     iss >> cur >> next;
    //
    //     // set increasing
    //     increasing = next > cur;
    //     if ( !check_invariants( cur, next, increasing ) ) {
    //         safe = false;
    //         continue; // do not increment safe counter
    //     }
    //
    //     // set up for next loop iteration
    //     prev = cur;
    //     cur = next;
    //
    //     // iterate through the rest of the list
    //     while ( iss >> next ) {
    //         if ( !check_invariants( cur, next, increasing ) ) {
    //             safe = false;
    //             break; // do not increment safe counter
    //         }
    //
    //         cur = next; // set up for next loop iteration
    //     }
    //
    //     // if we are here, then report is safe
    //     if ( safe ) ++safe_reports;
    //     safe = true;
    // }

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

bool check_all_invariants( vector<int> & nums, int cur ) {

    int next = nums[2];

    bool increasing = next > cur;
    for ( int i = 3; i < nums.size()-1; i++ ) {

        if ( !check_invariants( cur, next, increasing ) ) {
            return false;
        }

        cur = next;
        next = nums[i];
    }

    // if we get here, invariants are true
    return true;
}
