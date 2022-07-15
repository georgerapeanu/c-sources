/* Test generator - piezisa
 * CLI arguments: n q bucket_cnt bucket_size max_delta outliers file_in file_out
 * n - array length
 * q - no. queries
 * bucket_cnt - how many buckets
 * bucket_size - how many elements in a buckets
 * max_delta - a random amount between 0 and max_delta is added to bucket_size
 * for randomisation
 * outliers - elements that appear with a very small frequency
 * file_in - input file
 * file_out - output file
 */

#include "testlib.h"
#include <cassert>
#include <chrono>
#include <climits>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

int n, q, bucket_cnt, bucket_size, max_delta, outliers;
vector<int> arr;
vector<int> preff_xor;
vector<pair<int, int>> preffs;
vector<pair<int, int>> queries;
vector<int> answers;
FILE *file_in, *file_out;

void read_args() {
    n = opt<int>("n");
    q = opt<int>("q");
    bucket_cnt = opt<int>("bucket_cnt");
    bucket_size = opt<int>("bucket_size");
    max_delta = opt<int>("max_delta");
    outliers = opt<int>("outliers");

    // all the buckets should not have more than n elements
    assert(bucket_cnt * bucket_size <= n);
    // but with the extra max_delta should be more than n
    assert(bucket_cnt * (bucket_size + max_delta) >= n);

    //file_in = fopen(argv[7], "w");
    //file_out = fopen(argv[8], "w");
}

void create_input(mt19937 &gen) {
    // the generated array
    arr.resize(n + 1, 0);

    // preffix xor array over arr
    preff_xor.resize(n + 1, 0);

    // the queries generated
    queries.resize(q + 1, {0, 0});

    // answers to the queries
    answers.resize(q + 1, 0);

    // change INT_MAX with something else if needed
    uniform_int_distribution<int> value_range(0, 100);
    uniform_int_distribution<int> max_delta_range(0, max_delta);

    // select random preffix values for the buckets
    // and select their frequencies
    int total = 0;
    for (int i = 0; i < bucket_cnt; i++) {
        preffs.push_back(
            {value_range(gen), bucket_size + max_delta_range(gen)});
        total += preffs.back().second;
    }

    // remove until at most n - outliers elements
    int sub_from_all = (total - n) / (n - outliers);
    int rest = total % (n - outliers);

    if (sub_from_all > 0 || (sub_from_all >= 0 && rest > 0)) {
        for (int i = 0; i < bucket_cnt; i++) {
            preffs[i].second -= sub_from_all;
            if (rest) {
                preffs[i].second--;
                rest--;
            }
        }
    }

    // create outliers
    for (int i = 0; i < outliers; i++) {
        preffs.push_back({value_range(gen), 1});
    }

    // generate array
    for (int i = 1; i <= n; i++) {
        uniform_int_distribution<int> preff_range(0, preffs.size() - 1);
        int idx = preff_range(gen);

        // choose an element such that the preffix_xor is exactly
        // what we want
        arr[i] = preff_xor[i - 1] ^ preffs[idx].first;
        preff_xor[i] = preffs[idx].second;

        preffs[idx].second--;
        if (preffs[idx].second == 0) {
            preffs.erase(preffs.begin() + idx);
        }
    }

    // randomly generate queries
    uniform_int_distribution<int> index_range(1, n);
    for (int i = 1; i <= q; i++) {
        int x = index_range(gen);
        int y = index_range(gen);

        if (x > y) {
            swap(x, y);
        }

        queries[i] = {x, y};
    }
}

void solve() {
    // Temporary solution O(N^2) for each query
    // This could be also used as a brute-froce solution
    for (int i = 1; i <= q; i++) {
        bool stop = false;
        int x = queries[i].first;
        int y = queries[i].second;
        for (int len = 0; len <= n - (y - x + 1) && !stop; len++) {
            for (int st = max(1, x - len); st <= x; st++) {
                int dr = y + len - (x - st);
                if ((preff_xor[dr] ^ preff_xor[st - 1]) == 0) {
                    answers[i] = len;
                    stop = true;
                    break;
                }
            }
        }

        if (stop == false) {
            answers[i] = -1;
        }
    }
}

void print_input() {
    printf("%d\n", n);
    for (int i = 1; i < n; i++) {
        printf("%d ", arr[i]);
    }
		printf("%d", arr[n]);

    printf("\n");
		printf("%d\n", q);

    for (int i = 1; i <= q; i++) {
        printf("%d %d\n", queries[i].first - 1, queries[i].second - 1);
    }

    //fclose(file_in);
}

void print_output() {
    for (int i = 1; i <= q; i++) {
        fprintf(file_out, "%d\n", answers[i]);
    }
    fclose(file_out);
}

int main(int argc, char **argv) {

		registerGen(argc, argv, 1);
		mt19937 gen(rnd.next(1, 1000000000));

    read_args();
    create_input(gen);
    //solve();
    print_input();
    //print_output();

    return 0;
}
