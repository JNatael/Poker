//Defines the entry point for the console application.
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

/*
This function reads a line of int values into a vector function and returns that
vector.
*/
vector<long long> readlineoflongs(int count) {
    // Input values
    vector<long long> linevalues(count);
    for (int j = 0; j < count; j++) {
        long val;
        cin >> val;
        linevalues[j] = val;
    }
    return linevalues; // Return line values as a vector
}

//Code to sort only the first column of the vector taken from https://stackoverflow.com/questions/21978557/sort-multidimensional-vector-by-1st-column
//It's been altered to long
struct FirstColumnOnlyCmp {
    bool operator()(const std::vector<long long>& lhs, const std::vector<long long>& rhs) const {
        return lhs[0] < rhs[0];
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    // get test case count
    int t;
    std::cin >> t;

    //! loop over all the test cases
    for (int i = 1; i <= t; i++) {
        // Read in params
        vector<long long> params = readlineoflongs(1);
        long long n = params[0];

        //Loop over inputs
        vector<vector<long long>> tournaments;
        for (int j = 0; j < n; j++) {
            vector<long long> this_tournament = readlineoflongs(3);
            tournaments.push_back(this_tournament);
        }

        //Sort by start date
        std::sort(tournaments.begin(), tournaments.end(), FirstColumnOnlyCmp());

        vector<long long> winnings(tournaments.size());
        bool possible = false;
        //Iterate over boxes
        for (int j = 0; j < tournaments.size(); j++) {
            long long temp_winnings = tournaments[j][2]; //Set a temp height variable equal to picking this box alone
            //For all previous boxes
            for (int k = 0; k < j; k++) {
                if ((tournaments[k][1] <  tournaments[j][0]) || (tournaments[k][0] > tournaments[j][1])) { //If k ends before j starts or k starts after j ends
                    temp_winnings = max(temp_winnings, (tournaments[j][2] + winnings[k])); //Set temp winnings to max of current value and sum of this tournament and the previous tournament under consideration
                }
            }
            winnings[j] = temp_winnings; //Record the final height in the height matrix
        }


        //Find max of winnings from total
        long long max_winnings = 0;
        for (int j = 0; j < winnings.size(); j++) {
            if (winnings[j] > max_winnings) { max_winnings = winnings[j]; }
        }

        //Print output
        std::cout << "Case #" << i << ": " << max_winnings << std::endl;
        
    }
    return 0;
}