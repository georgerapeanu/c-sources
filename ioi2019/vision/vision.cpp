#include "vision.h"
#pragma once

using namespace std;

const int NMAX = 200;

int sum_diag_pos[2 * NMAX + 5];
int sum2_diag_pos[2 * NMAX + 5];
int diff_diag_pos[2 * NMAX + 5];
int diff2_diag_pos[2 * NMAX + 5];
vector<int> sum_cells[2 * NMAX + 5];
vector<int> diff_cells[2 * NMAX + 5];
int last_ind;

int at_most_k(int n,int m,int k) {
    vector<int> ok_sum_k_pos;
    for(int i = 0; i + k < n + m - 1; i++) {
        vector<int> tmp;
        for(int j = i; j <= i + k; j++) {
            tmp.push_back(sum_diag_pos[j]);
            tmp.push_back(sum2_diag_pos[j]);
        }
        last_ind++;
        add_or(tmp);
        last_ind++;
        add_xor(tmp);
        last_ind++;
        add_not(last_ind - 2);
        ok_sum_k_pos.push_back(last_ind++);
        add_and({last_ind - 2,last_ind - 4});
    }
    int ok_sum_k = last_ind++;
    add_or(ok_sum_k_pos);

    vector<int> ok_diff_k_pos;
    for(int i = 0; i + k < n + m - 1; i++) {
        vector<int> tmp;
        for(int j = i; j <= i + k; j++) {
            tmp.push_back(diff_diag_pos[j]);
            tmp.push_back(diff2_diag_pos[j]);
        }
        last_ind++;
        add_or(tmp);
        last_ind++;
        add_xor(tmp);
        last_ind++;
        add_not(last_ind - 2);
        ok_diff_k_pos.push_back(last_ind++);
        add_and({last_ind - 2,last_ind - 4});
    }
    int ok_diff_k = last_ind++;
    add_or(ok_diff_k_pos);

    last_ind++;
    add_and({ok_diff_k,ok_sum_k});

    return last_ind - 1;
}

void construct_network(int n, int m, int k) {
    last_ind = n * m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            sum_cells[i + j].push_back(i * m + j);
            diff_cells[i - j + m - 1].push_back(i * m + j);
        }
    }
    for(int sum = 0; sum < n + m - 1; sum++) {
        sum_diag_pos[sum] = last_ind++;
        add_or(sum_cells[sum]);
        last_ind++;
        add_xor(sum_cells[sum]);
        last_ind++;
        add_not(last_ind - 2);
        sum2_diag_pos[sum] = last_ind++;
        add_and({last_ind - 2,sum_diag_pos[sum]});
    }

    for(int diff = 0; diff < n + m - 1; diff++) {
        diff_diag_pos[diff] = last_ind++;
        add_or(diff_cells[diff]);
        last_ind++;
        add_xor(diff_cells[diff]);
        last_ind++;
        add_not(last_ind - 2);
        diff2_diag_pos[diff] = last_ind++;
        add_and({last_ind - 2,diff_diag_pos[diff]});
    }
    int ok1 = at_most_k(n,m,k);
    int ok2 = at_most_k(n,m,k - 1);

    add_not(ok2);
    ok2 = last_ind++;

    add_and({ok1,ok2});
}
