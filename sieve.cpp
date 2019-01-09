/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Bobby Georgiou
 * Date        : 09/10/2018
 * Description : Programming Assignment 1 - Sieve of Eratosthenes
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System."
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    /**
     * Constructor for class PrimesSieve
     */
    PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
        sieve();
        num_primes_ = count_num_primes(); // set num_primes_
        // set max_prime_
        int i = limit_ - 1;
        while (!is_prime_[i] && i >= 0) {
            i--;
        }
        max_prime_ = i;
    }

    /**
     * Destructor for class PrimesSieve
     */
    ~PrimesSieve() {
        delete [] is_prime_;
    }

    /**
     * Accessor for num_primes_ field
     */
    inline int num_primes() const {
        return num_primes_;
    }

    /**
     * Print the number of primes found followed by the list of primes
     * formatted with appropriate spacing and a maximum of 80 characters per line
     */
    void display_primes() const {
        cout << endl << "Number of primes found: " << num_primes() << endl;
        cout << "Primes up to " << limit_ << ":" << endl;
        const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
        int prime_in_row_cnt = 0; bool single_row = num_primes() <= primes_per_row;
        for (int i = 2; i < limit_ + 1; i++) {
            if (is_prime_[i]) {
                if (prime_in_row_cnt == primes_per_row) {
                    prime_in_row_cnt = 0;
                    cout << endl;
                }
                if (single_row) {
                    if (prime_in_row_cnt == num_primes() - 1) {
                        cout << i;
                    } else {
                        cout << i << " ";
                    }     
                } else {
                    if (prime_in_row_cnt == 0) {
                      cout << setw(max_prime_width);  
                    } else {
                    cout << setw(max_prime_width + 1);
                    }
                    cout << i;
                }
                prime_in_row_cnt++;
            }
        }
    }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    /**
     * Return the number of indices marked true in is_prime_
     */
    int count_num_primes() const {
        int cnt = 0;
        for (int i = 2; i < limit_ + 1; i++) {
            cnt += is_prime_[i] ? 1 : 0;
        }
        return cnt;
    }

    /**
     * Return the number of digits in input integer num
     */
    int num_digits(int num) const {
        if (num < 10) {
            return 1;
        } else {
            int digit_cnt = 1;
            do {
                num = floor(num / 10);
                digit_cnt++;
            } while (num > 10);
            return digit_cnt;
        }
    }

    /**
     * Test to see which indices of is_prime_ are prime up to the limit and
     * set the appropriate bool value when necessary
     */
    void sieve() {
        int n = limit_;
        for (int i = 2; i < n + 1; i++) {
            is_prime_[i] = true;
        }
        for (int i = 2; i <= floor(sqrt(n)); i++) {
            if (is_prime_[i]) {
                for (int j = pow(i, 2); j <= n; j += i) {
                    is_prime_[j] = false;
                }
            }
        }
    }
};

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // Create PrimesSieve object using provided limit value and display primes
    PrimesSieve ps(limit);
    ps.display_primes();

    return 0;
}
