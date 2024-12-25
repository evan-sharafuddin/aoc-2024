//
// Created by shara on 12/24/2024.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// create consts for target word
const string XMAS = "XMAS";
const string SAMX = "SAMX"; // backwards version
const size_t LEN  = XMAS.size();

// declare helper functions

class Shirt {
public:
    Shirt( string filename ) : filename(filename) {};
    ~Shirt() {
        if ( f ) f.close();
    };

    bool open() {
        f.open( filename );
        if ( !f.is_open() ) return false;

        // create 2D matrix
        string line;
        while ( getline( f, line ) ) {
            vector<char> buf;
            for( char c : line ) {
                buf.push_back( c );
            }
            text.push_back( buf );
        }

        // set dimensions
        cols = text[0].size();
        rows = text.size();

        down.resize( rows, vector<char>(cols) );
        // create buffers
        /* Example 5x5
         *
         * XXXXX
         * XXXXX
         * XXXXX
         * XXXXX
         * XXXXX
         *
         * VERTICAL BUF: 5x5
         * HORIZONTAL BUF: 5x5
         * DIAGONAL BUF: cat(1x4, 1x5, 1x4)
         *
         * Generalized for NxM shirt
         * VERTICAL BUF: NxM
         * HORIZONTAL BUF: MxN
         * DIAGONAL BUF:
         * --> think of rotating the text of the shirt 45 degrees
         * --> ex: for down_right, rows go from top to bottom, running left to right
         * --> will always have "dead" space where you have 3 or less char. in a diagonal row
         * --> number of diagonals in an NxM cube is N+M-1
         * --> assuming N, M > 4 --> will have N+M-1-3-3, excluding the two sets of 3 rows
         *     that are not long enough
         */


        // print out text
        // cout << *this << endl;

        return true;
    };

    void update_vertical_bufs( char c, int i, int j ) {
        // down
        down[i].push_back( c );

        // TODO might be better to instead keep track of numbers, like 1 2 3, which mean how close we are to getting to xmax


    };


    // prints out shirt text
    friend ostream& operator<<( ostream& os, const Shirt& s ) {
        for ( auto v : s.text ) {
            for ( char c : v ) {
                os << c;
            }
            os << endl;
        }

        return os;
    };



private:
    string filename;
    ifstream f;

    // T-Shirt matrix
    vector<vector<char>> text;
    size_t rows, cols;

    // initialize buffers for identifying XMAS
    vector<vector<char>> down, up, right, left, down_left, down_right, up_left, up_right;



};


int main() {
    Shirt shirt("../test_inputs/day4.txt");
    cout << shirt.open() << endl;
    cout << shirt << endl;

    return 0;
}
