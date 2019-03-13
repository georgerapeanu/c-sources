#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("grup.in","r");
FILE *g = fopen("grup.out","w");

const int NMAX = 1e5;

vector<int> all;

vector<pair<int,int> > mixed;

int n,s;

int a[NMAX + 5];

char b[NMAX + 5];
char c[NMAX + 5];

int sta[3][NMAX + 5];
int len[3];
int k[3];

int main(){

    fscanf(f,"%d %d %d %d",&n,&s,&k[1],&k[2]);

    k[1] = s - k[1];

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&a[i]);
    }

    fscanf(f,"\n");

    fgets(b + 1,NMAX + 5,f);
    fgets(c + 1,NMAX + 5,f);

    for(int i = 1;i <= n;i++){
        b[i] = '1' - b[i] + '0';

        if(b[i] == '1' && c[i] == '1'){
            all.push_back(a[i]);
        }
        else{
            mixed.push_back({a[i],(b[i] - '0') + 2 * (c[i] - '0')});
        }
    }


    sort(all.begin(),all.end());
    sort(mixed.begin(),mixed.end());

    int cnt = 0;
    long long sum = 0;
    int last = -1;

    for(int i = 0;i < (int)mixed.size() && cnt < s;i++){
        last = i;
        if(mixed[i].second == 0){
            sum += mixed[i].first;
            cnt++;
            sta[0][++len[0]] = i;
            continue;
        }
        else{
            if(len[mixed[i].second] < k[mixed[i].second]){
                sta[mixed[i].second][++len[mixed[i].second]] = i;
                sum += mixed[i].first;
                cnt++;
            }
        }
    }

    long long ans = (cnt == s ? sum:1LL << 60);

    k[0] = NMAX + 5;

    bool ok = true;

    for(int i = 0;i < (int)all.size() && ok;i++){
        sum += all[i];
        cnt++;
        for(int j = 1;j <= 2;j++){
            k[j]--;
            if(len[j] > k[j]){
                if(len[j] > 0){
                    cnt--;
                    sum -= mixed[sta[j][len[j]]].first;
                    len[j]--;
                }
                else{
                    ok = false;
                    break;
                }
            }
        }
        if(!ok){
            break;
        }

        while(last < (int)mixed.size() && cnt < s){
            last++;
            if(last >= (int)mixed.size()){
                break;
            }
            if(len[mixed[last].second] < k[mixed[last].second]){
                sum += mixed[last].first;
                cnt++;
                sta[mixed[last].second][++len[mixed[last].second]] = last;
            }
        }

        while(last >= 0 && cnt > s){
            if(sta[mixed[last].second][len[mixed[last].second]] != last){
                last--;
                continue;
            }
            cnt--;
            sum -= mixed[last].first;
            len[mixed[last].second]--;
            last--;
        }

        if(last < 0){
            break;
        }

        if(cnt == s){
            ans = min(ans,sum);
        }
    }

    fprintf(g,"%lld",ans);

    fclose(f);
    fclose(g);

    return 0;
}
