#include <bits/stdc++.h>

const int MAX_N = 500;
const int MAX_M = 500;
const int MAX_NODES = MAX_N * MAX_M * 2;

std::string matr[MAX_N];
int line_node[MAX_N][MAX_M], col_node[MAX_N][MAX_M];

std::vector<int> graph[MAX_NODES];
int matched[MAX_NODES];
bool left_side[MAX_NODES];

int top, stiva[MAX_NODES];
bool vis[MAX_NODES];
bool critical_node[MAX_NODES];

char res_cell[] = "NSTB";

bool pair_up(int nod) {
    vis[nod] = true;
    stiva[top++] = nod;
    for(auto it: graph[nod])
        if(!vis[it] && matched[it] == -1) {
            matched[it] = nod;
            matched[nod] = it;
            return true;
        }
    for(auto it: graph[nod]) {
        if(matched[it] != -1 && !vis[matched[it]] && matched[it] != nod && pair_up(matched[it])) {
            matched[it] = nod;
            matched[nod] = it;
            return true;
        }
    }
    return false;
}

void undo_stack() {
    while(top > 0) {
        vis[stiva[top - 1]] = false;
        top--;
    }
}

int run_matching(int nodes) {
    int len = 0;
    bool found_matching;
    
    do {
        found_matching = false;
        for(int i = 0; i < nodes; ++i)
            if(left_side[i] && !vis[i] && matched[i] == -1) {
                bool res = pair_up(i);
                found_matching |= res;
                len += res;
            }

        undo_stack();
    } while(found_matching);
    return len;
}

int main() {
    int n, m;

    std::cin >> n >> m;

    assert(1 <= n && n <= MAX_N);
    assert(1 <= m && m <= MAX_M);

    int last_id = 0;

    for(int i = 0; i < n; ++i) {
        std::cin >> matr[i];
        
        assert(matr[i].size() == m);
        int current_line = -1;
        for(int j = 0; j < m; ++j) {
            assert(matr[i][j] == '.' || matr[i][j] == '#');

            if(matr[i][j] == '#')
                current_line = -1;
            else if(current_line == -1) {
                left_side[last_id] = true;
                matched[last_id] = -1;
                current_line = last_id++;
                line_node[i][j] = current_line;
            } else
                line_node[i][j] = current_line;
        }
    }

    for(int i = 0; i < m; ++i) {
        int current_col = -1;
        for(int j = 0; j < n; ++j) {
            if(matr[j][i] == '#')
                current_col = -1;
            else if(current_col == -1) {
                matched[last_id] = -1;
                current_col = last_id++;
                col_node[j][i] = current_col;
            } else
                col_node[j][i] = current_col;
        }
    }

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            if(matr[i][j] == '.') {
                graph[line_node[i][j]].push_back(col_node[i][j]);
                graph[col_node[i][j]].push_back(line_node[i][j]);
            }

    run_matching(last_id);
    for(int i = 0; i < last_id; ++i) {
        if(matched[i] != -1) {
            int other = matched[i];
            matched[i] = matched[other] = -1;
            
            vis[i] = true;
            stiva[top++] = i;
            if(!pair_up(other)) {
                critical_node[i] = true;
                // We couldn't expand the matching, so nothing was modified
                // so we have to 'repair' the matching
                matched[i] = other;
                matched[other] = i;
            } // we don't need to undo anything on the else-branch since
            // the new matching is going to be valid
            undo_stack();
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j)
            if(matr[i][j] == '#')
                printf("#");
            else {
                int mask = 0;
                if(critical_node[line_node[i][j]])
                    mask |= 1;
                if(critical_node[col_node[i][j]])
                    mask |= 2;
                fputc(res_cell[mask], stdout);
            }
        printf("\n");
    }

    return 0;
}

