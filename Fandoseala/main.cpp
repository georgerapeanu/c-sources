#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
FILE *f = fopen("fandoseala.in","r");
FILE *g = fopen("fandoseala.out","w");
int T;
int N,K;
pair<int,int> P[305];
pair<double,int> t[305];
int A,B;
void reorder(int &A,int &B,int &C){
    if(A > B){
        swap(A,B);
    }
    if(A > C){
        swap(A,C);
    }
    if(B > C){
        swap(B,C);
    }
}
int det(pair<int,int> a,pair<int,int> b,pair<int,int> c){
    return a.first * b.second + b.first * c.second + c.first * a.second - a.first * c.second - b.first * a.second - c.first * b.second;
}
double dist(pair<int,int> a,pair<int,int> b){
    return sqrt(double(a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}
double raza(int c){
    return dist(P[A],P[c]) * dist(P[B],P[c]) / abs(det(P[A],P[B],P[c]));
}
bool cmp(int a,int b){
    return raza(a) < raza(b);
}
const int LEN = 1e4;
int ind = LEN - 1;
char buff[LEN];
int i32(){
    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    int rez = 0;
    while(!(buff[ind] < '0' || buff[ind] > '9')){
        rez = rez * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return rez;
}
int main(){
    T = i32();
    while(T--){
        N = i32();
        K = i32();
        int lowest = 1;
        for(int i = 1;i <= N;i++){
             P[i].first = i32();
             P[i].second = i32();
             if(P[lowest].first > P[i].first){
                lowest = i;
             }
        }
        A = lowest;
        B = 1 + (A == 1);
        for(int i = 1;i <= N;i++){
            if(i != A && det(P[A],P[B],P[i]) < 0){
                B = i;
            }
        }
        int len = 0;
        double tmp = dist(P[A],P[B]);
        for(int i = 1;i <= N;i++){
            if(i != A && i != B){
                t[++len].second = i;
                t[len].first = raza(i);
                if((2 * P[i].first - P[A].first - P[B].first) * (2 * P[i].first - P[A].first - P[B].first) + (2 * P[i].second - P[A].second - P[B].second) * (2 * P[i].second - P[A].second - P[B].second) <= tmp * tmp){
                    t[len].first *= -1;
                }
            }
        }
        nth_element(t + 1,t + K - 2,t + len + 1);
        int C = t[K - 2].second;
        reorder(A,B,C);
        fprintf(g,"%d %d %d\n",A,B,C);
    }
    fclose(f);
    fclose(g);
    return 0;
}
