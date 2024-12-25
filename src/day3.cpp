//
// Created by shara on 12/24/2024.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <string>
#include <cstring>
//68195604

using namespace std;

int main() {

    // load file into string
    ifstream f("../inputs/day3.txt");
    stringstream buffer;
    buffer << f.rdbuf();
    string s = buffer.str();
    f.close();

    // add do() to start of string to make regex easier
    s.insert( 0, "do()" );
    // add don't() to end of string to make regex easier
    s.append( "don't()" );


    // parse string using regex
    // extract the numbers from valid mul() commands, comma separated
    regex get_nums(R"(mul\((\d{1,3}),(\d{1,3})\))");
    // regex get_nums(R"(do\(\).*(?:mul\((\d+),(\d+)\))+.*don't\(\)))");
    regex get_matches(R"(do\(\)(.|\n|\r)*?don't\(\))");
    smatch num_matches;
    // cout << s << endl;

    int sum = 0;
    int prod = 1;

    if ( regex_search( s, get_matches ) ) {
        for (sregex_iterator it(s.begin(), s.end(), get_matches);
        it != sregex_iterator(); ++it)
        {

            smatch match_enabled = *it;
            string s_enabled = match_enabled[0];
            // cout << "thing: " << s_enabled << endl;
            if ( regex_search( s_enabled, get_nums ) ) {
                cout << "At least one match found." << endl;

                for (sregex_iterator it(s_enabled.begin(), s_enabled.end(), get_nums);
                        it != sregex_iterator(); ++it)
                {
                    smatch match = *it;

                    cout << match[0] << endl;
                    for ( int i = 1; i < match.size(); i++ ) {
                        cout << match[i] << " ";
                        prod *= stoi(match[i].str());
                    }
                    cout << sum << endl;
                    sum += prod;
                    prod = 1;
                }
            }
        }
    }

    else {
        cout << "No matching commands." << endl;
    }

    cout << "Sum: " << sum << endl;

    return 0;
}

// if ( regex_search( s, get_nums ) ) {
//     cout << "At least one match found." << endl;
//
//     for (sregex_iterator it(s.begin(), s.end(), get_nums);
//             it != sregex_iterator(); ++it) {
//         smatch match = *it;
//
//         cout << match[0] << endl;
//         for ( int i = 1; i < match.size(); i++ ) {
//             cout << match[i] << " ";
//             // prod *= stoi(match[i].str());
//         }
//
//         sum += prod;
//         prod = 1;
//
//     }
// }