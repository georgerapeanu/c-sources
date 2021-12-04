#include <bits/stdc++.h>

using namespace std;

class CodeInterpretor{
  vector<string> tokens;
  vector<int> stack;
  
  string rax;
  int rbp;

public:

  CodeInterpretor(){
    tokens = vector<string>();
  }

  CodeInterpretor(string s){
    tokens = vector<string>();
    stack = vector<int>();
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

  int find_corresponding_end(int instruction_pointer){
    int scope_level = 0;
    while(instruction_pointer < (int)tokens.size()){
      string opcode = tokens[instruction_pointer];
      if(opcode == "end"){
        scope_level--;
        if(scope_level == 0){
          return instruction_pointer;
        }
      }else if(opcode == "start" || opcode == "if" || opcode == "else"){
        scope_level++;
      }
      instruction_pointer++;
    }
    return -1;
  }

  void exec(){
    rbp = 0;
    int instruction_pointer = 0;

    while(0 <= instruction_pointer && instruction_pointer < (int)tokens.size()){
      if(tokens[instruction_pointer] == "print"){
        instruction_pointer++;
        cout << tokens[instruction_pointer];
        instruction_pointer++;
      }else if(tokens[instruction_pointer] == "end"){
        instruction_pointer = stack.back();
        stack.pop_back();
      }else if(tokens[instruction_pointer] == "start"){
        int return_address = find_corresponding_end(instruction_pointer) + 1;
        stack.push_back(return_address);
        instruction_pointer++;
      }else if(tokens[instruction_pointer] == "if"){
        int else_address = find_corresponding_end(instruction_pointer) + 1;
        int after_if_address = find_corresponding_end(else_address) + 1;
        assert(else_address != -1);
        assert(after_if_address != -1);

        instruction_pointer++;

        if(tokens[instruction_pointer] == "true"){
          instruction_pointer++;
        }else{
          instruction_pointer = else_address + 1;
        }
        stack.push_back(after_if_address);

      }else if(tokens[instruction_pointer] == "return"){
        rax = tokens[instruction_pointer + 1];
        while((int)stack.size() != rbp + 1){
          stack.pop_back();
        }
        instruction_pointer = stack.back();
        stack.pop_back();
      }else{
        instruction_pointer++;
      }
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
