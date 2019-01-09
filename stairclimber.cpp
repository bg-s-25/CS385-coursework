/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Bobby Georgiou
 * Date        : 09/27/2018
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System."
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

/**
 * Return a vector of vectors of integers representing the
 * different combinations of ways to climb num_stairs stairs,
 * moving up either 1, 2, or 3 stairs at a time
 */
vector<vector<int>> get_ways(int num_stairs) {
    vector<vector<int>> ways = {};
    if (num_stairs <= 0) {
        ways.push_back({});
    } else {
        for (int i = 1; i < 4; i++) {
            if (num_stairs >= i) {
                vector<vector<int>> result = get_ways(num_stairs - i);
                for (vector<int> &v : result) {
                    v.push_back(i);
                }
                for (vector<int> &v : result) {
                    ways.push_back(v);
                }
            }
        }
    }
    sort(ways.begin(), ways.end()); 
    return ways;
}

/**
 * Display the ways of climbing a certain number of stairs by using
 * the vector returned by get_ways() and printing each combination
 */
void display_ways(const vector<vector<int>> &ways) {
    int num_ways = ways.size();
    int &num_ways_temp = num_ways;
    unsigned int num_max_digits;
    if (num_ways_temp < 10) {
        num_max_digits = 1;
    } else {
        int digit_cnt = 1;
        do {
            num_ways_temp = floor(num_ways_temp / 10);
            digit_cnt++;
        } while (num_ways_temp > 10);
        num_max_digits = digit_cnt;
    }
    int vectorCnt = 0;
    for (const vector<int> &v : ways) {
        vectorCnt++;
        unsigned int intCnt = 0;
        string prefix = to_string(vectorCnt);
        while (prefix.size() < num_max_digits) {
            prefix.insert(0, " ");
        }
        cout << prefix << ". [";
        for (const int &i : v) {
            intCnt++;
            if (intCnt == v.size()) {
                cout << i;
            } else {
                cout << i << ", ";
            }
        }
        cout << "]" << endl;
    }
}

int main(int argc, char * const argv[]) {
    if (argc == 1) {
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    } else if (argc > 2) {
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }
    istringstream iss(argv[1]);
    int val;
    if (!(iss >> val)) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    if (val <= 0) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    vector<vector<int>> result = get_ways(val);
    string wayStr = result.size() == 1 ? "way" : "ways";
    string stairStr = val == 1 ? "stair" : "stairs";
    cout << to_string(result.size()) + " " + wayStr + " to climb " + to_string(val) + " " + stairStr + "." << endl;
    display_ways(result);
    return 0;
}
