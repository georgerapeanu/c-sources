#include <bits/stdc++.h>

using namespace std;

class ValueContainer{
  map<string,pair<string,string>> mp; ///each variable points to a type and a value

  public:

  ValueContainer(){
    mp = map<string,pair<string,string> >();
    mp["true"] = {"boolean","true"};
    mp["false"] = {"boolean","false"};
  }

  bool exists(string variable_name){
    return mp.count(variable_name) > 0; 
  }

  bool create(string variable_name,string value){
    if(exists(variable_name)){
      return false;
    }
    if(exists(value)){
      mp[variable_name] = mp[value];
    }else{
      bool only_digits = true;
      int idx = 0;
      if(value[idx] == '-'){
        idx++;
      }
      while(idx < (int)value.size()){
        if(value[idx] < '0' || value[idx] > '9'){
          only_digits = false;
          break;
        }
        idx++;
      }
      if(only_digits){
        mp[variable_name] = {"integer",value};
      }else{
        mp[variable_name] = {"string",value};
      }
    }
    return true;
  }

  bool set(string variable_name,string value){
    if(exists(variable_name) == false){
      return false;
    }
    if(exists(value)){
      mp[variable_name] = mp[value];
    }else{
      bool only_digits = true;
      int idx = 0;
      if(value[idx] == '-'){
        idx++;
      }
      while(idx < (int)value.size()){
        if(value[idx] < '0' || value[idx] > '9'){
          only_digits = false;
          break;
        }
        idx++;
      }
      if(only_digits){
        mp[variable_name] = {"integer",value};
      }else{
        mp[variable_name] = {"string",value};
      }
    }
    return true;
  }

  pair<pair<string,string>,bool> get(string variable_name){
    if(exists(variable_name) == false){
      return make_pair(make_pair("",""),false);
    }
    return make_pair(mp[variable_name],true);
  }
};

struct Registers{
  int rax;
  int rbp;
  int rip;
  Registers(){
    rax = 0;
    rbp = 0;
    rip = 0;
  }
};

class Stack{
  vector<int> stack;
  vector<bool> function_return;

public:

  Stack(){
    stack = vector<int>();
    function_return = vector<bool>();
  }

  void push(int value){
    stack.push_back(value);
    function_return.push_back(false);
  }

  void push_function_return(int value){
    stack.push_back(value);
    function_return.push_back(true);
  }

  bool is_function_return(){
    return function_return.back();
  }

  void pop(){
    stack.pop_back();
    function_return.pop_back();
  }

  int top(){
    return stack.back();
  }

  bool empty(){
    return stack.empty();
  }
};


class CodeInterpretor{
  vector<string> tokens;
  ValueContainer container;
  Stack stack;

  //map<string,bool> debugStuff;

  Registers registers;

public:

  CodeInterpretor(){
    tokens = vector<string>();
    container = ValueContainer();
    registers = Registers();
    stack = Stack();
  }

  CodeInterpretor(string s){
    tokens = vector<string>();
    stack = Stack();
    registers = Registers();
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

  int find_corresponding_end(int rip){
    int scope_level = 0;
    while(rip < (int)tokens.size()){
      string opcode = tokens[rip];
      if(opcode == "end"){
        scope_level--;
        if(scope_level == 0){
          return rip;
        }
      }else if(opcode == "start" || opcode == "if" || opcode == "else"){
        scope_level++;
      }
      rip++;
    }
    assert(false);
    return -1;
  }

  void return_scope(){
    registers.rip = stack.top();
    stack.pop();
  }

  void return_function(){
    while(stack.is_function_return() == false){
      stack.pop();
    }
    registers.rip = stack.top();
    stack.pop();
  }

  string exec(){
    container = ValueContainer();
    registers = Registers();
    stack = Stack();
    string result = "";
    string curr = "";

    while(0 <= registers.rip && registers.rip < (int)tokens.size()){
    //  debugStuff[tokens[registers.rip]] = true;
      if(tokens[registers.rip] == "print"){
        registers.rip++;
        if(container.exists(tokens[registers.rip])){
          pair<string,string> tmp = container.get(tokens[registers.rip]).first;
          curr += tmp.second;
        }else{
          curr += tokens[registers.rip];
        }
        registers.rip++;
      }else if(tokens[registers.rip] == "end"){
        return_scope();
      }else if(tokens[registers.rip] == "start"){
        int return_address = find_corresponding_end(registers.rip) + 1;
        stack.push_function_return(return_address);
        registers.rip++;
      }else if(tokens[registers.rip] == "if"){
        int else_address = find_corresponding_end(registers.rip) + 1;
        int after_if_address = find_corresponding_end(else_address) + 1;

        registers.rip++;

        pair<pair<string,string>,bool> tmp = container.get(tokens[registers.rip]);

        if(tmp.second == false || tmp.first.first != "boolean"){
          curr = "ERROR"; 
          return_function();
          goto done_interpretation;
        }
        if(tmp.first.second == "true"){
          registers.rip++;
        }else{
          registers.rip = else_address + 1;
        }
        stack.push(after_if_address);

      }else if(tokens[registers.rip] == "return"){
        registers.rip++;
        pair<pair<string,string>,bool> tmp = container.get(tokens[registers.rip]);
        
        /*if(tmp.second == false){
          curr = "ERROR"; 
          return_function();
          goto done_interpretation;
        }*/
        // rax = tmp.first.second;
        ///TODO add the actual return
        return_function();
      }else if(tokens[registers.rip] == "var"){
        if(container.create(tokens[registers.rip + 1],tokens[registers.rip + 2]) == false){
          curr = "ERROR";
          return_function();
          goto done_interpretation;
        }
        registers.rip += 3;
      }else if(tokens[registers.rip] == "set"){
        if(container.set(tokens[registers.rip + 1],tokens[registers.rip + 2]) == false){
          curr = "ERROR";
          return_function();
          goto done_interpretation;
        }
        registers.rip += 3;
      }else{
        registers.rip++;
      }
      done_interpretation:;
      if(stack.empty()){
        result += curr + "\n";
        curr = "";
        container = ValueContainer();
        //registers = Registers();
      }
    }
    //for(auto it:debugStuff)cerr << it.first << "\n";
    return result;
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

    cout << interpretor.exec();

    return 0;
}
