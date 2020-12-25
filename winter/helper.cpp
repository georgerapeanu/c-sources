#include <cstdio>

using namespace std;

int get_pos(int conf,int pos,int base){
    while(pos > 0){
        conf /= base;
        pos--;
    }
    return conf % base;
}

int main(){
    for(int conf_l = 0;conf_l < 27;conf_l++){
        for(int conf_c = 0;conf_c < 27;conf_c++){
            for(int i = 0;i < 3;i++){
                for(int j = 0;j < 3;j++){
                    printf("%d",(get_pos(conf_l,i,3) + get_pos(conf_c,j,3)) % 3);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}
