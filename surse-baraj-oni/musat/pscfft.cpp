#include <iostream>
#include <fstream>

using namespace std;

const int MAX_N = 5e5 + 100;
int v[MAX_N];
int v0[MAX_N];


int main() {
    ifstream fin( "pscfft.in" );
    ofstream fout( "pscfft.out" );

    int t;
    for ( fin >> t; t > 0; t-- ) {
        int n, s;
        fin >> n >> s;

        for ( int i = 0; i < n; i++ )
            fin >> v0[i];
        int k = 1, i;
        for ( i = 1; i <= MAX_N; i++ ) {
            if ( k * s <= i )
                k *= s;
            v[i] = (v[i % k] + i / k) % s;
//            cout << v[i] << ' ';
            if ( i >= n ) {
                int j = 0;
                while ( j < n && v[i - n + 1 + j] == v0[j] )
                    j++;
                if ( j == n )
                    break;
            }
        }
//        cout << endl;

        if ( i <= MAX_N )
            fout << i - n + 1 << '\n';
        else
            fout << -1 << '\n';
    }

    return 0;
}
