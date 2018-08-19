#include <iostream>
#include <iomanip>
#include <deque>
#include <algorithm>
#include <vector>

using namespace std;

int N,M;
int V[100005];

bool ok(double dist){
    double delta = 2 * M / (N);

    deque<double> points;

    for(int i = 1;i < N;i++){
        points.push_back(i * delta + V[1]);
    }

    while(points.back() <= points.front()){
        points.push_front(points.back());
        points.pop_back();
    }

    for(auto it:points){
        cout << it << " ";
    }
    cout << "\n\n\n\n";

    vector< pair<double,double> > S;

    for(int i = 2;i <= N;i++){
        S.push_back({max((double)0,V[i] - dist),min((double)2 * M,V[i] + dist)});
    }

    for(auto it:S){
        if(it.first > points.front() || 2 * M - it.second > points.back()){
            return false;
        }

        if(it.first <= points.front() && points.front() <= it.second){
            if(2 * M - it.second <= points.back() && points.back() <= 2 * M - it.first){
                double d1 = points.front() - it.first;
                double d2 = (2 * M - it.first) - points.back();
                if(d1 < d2){
                    points.pop_front();
                }
                else{
                    points.pop_back();
                }
            }
            else{
                points.pop_front();
            }
        }
        else if(2 * M - it.second <= points.back() && points.back() <= 2 * M - it.first){
            points.pop_back();
        }
    }

    return points.empty();
}

int main(){

    cin >> M >> N;

    for(int i = 1;i <= N;i++){
        int x;
        char bonus;
        cin >> x >> bonus;
        x = (bonus == 'R' ? 2 * M - x : x);
        V[i] = x;
    }

    sort(V + 1,V + 1 + N);

    double st = 0,dr = 3e8;

    cout << ok(1);

    /*while(dr - st > 1e-7){
        double mid = (st + dr) / 2;
        if(ok(mid)){
            dr = mid;
        }
        else{
            st = mid;
        }
    }*/

    cout << fixed << setprecision(7) << dr;

    return 0;
}
