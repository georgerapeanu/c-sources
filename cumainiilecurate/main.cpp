#include <cstdio>
long long c;
long long N,M,i,pos,j;
long long v[100001],val,best[100001],tmp[100001];
class InputReader {
    public:
        InputReader() {}
        InputReader(const char *file_name) {
            input_file = fopen(file_name, "r");
            cursor = 0;
            fread(buffer, SIZE, 1, input_file);
        }
        inline InputReader &operator >>(long long &n) {
            while(buffer[cursor] < '0' || buffer[cursor] > '9') {
                advance();
            }
            n = 0;
            while('0' <= buffer[cursor] && buffer[cursor] <= '9') {
                n = n * 10 + buffer[cursor] - '0';
                advance();
            }
            return *this;
        }
    private:
        FILE *input_file;
        static const int SIZE = 1 << 17;
        int cursor;
        char buffer[SIZE];
        inline void advance() {
            ++ cursor;
            if(cursor == SIZE) {
                cursor = 0;
                fread(buffer, SIZE, 1, input_file);
            }
        }
};
int main()
{
    InputReader f("cumainilecurate.in");
    f>>N>>M;
    for(i=1;i<=N;i++)
    {
        f>>v[i];
    }
    for(i=N;i>=1;i--)
    {
        for(j=i+1;j<=N;j++)
        {
            if(v[j]>v[i])
            break;
        }
        best[i]=best[j]+1;
        tmp[i]=j;
    }
    FILE *g;
    g=fopen("cumainilecurate.out","w");
    for(i=1;i<=M;i++)
    {
        f>>c;
        if(c==1)
        {
            f>>pos>>val;
            v[pos]=val;
            for(j=pos+1;j<=N;j++)
            {
                if(v[j]>v[pos])
                break;
            }
            best[pos]=best[j]+1;
            for(j=pos-1;j>0;j--)
            {
                if(v[j]<v[pos]&&tmp[j]>=pos)
                {
                    tmp[j]=pos;
                }
                best[j]=best[tmp[j]]+1;
            }
        }
        else
        {
            f>>pos;
            fprintf(g,"%lld\n",best[pos]);
        }
    }
    fclose(g);
}
