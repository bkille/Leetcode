#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


void vec_to_str(vector<int> vec) {
    std::cout << '{';
    for (auto i : vec) 
        std::cout << i << ',';
    std::cout << "}\n";
}
void output_vecvec(vector<vector<int>> vec) {
    for (auto v : vec) {
        vec_to_str(v);
    }
}

int find_intersection(vector<int>& v1, vector<int>& v2, int n) {
    int max_idx = n;
    int min_idx = 0;
    int i = max_idx/2;
    while (max_idx - min_idx >= 3) {
        if (v1[i] == v2[n - i]) {
            min_idx = max_idx = i;
            return i;
        }
        else if (v1[i] < v2[n - i]) { // increase i
            min_idx = i;
        } else {
            max_idx = i;
        }
        i = (min_idx + max_idx) / 2;
    }
    return i;
}

class Solution {
public:
    int superEggDrop(int K, int N) {
        vector<int> current(N + 2, 0);
        vector<int> prev(N + 2, 0);
        prev[0] = 0;
        for (int i = 1; i <= N + 1; ++i) 
           prev[i] = i - 1;
        // When K = 1, we need exactly N drops.
        
        for (int i = 2; i <= K; ++i) {
            // For some number of eggs i and n possible floors,
            // if we try dropping the egg at 
            // floor j, one of two things will happen:
            // 1. It breaks, therefore we know that F < j
            // 2. It doesnt, and therefor F >= j
            // So if we drop at floor j, we will need at least
            // 1 + max(memo[i-1][j], memo[k][n - j - 1])
            // And this will be stored in memo[i][n]


            // memo[i][j] is weakly increasing as j increases
            // memo[i][j] is weakly decreasing as i increases
            // memo[i-1][j] < memo[i][n-j] in the cases we care about
            // It suffices to find the 
            int new_idx = 0;
            for (int n = 2; n <= N + 1; ++n) { // n possible floors
                // looking for memo[i][n]
                if (current[n - new_idx - 1] != current[n - new_idx])
                    new_idx = find_intersection(prev, current, n);
                int best = max(prev[new_idx], current[n - new_idx]);
                current[n] = 1 + best;
            }
            prev.swap(current);
        }
        return prev[N + 1];
    }
};

int main() {
    Solution a {};

    int ret =  a.superEggDrop(10, 500);
    cout << "FINAL RESULT: " << ret << endl;


    return 0;
}
