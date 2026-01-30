#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

/* ---------------------------------------------------
   DATASET GENERATOR
   Generates n random intervals with overlap controlled
   by alpha.
--------------------------------------------------- */
vector<pair<int, int>> generate_intervals(int n, double D, double alpha) {
    vector<pair<int, int>> intervals;
    int T = n * D * alpha;  // time horizon

    for(int i = 0; i < n; i++) {
        int s = ((double) rand() / RAND_MAX) * T; // start time
        int d = 1 + ((double) rand() / RAND_MAX) * (D - 1); // duration
        int f = s + d; // finish time
        intervals.push_back({s, f});
    }
    return intervals;
}

/* ---------------------------------------------------
   GREEDY: Earliest Finish Time (Optimal Greedy)
--------------------------------------------------- */
int greedy_EFT(vector<pair<int,int>> intervals) {
    sort(intervals.begin(), intervals.end(),
         [](pair<int,int> a, pair<int,int> b) {
             return a.second < b.second;
         });

    int count = 0;
    int last_finish = -1;

    for(auto &interval : intervals) {
        if(interval.first >= last_finish) {
            count++;
            last_finish = interval.second;
        }
    }
    return count;
}

/* ---------------------------------------------------
   GREEDY: Earliest Start Time
--------------------------------------------------- */
int greedy_EST(vector<pair<int,int>> intervals) {
    sort(intervals.begin(), intervals.end(),
         [](pair<int,int> a, pair<int,int> b) {
             return a.first < b.first;
         });

    int count = 0;
    int last_finish = -1;

    for(auto &interval : intervals) {
        if(interval.first >= last_finish) {
            count++;
            last_finish = interval.second;
        }
    }
    return count;
}

/* ---------------------------------------------------
   GREEDY: Shortest Duration
--------------------------------------------------- */
int greedy_SD(vector<pair<int,int>> intervals) {
    sort(intervals.begin(), intervals.end(),
         [](pair<int,int> a, pair<int,int> b) {
             return (a.second - a.first) < (b.second - b.first);
         });

    int count = 0;
    int last_finish = -1;

    for(auto &interval : intervals) {
        if(interval.first >= last_finish) {
            count++;
            last_finish = interval.second;
        }
    }
    return count;
}

/* ---------------------------------------------------
   MAIN: Benchmarking
--------------------------------------------------- */
int main() {
    srand(time(0));  // seed once

    int n = 65536;       // increase for bigger tests
    double D = 10;
    double alpha = 1;   // Medium overlap

    auto intervals = generate_intervals(n, D, alpha);

    volatile int sink;   // prevents compiler optimization
    int repeats = 100;   // repeat runs for stable timing

    // ---- Time EFT ----
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < repeats; i++)
        sink = greedy_EFT(intervals);
    auto end = chrono::high_resolution_clock::now();
    double eft_time = chrono::duration<double, micro>(end - start).count() / repeats;

    // ---- Time EST ----
    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < repeats; i++)
        sink = greedy_EST(intervals);
    end = chrono::high_resolution_clock::now();
    double est_time = chrono::duration<double, micro>(end - start).count() / repeats;

    // ---- Time SD ----
    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < repeats; i++)
        sink = greedy_SD(intervals);
    end = chrono::high_resolution_clock::now();
    double sd_time = chrono::duration<double, micro>(end - start).count() / repeats;

    cout << "n = " << n << endl;
    cout << "EFT selected: " << greedy_EFT(intervals) << " | Avg Time: " << eft_time << " microseconds\n";
    cout << "EST selected: " << greedy_EST(intervals) << " | Avg Time: " << est_time << " microseconds\n";
    cout << "SD selected:  " << greedy_SD(intervals)  << " | Avg Time: " << sd_time  << " microseconds\n";

    return 0;
}
