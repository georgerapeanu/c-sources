#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <string.h>

using namespace std;

const int maxp = 5000005;

const int digits[] = {2, 3, 5, 7};

int n, p, father[maxp], cifra[maxp];

void bfs() {
    queue <int> q;
    memset(father, -1, sizeof(father));
    q.push(0);
    father[0] = 0;
    while(!q.empty()) { /// cat timp mai avem noduri de extras
        int node = q.front();
        if(node == n)
            break;
        q.pop();
        for(int i = 0 ; i < 4 ; ++ i) {
            int newnode = (node * 10 + digits[i]) % p;
            if(father[newnode] == -1) { /// nu a fost visitat
                father[newnode] = node;
                cifra[newnode] = digits[i];
                q.push(newnode);
            }
        }
    }
    if(father[n] == -1) {
        cout << "-1\n";
    }
    else {
        vector <int> nr;
        int node = n;
        while(node != 0) {
            nr.push_back(cifra[node]);
            node = father[node];
        }
        for(int i = nr.size() - 1 ; i >= 0 ; -- i)
            cout << nr[i];
        cout << '\n';
    }
}

int main() {
    freopen("cifre4.in", "r", stdin);
    freopen("cifre4.out", "w", stdout);
    int t;
    cin >> t;
    while(t -- ) {
        cin >> n >> p;
        bfs();
    }

}
