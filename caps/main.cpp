#include <cstdio>
#include <cstring>
using namespace std;
FILE *f = fopen("caps.in","r");
FILE *g = fopen("caps.out","w");
int N,Q,len;
char C[100005];
long long pos;
char getc(long long pos,long long stage,bool sw){
    if(!stage){
        if(sw){
            if('a' <= C[pos] && C[pos] <= 'z'){
                return C[pos] + 'A' - 'a';
            }
            else {
                return C[pos] + 'a' - 'A';
            }
        }
        else {
            return C[(int)pos];
        }
    }
    if(pos <= ((long long)len << (stage - 1))){
        return getc(pos,stage - 1,sw);
    }
    return getc(pos - ((long long)len << (stage - 1)),stage - 1,!sw);
}
long long frAfter1Stage[280];
int frA[100005][26];
int fra[100005][26];
long long getrez(long long pos,long long stage,bool sw,char c){
    if(!stage){
        if(sw){
            if('a' <= c && c <= 'z'){
                c = c + 'A' - 'a';
            }
            else{
                c = c + 'a' - 'A';
            }
        }
        if('A' <= c && c <= 'Z'){
            return (long long)frA[pos][c - 'A'];
        }
        return (long long)fra[pos][c - 'a'];
    }
    if(pos <= ((long long)len << (stage - 1))){
        return getrez(pos,stage - 1,sw,c);
    }
    long long rez = 0;
    if(stage == 1){
        rez += getrez(len,stage - 1,sw,c);
    }
    else{
        rez += frAfter1Stage[c] << (stage - 2);
    }
    return rez + getrez(pos - ((long long)len << (stage - 1)),stage - 1,!sw,c);
}
int main()
{
    fscanf(f,"%d %d\n",&N,&Q);
    fgets(C + 1,100005,f);
    len = strlen(C + 1);
    len -= (C[len] == '\n');
    for(int i = 1;i <= len;i++){
        frAfter1Stage[C[i]]++;
        if('a' <= C[i] && C[i] <= 'z'){
            frAfter1Stage[C[i] - 'a' + 'A']++;
            fra[i][C[i] - 'a']++;
        }
        else{
            frAfter1Stage[C[i] + 'a' - 'A']++;
            frA[i][C[i] - 'A']++;
        }
        for(int j = 0;j < 26;j++){
            fra[i][j] += fra[i - 1][j];
            frA[i][j] += frA[i - 1][j];
        }
    }
    int stage = 0;
    while(( (long long)len << stage ) <= (long long)1e18){
        stage++;
    }
    while(Q--){
        fscanf(f,"%lld",&pos);
        char tmp = getc(pos,stage,0);
        fputc(tmp,g);
        fprintf(g," %lld\n",getrez(pos,stage,0,tmp));
    }
    fclose(f);
    fclose(g);
    return 0;
}
