//
// Created by shara on 12/19/2024.


//

#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

#define DEBUG

using namespace std;

int main() {
    // load text file
    ifstream f ( "../inputs/day1.txt" );

    vector<int> col1;
    vector<int> col2;
    int t1, t2;

    string line;
    int sum = 0;

    // extract the two columns into vectors
    while ( getline( f, line ) ) {
        istringstream iss( line );
        iss >> t1 >> t2;
        col1.push_back( t1 );
        col2.push_back( t2 );
    }

    f.close();

    // sort the vectors
    sort( col1.begin(), col1.end() );
    sort( col2.begin(), col2.end() );

    // iterate through each of the vectors and calculate the difference between them
    auto it1 = col1.begin();
    auto it2 = col2.begin();

    while ( it1 != col1.end() && it2 != col2.end() ) {
        // cout << *it1 << " " << *it2 << endl;
        sum += abs( *it1 - *it2 );
        ++it1; ++it2;
    }

    cout << "Sum of differences is " << sum << endl;

    int similarity = 0;
    int count;

    // calculate similarity score
    for ( int i : col1 ) {
        count = 0;

        for ( int j : col2 ) {
            if ( i == j ) ++count;
        }

        similarity += i * count; // increase similarity score based on formula
    }

    cout << "Similarity score is " << similarity << endl;

    return 0;
}
