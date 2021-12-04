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
  pair<string,string> rax;
  int rbp;
  int rip;
  Registers(){
    rax = make_pair("","");
    rbp = 0;
    rip = 0;
  }
};

class Stack{
  vector<int> stack;
  vector<bool> function_return;
  vector<queue<int>> postponed;
public:

  Stack(){
    stack = vector<int>();
    function_return = vector<bool>();
    postponed = vector<queue<int>>(0,queue<int>());
  }

  void push(int value){
    stack.push_back(value);
    function_return.push_back(false);
    postponed.push_back(queue<int>());
  }

  void push_function_return(int value){
    stack.push_back(value);
    function_return.push_back(true);
    postponed.push_back(queue<int>());
  }

  bool is_function_return(){
    return function_return.back();
  }

  void pop(){
    stack.pop_back();
    function_return.pop_back();
    postponed.pop_back();
  }

  int top(){
    return stack.back();
  }

  bool empty(){
    return stack.empty();
  }

  void add_to_postponed(int value){
    postponed.back().push(value);
  }

  bool has_postponed(){
    return postponed.back().empty() == false;
  }

  int get_first_postponed(){
    return postponed.back().front();
  }

  void pop_first_postponed(){
    postponed.back().pop();
  }

  int size(){
    return stack.size();
  }
};


class CodeInterpretor{
  vector<string> tokens;
  vector<int> function_addresses;
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
    function_addresses = vector<int>();
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
      if(opcode == "end" || opcode == "endp" || opcode == "end_call"){
        scope_level--;
        if(scope_level == 0){
          return rip;
        }
      }else if(opcode == "postpone" || opcode == "start" || opcode == "if" || opcode == "else" || opcode == "call"){
        scope_level++;
      }
      rip++;
    }
    assert(false);
    return -1;
  }

  void return_scope(){
    if(stack.is_function_return()){
      registers.rax = container.get("true").first;  
    }
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

  void return_to_root_function(){
    while(stack.size() > 1){
      stack.pop();
    }
    registers.rip = stack.top();
    stack.pop();
  }

  void extract_functions(){
    function_addresses.clear();
    function_addresses.push_back(0);
    function_addresses.push_back(0);
    while(true){
      int nxt = find_corresponding_end(function_addresses.back()) + 1;
      if(nxt >= (int)tokens.size()){
        break;
      }
      function_addresses.push_back(nxt);
    }
  }

  void preprocess_calls(){
    vector<string> new_tokens;

    int cnt_call = 0;

    for(auto it:tokens){
      if(it == "call"){
        cnt_call++;
      }else{
        while(cnt_call--){
          new_tokens.push_back("end_call");
        }
      }
      new_tokens.push_back(it);
    }
    tokens = new_tokens;
  }

  string exec(){
    extract_functions();
    preprocess_calls();
    container = ValueContainer();
    registers = Registers();
    stack = Stack();
    string result = "";
    string curr = "";

    while(0 <= registers.rip && registers.rip < (int)tokens.size()){
      //debugStuff[tokens[registers.rip]] = true;
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
        if(stack.has_postponed()){
          int tmp = stack.get_first_postponed();
          stack.pop_first_postponed();
          registers.rip = tmp;
        }else{
          return_scope();
        }
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
          return_to_root_function();
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
        
        if(tmp.second == false){
          curr = "ERROR"; 
          return_function();
          goto done_interpretation;
        }
        registers.rax = tmp.first;
        return_function();
      }else if(tokens[registers.rip] == "var"){
        if(container.create(tokens[registers.rip + 1],tokens[registers.rip + 2]) == false){
          curr = "ERROR";
          return_to_root_function();
          goto done_interpretation;
        }
        registers.rip += 3;
      }else if(tokens[registers.rip] == "set"){
        if(container.set(tokens[registers.rip + 1],tokens[registers.rip + 2]) == false){
          curr = "ERROR";
          return_to_root_function();
          goto done_interpretation;
        }
        registers.rip += 3;
      }else if(tokens[registers.rip] == "postpone"){
        stack.add_to_postponed(registers.rip + 1);
        registers.rip = find_corresponding_end(registers.rip) + 1;  
      }else if(tokens[registers.rip] == "call"){
        stack.push_function_return(find_corresponding_end(registers.rip));
        registers.rip++; 
      }else if(tokens[registers.rip] == "end_call"){
        if(registers.rax.first != "integer" || registers.rax.second.empty() || registers.rax.second[0] == '-'){
          curr = "ERROR";
          return_to_root_function();
          goto done_interpretation;
        }
        int idx = 0;
        for(auto it:registers.rax.second){
          idx = 10 * idx + it - '0';

        }
        if(idx < 0 || idx >= (int)function_addresses.size()){
          curr = "ERROR";
          return_to_root_function();
          goto done_interpretation;
        }
        registers.rip = function_addresses[idx];
        
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
