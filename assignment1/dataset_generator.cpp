#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <cmath>


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
    srand(time(0));

    ofstream out("results.csv");
    out << "n,alpha,EFT_time,EST_time,SD_time,EFT_size,EST_size,SD_size\n";

    vector<int> sizes = {1024, 2048, 4096, 8192, 16384, 32768, 65536};
    vector<double> alphas = {0.1, 1, 5};  // High, Medium, Low overlap

    double D = 10;
    int repeats = 50;  // number of timing repeats
    volatile int sink; // prevent optimization

    for(double alpha : alphas) {
        for(int n : sizes) {

            auto intervals = generate_intervals(n, D, alpha);

            // ---- EFT Timing ----
            auto start = chrono::high_resolution_clock::now();
            for(int i = 0; i < repeats; i++)
                sink = greedy_EFT(intervals);
            auto end = chrono::high_resolution_clock::now();
            double eft_time = chrono::duration<double, micro>(end - start).count() / repeats;

            // ---- EST Timing ----
            start = chrono::high_resolution_clock::now();
            for(int i = 0; i < repeats; i++)
                sink = greedy_EST(intervals);
            end = chrono::high_resolution_clock::now();
            double est_time = chrono::duration<double, micro>(end - start).count() / repeats;

            // ---- SD Timing ----
            start = chrono::high_resolution_clock::now();
            for(int i = 0; i < repeats; i++)
                sink = greedy_SD(intervals);
            end = chrono::high_resolution_clock::now();
            double sd_time = chrono::duration<double, micro>(end - start).count() / repeats;

            int eft_size = greedy_EFT(intervals);
            int est_size = greedy_EST(intervals);
            int sd_size  = greedy_SD(intervals);

            out << n << "," << alpha << ","
                << eft_time << "," << est_time << "," << sd_time << ","
                << eft_size << "," << est_size << "," << sd_size << "\n";

            cout << "Done n=" << n << " alpha=" << alpha << endl;
        }
    }

    out.close();
    cout << "Results saved to results.csv\n";
    return 0;
}
