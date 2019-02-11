#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_N = 25;
int p[MAX_N], v[MAX_N], lvl[MAX_N];
vector<int> edg[MAX_N];

const int MOD = 1e9 + 7;


void dfs( int n ) {
    for ( int x : edg[n] )
        if ( x != p[n] ) {
            p[x] = n;
            lvl[x] = lvl[n] + 1;
            dfs( x );
        }
}


#define min( a, b ) ((a) < (b) ? (a) : (b))

int neval;

int LCA( int a, int b ) {
    if ( lvl[a] < lvl[b] )
        swap( a, b );

    while ( lvl[a] > lvl[b] ) {
        neval = min( neval, v[a] );
        a = p[a];
    }

    while ( a != b ) {
        neval = min( neval, v[a] );
        neval = min( neval, v[b] );
        a = p[a];
        b = p[b];
    }

    neval = min( neval, v[a] );
    return a;
}

int main() {
    ifstream fin( "countfefete.in" );
    ofstream fout( "countfefete.out" );

    int n, x, y;
    fin >> n;

    for ( int i = 0; i < n; i++ )
        fin >> v[i];

    for ( int i = 0; i < n - 1; i++ ) {
        fin >> x >> y;
        x--, y--;
        edg[x].push_back( y );
        edg[y].push_back( x );
    }

    p[0] = -1;
    dfs( 0 );

    long long ans = 0;
    for ( int mask = 1; mask < (1 << n); mask++ ) {
        int sum = -1, lca = 0;
        for ( int i = 0; i < n; i++ )
            if ( mask >> i & 1 ) {
                if ( sum == -1 ) {
                    sum = v[i];
                    lca = i;
                    neval = v[i];
                } else {
                    sum ^= v[i];
                    lca = LCA( lca, i );
                }
            }
        sum ^= neval;
        ans = (ans + sum) % MOD;
    }
    fout << ans << endl;


    return 0;
}
