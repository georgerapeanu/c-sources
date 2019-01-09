#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("pscfft.in","r");
FILE *g = fopen("pscfft.out","w");

const int MOD = 1e9 + 7;

inline int dist(int a,int b,int s){
    b -= a;
    if(b < 0){
        b += s;
    }
    return b;
}

inline int lgpow(int b,int e){
    int p = 1;
    while(e){
        if(e & 1){
            p = 1LL * p * b % MOD;
        }
        e >>= 1;
        b = 1LL * b * b % MOD;
    }
    return p;
}

vector<int> contract(const vector<int> &v,int last,int s,int &fst){
    vector<int> nv;
    fst = 0;
    int n = v.size();
    for(int i = last;i >= 0;i -= s){
        int sum = -1;
        for(int j = s - 1;j >= 0 && i - (s - 1 - j) >= 0;j--){
            if(sum == -1){
                sum = dist(j,v[i - (s - 1 - j)],s);
            }
            else if(sum != dist(j,v[i - (s - 1 - j)],s)){
                return {-1};
            }
            fst = j;
        }
        nv.push_back(sum);
    }

    for(int i = last + 1;i < n;i += s){
        int sum = -1;
        for(int j = 0;j < s && i + j < n;j++){
            if(sum == -1){
                sum = dist(j,v[i + j],s);
            }
            else if(sum != dist(j,v[i + j],s)){
                return {-1};
            }
        }
        nv.push_back(sum);
    }
    
    return nv;
}

int solve(const vector<int> &v,int s){
    int n = v.size();

    for(auto it:v){
        if(it >= s || it < 0){
            return -1;
        }
    }

    int last = -1;

    for(int i = 0;i < n - 1;i++){
        if(last == -1 && dist(v[i],v[i + 1],s) != 1){
            last = i;
        }
    }

    if(last == -1){
        if((int)v.size() > s){
            ///ugly case
            ///we know that there is an invisible split somewhere
            ///the fact that it is not found is due to the sum,excluding the last digit, give the
            ///same reminder divided by s as sum + 1
            ///so it has to contain s^(s-1) - 1 after that,maybe followed by other digits,because
            ///it's (sum + 1)mod s - sum mod s = longest_suf_of_(s-1) + 1,whici is 0
            ///that being said,we want to minimize the numbers which come after that
            ///for that,we want to minimize v[0] - fst,since fst + rem + (s - 1)(s - 1) = v[0](mod s)
            ///so rem = (v[0] - fst) - 1 mod s
            ///so we want the closest value to v[0],whici is not v[0] since rem would be s - 1 in that case
            ///but we are also limited
            ///we cannot have 2 changes in the last digit,since there are no 3 consequtive numbers with the same sum of digits mod s
            ///so we want a single group of (s - 1,0) in the last digits
            ///so we have to put a value of at most lim on the first position
            if((int)v.size() > 2 * s){
                return -1;
            }
            int val;
            int fst;
            int lim = s - 1 - ((n - 1) % s);
            if(lim >= (v[0] + s - 1) % s){
                fst = (v[0] + s - 1) % s;
            }
            else{
                fst = lim; 
            }
            val = (v[0] - fst + s) % s;
            return (1LL * solve({val,val},s) * s + fst) % MOD;
        }
        int cnt = 0;
        bool ok = false;
        for(int i = 0;i < n;i++){
            if(i && v[i] != 0 && v[i - 1] != v[i] - 1){
                return -1;
            }
            else if(i && v[i] == 0 && v[i - 1] != s - 1){
                return -1;
            }
            ok |= (v[i] == 0);
            cnt += ok;
        }
        
        if(cnt == n){
            return 0;
        }
        if(cnt == 0){
            return v[0];
        }
        return (1LL * (cnt + 1) * s - n) % MOD;  
    }

    if(n == 2){
        int v1 = (v[1] - 1 + s) % s;
        int tmp =  solve({v1,v[1]},s);
        int x;
        if(v[0] < v[1]){
            x = v[1] - v[0] - 1;
        }
        else{
            x = v[1] + s - v[0] - 1;
        }
        return ((1LL * lgpow(s,x) * (tmp + 1) - 1) % MOD + MOD) % MOD;
    }

    int fst = 0;
    vector<int> nv = contract(v,last,s,fst);
    int tmp = solve(nv,s);

    if(tmp == -1){
        return -1;
    }

    return (1LL * tmp * s + fst) % MOD;
}

int main(){
    
    int t;
   
    fscanf(f,"%d",&t);

    while(t--){
        int n,s;
        fscanf(f,"%d %d",&n,&s);
        vector<int> v(n,0);
        for(int i = 0;i < n;i++){
            fscanf(f,"%d",&v[i]);
        }  
       
        if(s == 1){
            fprintf(g,"%d\n",(n == 1 && v[0] == 0 ? 0:-1)); 
        }
        else{
            fprintf(g,"%d\n",solve(v,s));
        }
    }

    return 0;
}
