#include "monede.h"

using namespace std;

const Raport unu = Raport(1,1);
const Raport zero = Raport(0,1);
const Raport fair = Raport(1,2);
const Raport minus_unu = zero - unu;

struct node_t{
    Raport a[2][2];

    node_t(){
        ;
    }

    node_t(Raport p){
        a[0][0] = a[1][1] = unu - p;
        a[0][1] = a[1][0] = p;
    }

    node_t operator * (const node_t &other)const{
        node_t ans;
        for(int i = 0;i < 2;i++){
            for(int j = 0;j < 2;j++){
                ans.a[i][j] = zero;
                for(int k = 0;k < 2;k++){
                    ans.a[i][j] = ans.a[i][j] + this->a[i][k] * other.a[k][j];
                }
            }
        }
        return ans;
    }

    node_t identity()const{
        node_t ans;
        ans.a[0][0] = unu;
        ans.a[0][1] = zero;
        ans.a[1][0] = zero;
        ans.a[1][1] = unu;

        return ans;
    }

    node_t inv()const{
        node_t ans = *this;
        Raport tmp = unu / (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
        ans.a[0][0] = a[1][1] * tmp;
        ans.a[0][1] = a[1][0] * tmp * (minus_unu);
        ans.a[1][0] = a[0][1] * tmp * (minus_unu);
        ans.a[1][1] = a[0][0] * tmp;

        return ans;
    }
};

vector<node_t> pow_fair;
vector<node_t> pref;
vector<int> cnt_fair;
void init(int N,const Raport p[]) {
    pref.push_back(node_t(zero));
    cnt_fair.push_back(0);
    for(int i = 0;i < N;i++){
        if(p[i] == fair){
            pref.push_back(pref.back() * node_t(zero));
            cnt_fair.push_back(cnt_fair.back() + 1);
        }
        else{
            pref.push_back(pref.back() * node_t(p[i]));
            cnt_fair.push_back(cnt_fair.back());
        }
    }
    
    node_t fair_matrix = node_t(fair);

    pow_fair.push_back(node_t(zero));
    for(int i = 1;i <= cnt_fair.back();i++){
        pow_fair.push_back(pow_fair.back() *  fair_matrix);
    }
}

Raport solve(int a, int b) {
    a++;
    b++;
    node_t tmp = (pref[b] * pref[a - 1].inv()) * pow_fair[cnt_fair[b] - cnt_fair[a - 1]];
    return tmp.a[0][1];
}
