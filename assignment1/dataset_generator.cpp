#include<iostream>
#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int>> generate_intervals(int n, double D, double alpha) {
    vector<pair<int, int>> intervals;
    int T = n*D*alpha; // Total length considering overlap
    for(int i = 0; i < n; i++) {
        int s = ((double) rand() / RAND_MAX) * T;  // random start in [0, T)
        int d = 1 + ((double) rand() / RAND_MAX) * (D - 1);  // duration in [1, D]
        int f = s + d;
        intervals.push_back({s, f});
    }
    return intervals;
}

int greedy_EST(vector<pair<int,int>> intervals) {
    // Sort by start time
    sort(intervals.begin(), intervals.end(),
         [](pair<int,int> a, pair<int,int> b) {
             return a.first < b.first;
         });

    cout << "\nIntervals sorted by start time:\n";
    for(auto &in : intervals) {
        cout << "[" << in.first << ", " << in.second << "] ";
    }
    cout << "\n";

    int count = 0;
    int last_finish = -1;

    cout << "Selected intervals (EST):\n";

    for(auto &interval : intervals) {
        if(interval.first >= last_finish) {
            cout << "[" << interval.first << ", " << interval.second << "] ";
            count++;
            last_finish = interval.second;
        }
    }

    cout << "\n";
    return count;
}


int greedy_SD(vector<pair<int,int>> intervals) {
    // Sort by duration
    sort(intervals.begin(), intervals.end(),
         [](pair<int,int> a, pair<int,int> b) {
             return (a.second - a.first) < (b.second - b.first);
         });

    cout << "\nIntervals sorted by duration:\n";
    for(auto &in : intervals) {
        cout << "[" << in.first << ", " << in.second << "] ";
    }
    cout << "\n";

    int count = 0;
    int last_finish = -1;

    cout << "Selected intervals (SD):\n";

    for(auto &interval : intervals) {
        if(interval.first >= last_finish) {
            cout << "[" << interval.first << ", " << interval.second << "] ";
            count++;
            last_finish = interval.second;
        }
    }

    cout << "\n";
    return count;
}


int greedy_EFT(vector<pair<int,int>> intervals) {
    // Sort by finish time
    sort(intervals.begin(), intervals.end(),
         [](pair<int,int> a, pair<int,int> b) {
             return a.second < b.second;
         });

    cout << "\nIntervals sorted by finish time:\n";
    for(auto &in : intervals) {
        cout << "[" << in.first << ", " << in.second << "] ";
    }
    cout << "\n";

    int count = 0;
    int last_finish = -1;

    cout << "Selected intervals (EFT):\n";

    for(auto &interval : intervals) {
        if(interval.first >= last_finish) {
            cout << "[" << interval.first << ", " << interval.second << "] ";
            count++;
            last_finish = interval.second;
        }
    }

    cout << "\n";
    return count;
}


int main() {
    srand(time(0));  // seed random number generator

    int n = 10;
    double D = 10;
    double alpha = 0.1; //high overlap

    auto intervals = generate_intervals(n, D, alpha);
    for (const auto& interval : intervals) {
        cout << "[" << interval.first << ", " << interval.second << "]" << endl;
    } 
    
    int eft = greedy_EFT(intervals);
    cout << "Total selected by EFT: " << eft << "\n";

    int est = greedy_EST(intervals);
    cout << "Total selected by EST: " << est << "\n";

    int sd = greedy_SD(intervals);
    cout << "Total selected by SD: " << sd << "\n";


    return 0;
}