#include <bits/stdc++.h>

using namespace std;

int ask(int a,int b,int c){
    int ans;
    cout << "? " << a << " " << b << " " << c << endl;
    cin >> ans;
    return ans;
}

void answer(int nod){
    cout << "! " << nod << endl;
    exit(0);
}


int main(){
    
    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    int h;

    cin >> h;

    int n = (1 << h) - 1;

    map<int,int> fr;

    for(int i = 1;i <= 420;i++){
        int a,b,c;
        a = b = c = gen() % n + 1;

        while(a == b){
            b = gen() % n + 1;
        }

        while(a == c || b == c){
            c = gen() % n + 1;
        }

        fr[ask(a,b,c)]++;
    }

    vector<pair<int,int> > tmp;

    for(auto it:fr){
        tmp.push_back({it.second,it.first});
    }

    sort(tmp.begin(),tmp.end());
    reverse(tmp.begin(),tmp.end());

    int u = tmp[0].second;
    int v = tmp[1].second;

    for(int i = 1;i <= n;i++){
        if(i == u || i == v){
            continue;
        }
        if(ask(u,v,i) == i){
            answer(i);
            return 0;
        }
    }

    return 0;
}
