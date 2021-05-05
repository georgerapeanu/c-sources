#include <bits/stdc++.h>

using namespace std;
enum ErrorType {
  OK,
  NO_FILE,
  BAD_OUTPUT,
  INCORECT,
  GRADER_ERROR
};

const char* errmsg[] = {"OK", "Fisier de iesire inexistent", "Fisier de iesire corupt", "Incorrect", "Grader error"};
const int score[] = {0,9,18,30,43};

void handleError(ErrorType err,int subtask_number) {
  if(err == OK)
    printf("%d",score[subtask_number]);
  else
    printf("0");
  fprintf(stderr, "%s", errmsg[err]);
  exit(0);
}

const int INF = 1 << 22;

struct Input {
private:
  int nrq;
  int subtask_number;

public:
  Input(const char *str) {
    int only_k1 = 1;
    int small_diff = 1;
    int small_r = 1;
    int valid_input = 1;
    nrq = 0;

    FILE *fin = fopen(str, "r");
    
    fscanf(fin,"%d",&nrq);
    valid_input &= (1 <= nrq && nrq <= 1e6);
    
    for(int i = 0;i < nrq;i++){
        int k;
        long long l,r;
        fscanf(fin,"%d %lld %lld",&k,&l,&r);
        only_k1 &= (k == 1);
        small_diff &= (r - l + 1 <= 10);
        small_r &= (r <= 1e6);
        valid_input &= (1 <= k && k <= 20 && 0 <= l && r <= 1e18);
    }

    if(valid_input == 0 || small_diff + small_r + only_k1 > 1){
      handleError(GRADER_ERROR,-1);
    }
    if(only_k1 == 1){
        subtask_number = 1;
    }else if(small_diff == 1){
        subtask_number = 2;
    }else if(small_r == 1){
        subtask_number = 3;
    }else{
        subtask_number = 4;
    }
  }

  int getNrq() {
    return this->nrq;
  }
  
  int getSubtaskNumber(){
    return this->subtask_number;
  }
};

struct Output {
private:
  int *rez;
  FILE *fin;
  
public:
  Output(const char *str, int nrq,int subtask_number) {
    this->fin = fopen(str, "r");

    if(this->fin == NULL)
      handleError(NO_FILE,subtask_number);
    
    this->rez = new int[nrq];

    for(int i = 0; i < nrq; ++i) {
      if(fscanf(fin,"%d",&rez[i]) != 1){
        handleError(BAD_OUTPUT,subtask_number);
      }
    }
  }

  ~Output() {
    if(fin != NULL)
      fclose(fin);
    delete[] rez;
  }

  int getRez(int i) {
    return this->rez[i];
  }
};

int main() {
  Input *inp = new Input("xorfibo.in");
  Output *out = new Output("xorfibo.out", inp->getNrq(),inp->getSubtaskNumber()),
         *ok  = new Output("xorfibo.ok" , inp->getNrq(),inp->getSubtaskNumber());

  for(int i = 0; i < inp->getNrq(); ++i)
    if(out->getRez(i) != ok->getRez(i))
      handleError(INCORECT,inp->getSubtaskNumber());
  handleError(OK,inp->getSubtaskNumber());
  return 0;
}

