#include <bits/stdc++.h>

using namespace std;

int t;

int n,l;
int a[100005];

int main() {

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&l);

        for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
        }

        long double pos_a = 0;
        long double pos_b = double(l);
        int v_a = 1,v_b = 1;
        long double ti = 0;

       
        while(pos_a < pos_b){
            int id_a = v_a;
            int id_b = n - v_b + 1;

            if(id_a > id_b){
                ti += (pos_b - pos_a) / (v_a + v_b);
                break;
            }
            else if((pos_b - a[id_b]) / v_b < (a[id_a] - pos_a) / v_a){
                ti += (pos_b - a[id_b]) / v_b;
                pos_a += (pos_b - a[id_b]) / v_b * v_a;
                pos_b = a[id_b];
                v_b++;
            }
            else if((pos_b - a[id_b]) / v_b > (a[id_a] - pos_a) / v_a){
                ti += (a[id_a] - pos_a) / v_a;
                pos_b -= (a[id_a] - pos_a) / v_a * v_b;
                pos_a = a[id_a];
                v_a++;
            }
            else{
                ti += (a[id_a] - pos_a) / v_a;
                pos_a = a[id_a];
                pos_b = a[id_b];
                v_a++;
                v_b++;
            }
        }

        printf("%.7f\n",double(ti));
    }

    return 0;
}
