///basicly,the thing is that a pirate needs exactly a[i] pirates to succes,so ditch the others
///so the ditched pirates act like they have no profit
///so the strategy is obvious:ditch the biggest pirates and if you don't have enough pirates at the end,bring some of the 0 profit ones
///so we can mentain a deque,on which we would like to maintain pairs of (profit of the pirate,and how pirates have this pirate)
///we want to pop the most expensive ones,and push in the front some of the 0 ones
///since we actually pay this pirates,the pairs now change to (delta between two clases of pirates,and count of pirates)
///the pirates that make a good profit,if we have to pay one of the to get our plan going,it can be shown that there is a better solution using other pirates,or that we cannot make a profit.so for simplicity,we push this pirates at the end with delta=-1.notice how there can be at most one of them in the deque at any given time
#include <cstdio>
#include <deque>
#include <algorithm>

using namespace std;

FILE *f = fopen("caraibe.in","r");
FILE *g = fopen("caraibe.out","w");

int n;
int v[65003];

int main() {

    fscanf(f,"%d",&n);

    for(int i = 1; i <= n - 2; i++) {
        fscanf(f,"%d",&v[i]);
    }

    deque<pair<int,int> > dq;//(delta,count),there are count elemnts with pref_sum(delta)
    int indq = 0;

    for(int i = n - 1; i; i--) {
        int fute = n - i - v[i];

        while(dq.size() && fute) {
            if(dq.back().second <= fute) {
                fute -= dq.back().second;
                indq -= dq.back().second;
                dq.pop_back();
            }
            else {
                dq.back().second -= fute;
                indq -= fute;
                fute = 0;
            }
        }

        if(dq.size() && dq.back().first == -1) {
            dq.back().second += n - i - v[i];
            indq += n - i - v[i];
        }
        else {
            dq.push_front({1,max(v[i] - indq,0)});
            indq += max(v[i] - indq,0);
            if(i > 1) {
                dq.push_back({-1,1});///basicly so big that if you have this,welp...
                indq++;
            }
        }
    }

    if(dq.size() && dq.back().first == -1) {
        fprintf(g,"0\n");
    }
    else {
        long long prof = 1e10;
        long long delta = 0;
        for(auto it:dq) {
            delta += it.first;
            prof -= delta * it.second;
        }
        fprintf(g,"%lld\n",prof);
    }

    fclose(f);
    fclose(g);

    return 0;
}
