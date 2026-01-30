#include<iostream>
#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int>> generate_intervals(int n, double D, double alpha) {
    vector<pair<int, int>> intervals;
    srand(time(0));  // seed random number generator
    int T = n*D*alpha; // Total length considering overlap
    for(int i = 0; i < n; i++) {
        int s = ((double) rand() / RAND_MAX) * T;  // random start in [0, T)
        int d = 1 + ((double) rand() / RAND_MAX) * (D - 1);  // duration in [1, D]
        int f = s + d;
        intervals.push_back({s, f});
    }
    return intervals;
}


int main() {
    int n = 10;
    double D = 10;
    double alpha = 0.1; //high overlap
    auto intervals = generate_intervals(n, D, alpha);
    for (const auto& interval : intervals) {
        cout << "[" << interval.first << ", " << interval.second << "]" << endl;
    }   
    return 0;
}