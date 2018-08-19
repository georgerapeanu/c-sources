#include <iostream>
#include <algorithm>

using namespace std;

int N;
int V[105],sum;

int main(){
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> V[i];
        sum += V[i];
    }
    sort(V + 1,V + 1 + N);
    for(int pref = 0;pref <= N;pref++){
        if(sum + pref * 5 >= N * 4.5){
            cout << pref;
            return 0;
        }
        sum -= V[pref + 1];
    }
    return 0;
}
