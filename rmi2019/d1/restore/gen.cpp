#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

const int NMAX = 10;
const int MMAX = 20;

int main(){
    random_device rd;
    mt19937 gen(rd());

    int n = gen() % NMAX + 1;
    int m = gen() % MMAX + 1;

    cout << n << " " << m << "\n";

    string s = "";

    for(int i = 0;i < n;i++){
        s += '0' + (gen() % 2);
    }

    bool ok = (gen() % 100 <= 10);

    cerr << s << " " << ok << "\n";

    while(m--){
        int x,y;
        x = gen() % n;
        y = gen() % n;
        if(x > y)swap(x,y);
        int k = gen() % (y - x + 1) + 1;
        string tmp = s;
        sort(tmp.begin() + x,tmp.begin() + y + 1);
        cout << x << " " << y << " " << k << " " << char((ok == false && gen() % 100 <= 50 ? 1:0) ^ tmp[x + k - 1]) << "\n";
    }
    
    return 0;
}
