#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;
int N;
int V[2005];
int main()
{
    srand(time(NULL));
    cin >> N;
    long long rez = 0,S = 0;;
    for(int i = 1;i <= N;i++){
        cin >> V[i];
        S += V[i];
    }
    int tests = 3.5e4;
    long long dif = 1LL << 60;
    while(tests--){
        random_shuffle(V + 1,V + 1 + N);
        long long sum = 0;
        for(int i = 1;i <= N;i++){
            sum += V[i];
            if(dif > abs(S - 2 * sum)){
                dif = S - 2 * sum;
                rez = max(sum,S- sum);
            }
        }
    }
    cout << rez;
    return 0;
}
