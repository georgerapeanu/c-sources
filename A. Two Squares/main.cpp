#include <iostream>
#include <algorithm>

using namespace std;

int N;
pair<int,int> A[5];
pair<int,int> B[5];

int det(pair<int,int> a,pair<int,int> b,pair<int,int> c){
    return a.first * b.second + b.first * c.second + c.first * a.second - a.first * c.second - b.first * a.second - c.first * b.second;
}

bool inside(pair<int,int> P[],int N,pair<int,int> A){
    int arie = 0;
    for(int i = 1;i <= N;i++){
        arie += abs(det(P[1],P[i],P[i % N + 1]));
        arie -= abs(det(A,P[i],P[i % N + 1]));
    }
    return arie == 0;
}

bool onSegment(pair<int,int> p, pair<int,int> q, pair<int,int> r)
{
    if (q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) &&
        q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second))
       return true;

    return false;
}

bool doIntersect(pair<int,int> p1, pair<int,int> q1, pair<int,int> p2, pair<int,int> q2)
{
    int o1 = det(p1, q1, p2);
    int o2 = det(p1, q1, q2);
    int o3 = det(p2, q2, p1);
    int o4 = det(p2, q2, q1);

    if (o1 * o2 < 0 && o3 * o4 < 0)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

int main(){
    N = 4;
    for(int i = 1;i <= 4;i++){
        cin >> A[i].first >> A[i].second;
    }
    for(int i = 1;i <= 4;i++){
        cin >> B[i].first >> B[i].second;
    }

    for(int i = 1;i <= 4;i++){
        if(inside(A,4,B[i])){
            cout << "YES";
            return 0;
        }
    }
    for(int i = 1;i <= 4;i++){
        if(inside(B,4,A[i])){
            cout << "YES";
            return 0;
        }
    }

    for(int i = 1;i <= 4;i++){
        for(int j = 1;j <= 4;j++){
            if(doIntersect(A[i],A[i % N + 1],B[j],B[j % N + 1])){
                cout << "YES";
                return 0;
            }
        }
    }

    cout << "NO";

    return 0;
}
