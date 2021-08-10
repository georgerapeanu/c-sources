#include <iostream>

#include "ctree.h"

int main(){
    int N, T;
    std::cin >> T;
    for(int t = 1; t <= T; t++) {
        std::cin >> N;
        std::vector<int> X(N - 1), Y(N - 1);
        for (int i = 0; i < N - 1; i++) {
            std::cin >> X[i] >> Y[i];
        }
        std::vector<int> answers = solve(N, X, Y);
        for (auto answer: answers)
            std::cout << answer << ' ';
        std::cout << '\n';
    }
    return 0;
}
