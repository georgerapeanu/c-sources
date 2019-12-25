#include <bits/stdc++.h>

using namespace std;

FILE *code = fopen("code","r");

int get_int(char *argv) {
    int ans = 0;
    int ind = 0;
    while(argv[ind] >= '0' && argv[ind] <= '9') {
        ans = ans * 10 + (argv[ind] - '0');
        ind++;
    }
    return ans;
}

string my_to_string(int a) {
    bool sgn = false;
    if(a == 0) {
        return "0";
    }
    else if(a < 0) {
        sgn = 1;
        a *= -1;
    }
    string ans = "";

    while(a) {
        ans = char('0' + (a % 10)) + ans;
        a /= 10;
    }
    if(sgn) {
        ans = "-" + ans;
    }
    return ans;
}

int my_to_int(string s) {
    int ans = 0;
    int sgn = 1;
    int ind = 0;
    if(s[0] == '-') {
        sgn = -1;
        ind = 1;
    }
    while(ind < (int)s.size() && s[ind] >= '0' && s[ind] <= '9') {
        ans = ans * 10 + (s[ind] - '0');
        ind++;
    }
    return sgn * ans;
}

class IntcodeComputer {
protected:
    int start;
    int n;
    bool halted;
    deque<int> inputs;
    vector<int> v;

public:

    bool is_halted() {
        return halted;
    }

    IntcodeComputer(const deque<int> &inputs,const vector<int> &code) {
        this->n = code.size();
        this->inputs = inputs;
        this->v = code;
        this->start = 0;
        this->halted = false;
    }

    void replace_inputs(const deque<int> &inputs) {
        this->inputs = inputs;
    }

    virtual string run() {
        string ans;
        while(start <= n) {
            int mode = v[start] % 100;
            int val = v[start] / 100;
            start++;

            if(mode == 99) {
                this->halted = true;
                return ans;
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
                v[a] = inputs.front();
                inputs.pop_front();
            }
            else if(mode == 4) {
                int a = (val % 10 == 0 ? v[v[start]]:v[start]);
                val /= 10;
                start++;
                ans += my_to_string(a);
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
    }
};

class Amplifier:public IntcodeComputer {
public:
    Amplifier(const deque<int> &inputs,const vector<int> &code):IntcodeComputer(inputs,code) {}

    virtual string run() {
        string ans = "";
        while(start <= n) {
            int mode = v[start] % 100;
            int val = v[start] / 100;
            start++;

            if(mode == 99) {
                this->halted = true;
                return ans;
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
                v[a] = inputs.front();
                inputs.pop_front();
            }
            else if(mode == 4) {
                int a = (val % 10 == 0 ? v[v[start]]:v[start]);
                val /= 10;
                start++;
                ans += my_to_string(a);
                return ans;
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
    }
};

vector<int> code_v;

int solve(const vector<int> &perm) {
    Amplifier a({perm[0],0},code_v);
    Amplifier b({perm[1],my_to_int(a.run())},code_v);
    Amplifier c({perm[2],my_to_int(b.run())},code_v);
    Amplifier d({perm[3],my_to_int(c.run())},code_v);
    Amplifier e({perm[4],my_to_int(d.run())},code_v);
    int power = my_to_int(e.run());

    while(e.is_halted() == false) {
        a.replace_inputs({power});
        b.replace_inputs({my_to_int(a.run())});
        c.replace_inputs({my_to_int(b.run())});
        d.replace_inputs({my_to_int(c.run())});
        e.replace_inputs({my_to_int(d.run())});
        string tmp = e.run();
        if(e.is_halted() == false) {
            power = my_to_int(tmp);
        }
    }

    return power;
}

int main(int argc,char **argv) {

    int val = 0;

    while(fscanf(code,"%d,",&val) == 1) {
        code_v.push_back(val);
    }

    vector<int> v = {5,6,7,8,9};

    int ans = -1e9;

    do {
        ans = max(ans,solve(v));
    } while(next_permutation(v.begin(),v.end()));

    fprintf(stdout,"%d\n",ans);

///   fprintf(out,"%d\n",v[0]);

    fclose(code);

    return 0;
}
