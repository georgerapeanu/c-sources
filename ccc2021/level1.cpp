#include <bits/stdc++.h>

using namespace std;

class CodeInterpretor{
  vector<string> tokens;

public:

  CodeInterpretor(){
    tokens = vector<string>();
  }

  CodeInterpretor(string s){
    tokens = vector<string>();
    string curr = "";

    for(auto it:s){
      if(it != ' ' && it != '\t' && it != '\n'){
        curr += it;
      }else{
        tokens.push_back(curr);
        curr = "";
      }
    }
  }

  void append(string s){
    string curr = "";

    for(auto it:s){
      if(it != ' ' && it != '\t' && it != '\n'){
        curr += it;
      }else{
        if(curr != ""){
          tokens.push_back(curr);
        }
        curr = "";
      }
    }
    if(curr != ""){
      tokens.push_back(curr);
    }
  }

  void exec(){
    int instruction_pointer = 0;

    while(0 <= instruction_pointer && instruction_pointer < (int)tokens.size()){
      if(tokens[instruction_pointer] == "print"){
        instruction_pointer++;
        cout << tokens[instruction_pointer];
      }
      instruction_pointer++;
    }
  }
};

int main(){

    int n;
    string line_of_code;

    CodeInterpretor interpretor;
    

    cin >> n;
    while(cin >> line_of_code){
      interpretor.append(line_of_code);
    }

    interpretor.exec();

    return 0;
}
