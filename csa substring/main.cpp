#include <bits/stdc++.h>

using namespace std;
int longestParenthesisedSubstring(const string& S) {
    stack<int> st;
    int maxim=0;
    unordered_map <char,char> M;
    M[')']='(';
    M['(']='0';
    int N=S.size();
    st.push(-1);
    for(int i=0;i<N;i++)
    {
        if(st.size()==1||M[S[i]]!=S[st.top()])
        {
            st.push(i);
            continue;
        }
        st.pop();
        maxim=max(maxim,i-st.top());
    }
    if(maxim)
        return maxim;
    return -1;
}

int main() {
    string S;
    cin >> S;
    cout << longestParenthesisedSubstring(S) << "\n";
    return 0;
}
