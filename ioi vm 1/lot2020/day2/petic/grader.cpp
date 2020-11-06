#include <iostream>
#include "petic.h"


int main() {
    int nrLin, nrCol, Q;
    std::cin >> nrLin >> nrCol >> Q;

    std::vector<std::string> matrix(nrLin);
    std::vector<int> X1(Q);
    std::vector<int> Y1(Q);
    std::vector<int> X2(Q);
    std::vector<int> Y2(Q);

    for (int i = 0; i < nrLin; i++)
        std::cin >> matrix[i];

    for(int i = 0; i < Q; i++)
        std::cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];

    auto r = solve(nrLin, nrCol, Q, matrix, X1, Y1, X2, Y2);

    for (auto &y : r)
        std::cout << y << '\n';
    
    return 0;
}
