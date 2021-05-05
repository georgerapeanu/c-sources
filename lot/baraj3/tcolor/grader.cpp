#include "tcolor.h"

#include <iostream>

int main() {
    int testCount = 0;
    std::cin >> testCount;
    for(int testNumber = 0; testNumber < testCount; testNumber++) {
        int N, V, E;
        std::cin >> N;

        std::vector<int> A(N-1), B(N-1);
        for(int i = 0; i < N-1; i++)
            std::cin >> A[i] >> B[i];

        std::cin >> V >> E;
        std::vector<int> X(E), Y(E);
        for(int i = 0; i< E; i++)
            std::cin >> X[i] >> Y[i];

        std::vector<int> answer = solve(N, V, E, A, B, X, Y);
        std::cout << answer.size() << '\n';
        for(int color: answer)
            std::cout << color <<' ';
        std::cout<<'\n';
    }
    return 0;
}
