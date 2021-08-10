#include <bits/stdc++.h>

using namespace std;

int t;
int n;

void do_swap(int a,int b){
    if(a > b){
        swap(a,b);
    }
    if(a != b){
        cout << "S " << a << " " << b << endl;
        int ans;
        cin >> ans;
        if(ans == -1){
            exit(0);
        }
    }
}

int get_min(int st,int dr){
    if(st == dr){
        return st;
    }

    int ans;

    cout << "M " << st << " " << dr << endl;
    cin >> ans;

    if(ans == -1){
        exit(0);
    }

    return ans;
}

void done(){
    cout << "D" << endl;
    int ans;
    cin >> ans;
    if(ans == -1){
        exit(0);
    }
}

int main(){

    cin >> t >> n;

    while(t--){
        for(int i = 1;i <= n;i++){
            do_swap(get_min(i,n),i);
        }
        done();
    }

    return 0;
}
