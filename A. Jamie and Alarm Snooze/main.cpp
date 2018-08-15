#include <iostream>

using namespace std;
int x,y;
int S,rez;
int nrmin;
bool lucky(int nrmin){
    x = nrmin / 60;
    y = nrmin % 60;
    if(x % 10 == 7 || y % 10 == 7){
        return 1;
    }
    return 0;
}
int main()
{
    cin >> S >> x >> y;
    nrmin = x * 60 + y;
    while(!lucky(nrmin)){
        nrmin -= S;
        if(nrmin < 0){
            nrmin += 24 * 60;
        }
        rez++;
    }
    cout << rez;
    return 0;
}
