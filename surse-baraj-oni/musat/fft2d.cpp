#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

const int MAX_N = 16;
const int MAX_T = 1e5 + 100;

pair<int, int> blacks[MAX_T];

bool cmp_node( pair<int, int> a, pair<int, int> b ) {
    if ( a.first != b.first )
        return a.first > b.first;
    else
        return a.second < b.second;
}

long long par[MAX_T], imp[MAX_T];
int F;

bool can_reach( int h1, int x1, int h2, int x2 ) {
    /// h1 < h2
    if ( h1 > h2 )
        swap( h1, h2 );

//    cout << F - h1 - 1 << endl;

    if ( (x1 >> (F - h1 - 1)) != (x2 >> (F - h1 - 1)) )
        return 0;
    int mask = (1 << F - h2 - 1) - 1;
    if ( (x1 & mask) != (x2 & mask) )
        return 0;
    return 1;
}


int main() {
    ifstream fin( "fft2d.in" );
    ofstream fout( "fft2d.out" );

    int T;
    fin >> F >> T;

    for ( int i = 0; i < T; i++ )
        fin >> blacks[i].first >> blacks[i].second;
    sort( blacks, blacks + T, cmp_node );

    long long ans = 1 << (2 * F - 2);
    for ( int i = 0; i < T; i++ ) {
        imp[i] = (1 << F - 1 - blacks[i].first);

        for ( int j = 0; j < i; j++ ) {
            if ( can_reach( blacks[i].first, blacks[i].second, blacks[j].first, blacks[j].second ) ) {
//                cout << blacks[i].first << ' ' << blacks[i].second << ' ' << blacks[j].first << ' ' << blacks[j].second << endl;
                imp[i] += par[j];
                par[i] += imp[j];
            }
        }

//        cout << blacks[i].first << ' ' << blacks[i].second << ':' << imp[i] << ' ' << par[i] << endl;

        ans -= (imp[i] - par[i]) * (1 << blacks[i].first);
    }

    fout << ans;

    return 0;
}
