#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n;

int target[300];
int pass[300];
int state[300];
bool viz[300];

int sample[8];
int fr[8];

vector<pair<int,int> > v;

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        target[i] = a * 4 + 2 * b + c;
        fr[target[i]]++;
        if(target[i] == 0) {
            viz[i] = true;
        }
    }

    for(int i = 1; i <= n; i++) {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        pass[i] = a * 4 + 2 * b + c;
    }

    sample[7] = 1;
    viz[1] = true;

    for(int conf = 7; conf; conf--) {
        if(sample[conf] == 0) {
            continue;
        }
        for(int i = 1; i <= n; i++) {
            if(viz[i] == false && target[i] == conf) {
                viz[i] = true;
                v.push_back({sample[conf],i});
                state[i] = true;
                sample[target[i] & pass[i]] = i;
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        if(viz[i] == false) {
            if(sample[target[i]] == 0) {
                for(int h = 0; h < 3; h++) {
                    if((target[i] >> h) & 1) {
                        if(sample[1 << h] == 0) {
                            printf("Impossible\n");
                            return 0;
                        }
                        v.push_back({sample[1 << h],i});
                    }
                }
                sample[target[i]] = i;
            }
            else {
                v.push_back({sample[target[i]],i});
            }
        }
    }

    printf("Possible\n");

    for(int i = 1; i <= n; i++) {
        printf("%d ",state[i]);
    }
    printf("\n");

    printf("%d\n",(int)v.size());

    for(auto it:v) {
        printf("%d %d\n",it.first,it.second);
    }


    return 0;
}
