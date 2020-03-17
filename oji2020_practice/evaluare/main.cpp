#include <cstdio>

using namespace std;

FILE *f = fopen("evaluare.in","r");
FILE *g = fopen("evaluare.out","w");

int fact();
int term();
int expr();

char c[100005];
int ind;

int fact(){
    if(c[ind] == '\0' || c[ind] == '\n'){
        return 0;
    }
    if(c[ind] == '('){
        ind++;
        int ans = expr();
        ind++;
        return ans;
    }
    int tmp = 0;

    while('0' <= c[ind] && c[ind] <= '9'){
        tmp = tmp * 10 + (c[ind] - '0');
        ind++;
    }

    return tmp;
}

int term(){
    int ans = fact();

    while(c[ind] == '*' || c[ind] == '/'){
        if(c[ind] == '*'){
            ind++;
            ans = ans * fact();
        }
        else{
            ind++;
            ans = ans / fact();
        }
    }

    return ans;
}

int expr(){
    int ans = term();

    while(c[ind] == '+' || c[ind] == '-'){
        int sgn = (c[ind] == '+' ? 1:-1);
        ind++;
        ans = ans + sgn * term();
    }

    return ans;
}

int main(){

    fgets(c,100005,f);

    fprintf(g,"%d\n",expr());

    fclose(f);
    fclose(g);

    return 0;
}
