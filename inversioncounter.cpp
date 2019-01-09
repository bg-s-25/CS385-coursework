/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Bobby Georgiou
 * Version     : 1.0
 * Date        : 10/27/2018
 * Description : Counts the number of inversions in an array.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System."
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long inversion_cnt = 0;
    for (int i = 0; i < length; ++i) {
        for (int j = i + 1; j < length; ++j) {
            if (array[j] < array[i]) {
                inversion_cnt++;
            }
        }
    }
    return inversion_cnt;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int * scratch;
    scratch = new int[length];
    long inversion_cnt = mergesort(array, scratch, 0, length - 1);
    delete [] scratch;
    return inversion_cnt;
}

/**
 * Returns the number of inversions in an array by applying merge sort 
 * and recursively accumulating the inversion count
 */
static long mergesort(int array[], int scratch[], int low, int high) {
    if (low < high) {
        long inversion_cnt = 0;
        int mid = low + (high - low) / 2;
        inversion_cnt += mergesort(array, scratch, low, mid);
        inversion_cnt += mergesort(array, scratch, mid + 1, high);
        int L = low, H = mid + 1;
        for (int k = low; k <= high; ++k) {
            if (L <= mid && (H > high || array[L] <= array[H])) {
                scratch[k] = array[L];
                L++;
            } else {
                scratch[k] = array[H];
                inversion_cnt += mid + 1 - L; // increment inversion count
                H++;
            }
        }
        for (int k = low; k <= high; ++k) {
            array[k] = scratch[k];
        }
        return inversion_cnt;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    bool slow = false;
    if (argc > 2) {
        cerr << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    } else if (argc == 2) {
        if (strcmp(argv[1], "slow") == 0) {
            slow = true;
        } else {
            cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
            return 1;
        }
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if (values.size() == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    long inversion_cnt;
    if (slow) {
        inversion_cnt = count_inversions_slow(&values[0], values.size());
    } else {
        inversion_cnt = count_inversions_fast(&values[0], values.size());
    }

    cout << "Number of inversions: " << inversion_cnt << endl;

    return 0;
}
