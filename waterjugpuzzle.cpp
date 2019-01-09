/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Bobby Georgiou
 * Date        : 10/19/2018
 * Description : Program to solve the famous water jug puzzle using breadth-first search
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System."
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <stack>

using namespace std;

const string jug_labels[] = {"", "A", "B", "C", "A", "B", "C"};
const string index_to_label[] = {"A", "B", "C"};

/**
 * Returns string representation of a vector of integers
 */
string vec_string(vector<int> vec) {
    ostringstream oss;
    oss << "(";
    for (unsigned int i = 0; i < vec.size(); ++i) {
        if (i == vec.size() - 1) {
            oss << vec[i];
        } else {
            oss << vec[i] << ", ";
        }
    }
    oss << ")";
    return oss.str();
}

/**
 * Struct for object PourData that contains information about each move that is made
 */
struct PourData {
    bool can_pour;
    vector<int> new_state;
    int from, to, amount;
    vector<int> parent;

    PourData() {}
    PourData(bool _can_pour, vector<int> _new_state, int _from, int _to, int _amount, vector<int> _parent) : 
    can_pour(_can_pour), new_state(_new_state), from(_from), to(_to), amount(_amount), parent(_parent) { }

    string to_string() {
        ostringstream oss;
        oss << "new: " << vec_string(new_state) << " from: " << from << " to: " << to << " amount: " << amount << " parent: " << vec_string(parent);
        return oss.str();
    }
};

/**
 * Return object PourData for state given of the jugs; PourData contains a boolean representing 
 * if the the move can be done, a vector containing the new possible state, integers for the jug 
 * poured from and to, amount poured, and a vector containing the parent state of jugs
 */
PourData pour(const vector<int> &state, const vector<int> &caps, int from, int to) {
    vector<int> new_state = state;
    int amount;
    if (state[to] + state[from] >= caps[to] && state[to] < caps[to]) {
        new_state[from] -= caps[to] - state[to];
        new_state[to] = caps[to]; // TO full
        amount = caps[to] - state[to];
    } else if (state[to] + state[from] < caps[to] && state[from] > 0) {
        new_state[from] = 0; // FROM empty
        new_state[to] += state[from];
        amount = state[from];
    } else { // move not possible
        return PourData(false, {}, -1, -1, -1, {});
    }
    return PourData(true, new_state, from, to, amount, state);
}

/**
 * Display the result of attemping to solve the puzzle, utilizing the stack produced by solve()
 */
void display_results(bool possible, stack<PourData> order) {
    if (possible) {
        vector<int> seeking_parent;
        stack<PourData> final_order;
        while (!order.empty()) {
            PourData cur_p = order.top();
            if (cur_p.parent.empty()) { // reached start state
                final_order.push(cur_p);
            } else if (seeking_parent.empty() || cur_p.new_state == seeking_parent) {
                final_order.push(cur_p);
                seeking_parent = cur_p.parent;
            }
            order.pop();
        }
        bool init_shown = false;
        ostringstream oss;
        while (!final_order.empty()) {
            PourData cur_p = final_order.top();
            if (!init_shown) {
                oss << "Initial state. " << vec_string(cur_p.new_state) << endl;
                init_shown = true;
            } else {
                string gal_modifier = cur_p.amount == 1 ? "gallon" : "gallons";
                oss << "Pour " + to_string(cur_p.amount) << " " << gal_modifier << " from " << index_to_label[cur_p.from] << " to " 
                << index_to_label[cur_p.to] << ". " << vec_string(cur_p.new_state) << endl;
            }
            final_order.pop();
        }
        cout << oss.str();
    } else {
        cout << "No solution." << endl;
    }
}

/**
 * Attempt to solve the water jug puzzle to reach the specified goal state 
 * using breadth-first search and struct PourData; display results when finished
 */
void solve(const vector<int> args) {
    vector<vector<int>> pour_order = {{2, 0}, {1, 0}, {2, 1}, {0, 1}, {1, 2}, {0, 2}};
    vector<int> caps = {args[0], args[1], args[2]}; // jug capacities
    vector<int> goal = {args[3], args[4], args[5]}; // goal state
    vector<int> start = {0, 0, args[2]};
    vector<int> temp_state = start;
    vector<int> temp_state_inner;

    map<vector<int>, bool> visited;
    queue<vector<int>> q;
    PourData p;
    stack<PourData> order;

    order.push(PourData(true, temp_state, -1, -1, -1, {}));

    if (temp_state == goal) {
        display_results(true, order);
        return;
    }

    q.push(temp_state);
    while (!q.empty()) {
        temp_state = q.front();
        visited[temp_state] = true;
        for (const vector<int> &t : pour_order) {
            p = pour(temp_state, caps, t[0], t[1]);
            if (p.can_pour) { // can pour
                temp_state_inner = p.new_state;
                if (!visited[temp_state_inner]) {
                    visited[temp_state_inner] = true;
                    order.push(p);
                    q.push(temp_state_inner);
                    if (temp_state_inner == goal) {
                        display_results(true, order);
                        return;
                    }
                }
            }
        }
        q.pop();
    }
    display_results(false, order);
}

int main(int argc, char * const argv[]) {
    if (argc != 7) {
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }
    vector<string> args(argv, argc + argv);
    int curArg;
    int curArgIndex = -1;
    for (const string &arg : args) {
        curArgIndex++;
        istringstream iss(arg);
        if (curArgIndex > 0) {
            if (!(iss >> curArg)) {
                if (curArgIndex < 4) {
                    cerr << "Error: Invalid capacity '" << arg << "' for jug " << jug_labels[curArgIndex] << "." << endl;
                } else if (curArgIndex > 3 && curArgIndex < 7) {
                    cerr << "Error: Invalid goal '" << arg << "' for jug " << jug_labels[curArgIndex] << "." << endl;
                }
                return 1;
            } else if (curArgIndex < 4 && stoi(arg) <= 0) {
                cerr << "Error: Invalid capacity '" << arg << "' for jug " << jug_labels[curArgIndex] << "." << endl;
                return 1;
            } else if (curArgIndex > 3 && curArgIndex < 7 && stoi(arg) < 0) {
                cerr << "Error: Invalid goal '" << arg << "' for jug " << jug_labels[curArgIndex] << "." << endl;
                return 1;
            }
        }
    }
    if (stoi(args[4]) > stoi(args[1])) {
        cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    if (stoi(args[5]) > stoi(args[2])) {
        cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    if (stoi(args[6]) > stoi(args[3])) {
        cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }
    if (stoi(args[4]) + stoi(args[5]) + stoi(args[6]) != stoi(args[3])) {
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }

    args.erase(args.begin());
    vector<int> args_int;
    for (const string &s : args) {
        args_int.push_back(stoi(s));
    }

    solve(args_int);

    return 0;
}
