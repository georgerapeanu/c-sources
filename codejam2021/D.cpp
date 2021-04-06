#include <iostream>
#include <cassert>

using namespace std;

const int NMAX = 50;

int n,q,t;
int _n;
int v[NMAX + 5];

int ask(int a,int b,int c){
    cout << a << " ";
    cout << b << " ";
    cout << c << endl;
    int ans = 0;
    cin >> ans;
    return ans;
}

void answer(){
    for(int i = 1;i <= n;i++){
        cout << v[i] << " ";
    }
    cout << endl;
    int ans;
    cin >> ans;
    assert(ans == 1);
}

int main(){

    cin >> t >> _n >> q;

    while(t--){
        for(int i = 0;i <= _n + 1;i++){
            v[i] = 0;
        }
        v[1] = 1;
        v[2] = 2;
        n = 2;

        for(int i = 3;i <= _n;i++){
            int l = 0;
            int r = n + 1;

            while(r - l > 2){
                int cnt_l = (r - l + 2) / 3;
                int cnt_r = (r - l) / 3;
                int ll = l + cnt_l;
                int rr = r - cnt_r;

                int ans = ask(v[ll],v[rr],i);

                if(ans == v[ll]){
                    r = ll;
                }else if(ans == i){
                    l = ll;
                    r = rr;
                }else{
                    l = rr;
                }
            }
            if(r - l == 2){
                if(l == 0){
                    if(ask(v[l + 1],v[l + 2],i) == v[l + 1]){
                        r = l + 1;
                    }else{
                        l = l + 1;
                    }
                }else{
                    if(ask(v[l],v[l + 1],i) == v[l + 1]){
                        l = l + 1;
                    }else{
                        r = l + 1;
                    }
                }
            }
            for(int i = ++n;i > r;i--){
                v[i] = v[i - 1];
            }
            v[r] = i;
        }
        
        answer();
    }

    return 0;
}
