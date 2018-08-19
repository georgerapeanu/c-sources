#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;
int main() {
    FILE *f = fopen("out","r");
    FILE *g = fopen("ok","r");
    freopen("in","r",stdin);

    int N,M;
    cin >> N >> M;
    while(M--){
        int a,b;
        fscanf(f,"%d",&a);
        fscanf(g,"%d",&b);
        if(a != b){
            cout << "WA\n";
            while(1);
        }
    }
    cout << "OK\n";
    return 0;
}
