#include <cstdio>

using namespace std;

FILE *f = fopen("mstack.in","r");
FILE *g = fopen("mstack.out","w");

class DequeMimic{
private:
    int fst_sz,fst_id;///first stack, with the front part
    int snd_sz,snd_id;///second stack,with the back part
    int tmp_id,tmp_sz;
public:

    DequeMimic(int fst_id,int snd_id,int tmp_id){
        fst_sz = snd_sz = tmp_sz = 0;
        this->fst_id = fst_id;
        this->snd_id = snd_id;
        this->tmp_id = tmp_id;
    }

    void push_back(int move_id = 0){
        if(move_id == 0){
            fprintf(g,"push %d\n",snd_id);
        }
        else{
            fprintf(g,"move %d %d\n",move_id,snd_id);
        }
        snd_sz++;
    }

    void push_front(int move_id = 0){
        if(move_id == 0){
            fprintf(g,"push %d\n",fst_id);
        }
        else{
            fprintf(g,"move %d %d\n",move_id,fst_id);
        }
        fst_sz++;
    }

    void pop_back(int move_id = 0){
        if(snd_sz == 0){
            while(tmp_sz + 1 < fst_sz){
                fst_sz--;
                tmp_sz++;
                fprintf(g,"move %d %d\n",fst_id,tmp_id);
            }
            while(fst_sz > 0){
                fst_sz--;
                snd_sz++;
                fprintf(g,"move %d %d\n",fst_id,snd_id);
            }
            while(tmp_sz > 0){
                tmp_sz--;
                fst_sz++;
                fprintf(g,"move %d %d\n",tmp_id,fst_id);
            }
        }

        snd_sz--;
        if(move_id == 0){
            fprintf(g,"pop %d\n",snd_id);
        }
        else{
            fprintf(g,"move %d %d\n",snd_id,move_id);        }
    }

    void pop_front(int move_id = 0){
        if(fst_sz == 0){
            while(tmp_sz + 1 < snd_sz){
                snd_sz--;
                tmp_sz++;
                fprintf(g,"move %d %d\n",snd_id,tmp_id);
            }
            while(snd_sz > 0){
                snd_sz--;
                fst_sz++;
                fprintf(g,"move %d %d\n",snd_id,fst_id);
            }
            while(tmp_sz > 0){
                tmp_sz--;
                snd_sz++;
                fprintf(g,"move %d %d\n",tmp_id,snd_id);
            }
        }

        fst_sz--;
        if(move_id == 0){
            fprintf(g,"pop %d\n",fst_id);
        }
        else{
            fprintf(g,"move %d %d\n",fst_id,move_id);        }
    }

    void front(){
        if(fst_sz == 0){
            while(tmp_sz + 1 < snd_sz){
                snd_sz--;
                tmp_sz++;
                fprintf(g,"move %d %d\n",snd_id,tmp_id);
            }
            while(snd_sz > 0){
                snd_sz--;
                fst_sz++;
                fprintf(g,"move %d %d\n",snd_id,fst_id);
            }
            while(tmp_sz > 0){
                tmp_sz--;
                snd_sz++;
                fprintf(g,"move %d %d\n",tmp_id,snd_id);
            }
        }
        fprintf(g,"top %d\n",fst_id);
    }

    void back(){
        if(snd_sz == 0){
            while(tmp_sz + 1 < fst_sz){
                fst_sz--;
                tmp_sz++;
                fprintf(g,"move %d %d\n",fst_id,tmp_id);
            }
            while(fst_sz > 0){
                fst_sz--;
                snd_sz++;
                fprintf(g,"move %d %d\n",fst_id,snd_id);
            }
            while(tmp_sz > 0){
                tmp_sz--;
                fst_sz++;
                fprintf(g,"move %d %d\n",tmp_id,fst_id);
            }
        }
        fprintf(g,"top %d\n",snd_id);
    }

    int size(){
        return fst_sz + snd_sz;
    }
};

char c[10];

int main(){

    int n;

    fscanf(f,"%d\n",&n);

    int total = 0;
    int dump_id = 4;

    DequeMimic dq(1,2,3);

    while(n--){
        fgets(c + 1,10,f);

        if(c[1] == 'p' && c[2] == 'u'){
            total++;
            dq.push_back();
            if(dq.size() > (total + 1) / 2){
                dq.pop_front(dump_id);
            }

        }
        else if(c[1] == 'p' && c[2] == 'o'){
            total--;
            dq.pop_back();
            if(dq.size() < (total + 1) / 2){
                dq.push_front(dump_id);
            }
        }
        else if(c[1] == 't'){
            dq.back();
        }
        else{
            dq.front();
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
