#include <cstdio>
#include <cassert>

using namespace std;

FILE *in = fopen("in","r");
FILE *code = fopen("code","r");
FILE *out = fopen("out","w");

int v[int(1e6 + 5)];

int main(int argc,char **argv) {

//   assert(argc == 3);

//   int fst = (argv[1][0] - '0') * (argv[1][1] >= '0' && argv[1][1] <= '9' ? 10:1) + (argv[1][1] <= '9' && argv[1][1] >= '0') * (argv[1][1] - '0' );
//   int snd = (argv[2][0] - '0') * (argv[2][1] >= '0' && argv[2][1] <= '9' ? 10:1) + (argv[2][1] <= '9' && argv[2][1] >= '0') * (argv[2][1] - '0' );

    int n = 0;

    while(fscanf(code,"%d,",&v[n]) == 1) {
        n++;
    }

    int start = 0;

//   v[1] = fst;
//   v[2] = snd;

    while(start <= n) {
        int mode = v[start] % 100;
        int val = v[start] / 100;
        start++;

        if(mode == 99) {
            break;
        }
        else if(mode == 1) {
            int a = (val % 10 == 0 ? v[v[start]]:v[start]);
            val /= 10;
            start++;
            int b = (val % 10 == 0 ? v[v[start]]:v[start]);
            val /= 10;
            start++;
            int c = (val % 10 == 0 ? v[start]:-1);
            val /= 10;
            start++;
            v[c] = a + b;
        }
        else if(mode == 2) {
            int a = (val % 10 == 0 ? v[v[start]]:v[start]);
            val /= 10;
            start++;
            int b = (val % 10 == 0 ? v[v[start]]:v[start]);
            val /= 10;
            start++;
            int c = (val % 10 == 0 ? v[start]:-1);
            val /= 10;
            start++;
            v[c] = a * b;
        }
        else if(mode == 3) {
            int a = (val % 10 == 0 ? v[start]:-1);
            val /= 10;
            start++;
            fscanf(in,"%d",&v[a]);
        }
        else if(mode == 4) {
            int a = (val % 10 == 0 ? v[v[start]]:v[start]);
            val /= 10;
            start++;
            fprintf(out,"%d",a);
        }
        else if(mode == 5) {
            int a = (val % 10 == 0 ? v[v[start]]:v[start]);
            val /= 10;
            start++;
            int b = (val % 10 == 0 ? v[v[start]]:v[start]);
            val /= 10;
            start++;
            if(a != 0) {
                start = b;
            }
        }
        else if(mode == 6) {
            int a = (val % 10 == 0 ? v[v[start]]:v[start]);
            val /= 10;
            start++;
            int b = (val % 10 == 0 ? v[v[start]]:v[start]);
            val /= 10;
            start++;
            if(a == 0) {
                start = b;
            }
        }
        else if(mode == 7) {
            int a = (val % 10 == 0 ? v[v[start]]:v[start]);
            val /= 10;
            start++;
            int b = (val % 10 == 0 ? v[v[start]]:v[start]);
            val /= 10;
            start++;
            int c = (val % 10 == 0 ? v[start]:-1);
            val /= 10;
            start++;
            if(a < b) {
                v[c] = 1;
            }
            else {
                v[c] = 0;
            }
        }
        else if(mode == 8) {
            int a = (val % 10 == 0 ? v[v[start]]:v[start]);
            val /= 10;
            start++;
            int b = (val % 10 == 0 ? v[v[start]]:v[start]);
            val /= 10;
            start++;
            int c = (val % 10 == 0 ? v[start]:-1);
            val /= 10;
            start++;
            if(a == b) {
                v[c] = 1;
            }
            else {
                v[c] = 0;
            }
        }
        else {
            ///dunno
        }
    }

///   fprintf(out,"%d\n",v[0]);

    fclose(in);
    fclose(code);
    fclose(out);

    return 0;
}
