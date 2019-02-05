#ifndef INTERACTION_IMLP
#define INTERACTION_IMLP

#include "icc.h"

#include <cstdio>
#include <cmath>

#include <array>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define DEBUG(...) if (0) { __VA_ARGS__; }

namespace ceoi_2016 {
const bool PRINT_SCORE_TO_STDERR = false;

void Fail(const string&);

// If condition is not true, sets score to 0 because reasons.
void Expect(bool condition, const string& message) {
    if (not condition) {
        Fail(message);
    }
};

class Solver {
public:
    // query provided by the problem
    virtual bool Query(int n, int m, int* a, int* b) = 0;

    // checks whatever or not that is the edge. order does not matter.
    // does not crash if it's false. just returnes true.
    virtual bool SetEdge(int a, int b) = 0;

    // returns true if threre're no more edges left to add.
    virtual bool IsOver() = 0;

    virtual int NumVertices() = 0;
};

struct BasicSolver : public Solver {
    BasicSolver(istream& fin) {
        fin >> n;
        edges_order.resize(n - 1);
        for (int i = 0; i < n; i += 1) {
            fin >> edges_order[i].first >> edges_order[i].second;
        }

        current_edge = 0;
    }

    bool Query(int a, int b, int* A, int *B);

    bool SetEdge(int a, int b);

    bool IsOver() {
        return current_edge == n - 1;
    }

    int NumVertices() {
        return n;
    }

private:
    vector<pair<int, int> > edges_order;
    int n, current_edge;
};

bool BasicSolver::Query(int a, int b, int A[], int B[]) {
    DEBUG({
        fprintf(stderr, "[Query]\n{");
        for (int i = 0; i < a; i += 1) {
            fprintf(stderr, "%d%s", A[i], ((i + 1 != a) ? (",\t") : ("")));
        }
        fprintf(stderr, "}\n{");
        for (int i = 0; i < b; i += 1) {
            fprintf(stderr, "%d%s", B[i], ((i + 1 != b) ? (",\t") : ("")));
        }
        fprintf(stderr, "}\n\n");
    });

    vector<int> left(n + 1, 0), right(n + 1, 0);

    for (int i = 0; i < a; i += 1) {
        // sanity check
        Expect(1 <= A[i] and A[i] <= n, "Query cities not in range [1, n]");

        left[A[i]] = 1;
    }

    for (int i = 0; i < b; i += 1) {
        // sanity check
        Expect(1 <= B[i] and B[i] <= n, "Query cities not in range [1, n]");

        right[B[i]] = 2;

        Expect(left[B[i]] == 0, "The query sets must be disjoint");
    }

    bool ok = false;
    for (int i = 0; i <= current_edge; i += 1) {
        ok |= (left[edges_order[i].first] + right[edges_order[i].second] == 3);
        ok |= (left[edges_order[i].second] + right[edges_order[i].first] == 3);
    }

    return ok;
}

bool BasicSolver::SetEdge(int a, int b) {
    int x = edges_order[current_edge].first;
    int y = edges_order[current_edge].second;

    if (x > y) {
        swap(x, y);
    }

    if (a > b) {
        swap(a, b);
    }

    DEBUG({
        fprintf(stderr, "[SetRoad]\nGiven Road\t%d\t%d\nActual Road\t%d\t%d\n\n\n\n", a, b, x, y);
    });

    if ((a == x and b == y) or (a == y and b == x)) {
        current_edge += 1;
        return true;
    } else {
        current_edge += 1;
        cout << "ai belit muchia " << a << " " << b << "\n";
        return false;
    }
}

// **********************************************************************************************************************************
//
//   Interactive Solver
//
// **********************************************************************************************************************************

static const int kMaxN = 101;
typedef array<array<int, kMaxN>, kMaxN> IntArr;

struct AdjacencyMatrixInformation {
    int num_ctc_pairs;
    int num_edges;
    int max_edges_2_ctcs;

    AdjacencyMatrixInformation()
        : num_ctc_pairs(0), num_edges(0), max_edges_2_ctcs(0) { }
};

AdjacencyMatrixInformation GetAMInformation(const IntArr& valid_edge, const vector<int>& component) {
    IntArr component_count;
    AdjacencyMatrixInformation result;

    int n = kMaxN - 1;

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            component_count[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            if (valid_edge[i][j] == 1) {
                component_count[component[i]][component[j]] += 1;
            }
        }
    }

    for (int i = 1; i <= n; i += 1) {
        for (int j = i + 1; j <= n; j += 1) {
            if (component_count[i][j] != 0) {
                result.num_ctc_pairs += 1;
                result.max_edges_2_ctcs = max(result.max_edges_2_ctcs, component_count[i][j]);
                result.num_edges += component_count[i][j];
            }
        }
    }

    return result;
}

struct BasicInteractiveSolver : public Solver {
    double full_num_edges, log_num_edges;
    double full_max_edges_2_ctc, log_max_edges_2_ctc;
    double full_num_ctc_pairs, log_num_ctc_pairs;
    double max_rand;

    double false_coef, true_coef;

    // constructor from istream from file
    BasicInteractiveSolver(istream& fin) : step(0) {
        fin >> n;

        fin >> full_num_edges;
        fin >> log_num_edges;
        fin >> full_max_edges_2_ctc;
        fin >> log_max_edges_2_ctc;
        fin >> full_num_ctc_pairs;
        fin >> log_num_ctc_pairs;
        fin >> max_rand;

        fin >> false_coef >> true_coef;

        component.resize(n + 1);
        for (int i = 0; i <= n; i += 1) {
            component[i] = i;
        }

        ResetValidEdges();
    }

    // api
    virtual bool Query(int a, int b, int* A, int* B);
    virtual bool SetEdge(int a, int b);

    // interaction
    bool IsOver() {
        return step == n - 1;
    }
    int NumVertices() {
        return n;
    }

    // checks whenever of not the query is true by the selected edges up to this point
    bool IsAlreadyGood(int a, int b, int* A, int *B);

    // based on a query, returns the adjency matrix for both answers
    pair<IntArr, IntArr> GetIncludedExcluded(int a, int b, int* A, int *B);

    // to next edge
    void ResetValidEdges();
    void UniteVertices(int a, int b);

    // given a adjency matrix estimates the required time to finish
    virtual int MaxScoreFromAMInfo(AdjacencyMatrixInformation);

    // step - num of selected edges up to this point, n - num of vertices
    int step, n;
    vector<pair<int, int> > selected_edges;

    // in which component is the node X
    vector<int> component;
    IntArr valid_edge;

public:

    // DEBUG ONLY
    void Print(const IntArr& arr) {
        fprintf(stderr, "~~~~~~|||~~~~~~\n");
        for (int i = 1; i <= n; i += 1) {
            for (int j = 1; j <= n; j += 1) {
                fprintf(stderr, "%d ", arr[i][j]);
            }
            fprintf(stderr, "\n");
        }
    }

};

// **********************************************************************************************************************************
//
//   Good overall things
//
// **********************************************************************************************************************************

// Checks if the API query is already ok. Else, we should chose if it's true or not
bool BasicInteractiveSolver::IsAlreadyGood(int a, int b, int* A, int *B) {
    DEBUG({
        fprintf(stderr, "[Query]\n{");
        for (int i = 0; i < a; i += 1) {
            fprintf(stderr, "%d%s", A[i], ((i + 1 != a) ? (",\t") : ("")));
        }
        fprintf(stderr, "}\n{");
        for (int i = 0; i < b; i += 1) {
            fprintf(stderr, "%d%s", B[i], ((i + 1 != b) ? (",\t") : ("")));
        }
        fprintf(stderr, "}\n\n");
    });

    vector<int> left(n + 1, 0), right(n + 1, 0);

    for (int i = 0; i < a; i += 1) {
        // sanity check
        Expect(1 <= A[i] and A[i] <= n, "Query cities not in range [1, n]");

        left[A[i]] = 1;
    }

    for (int i = 0; i < b; i += 1) {
        // sanity check
        Expect(1 <= B[i] and B[i] <= n, "Query cities not in range [1, n]");

        right[B[i]] = 2;

        Expect(left[B[i]] == 0, "The query sets must be disjoint");
    }

    bool ok = false;
    for (int i = 0; i < step; i += 1) {
        ok |= (left[selected_edges[i].first] + right[selected_edges[i].second] == 3);
        ok |= (left[selected_edges[i].second] + right[selected_edges[i].first] == 3);
    }

    return ok;
}

// method exposed throw API
bool BasicInteractiveSolver::SetEdge(int a, int b) {
    pair<int, int> answer;
    int count = 0;
    for (int i = 1; i <= n; i += 1) {
        for (int j = i + 1; j <= n; j += 1) {
            if (valid_edge[i][j] != 0) {
                count += 1;
                answer = {i, j};
            }
        }
    }

    if (count == 0) {
        Fail("Bug in interaction! Err #1");
    }

    if (count != 1) {
        return false;
    }

    if (answer == make_pair(a, b) or answer == make_pair(b, a)) {
        UniteVertices(a, b);
        ResetValidEdges();
        step += 1;
        return true;
    } else {
        return false;
    }
}

void BasicInteractiveSolver::UniteVertices(int a, int b) {
    a = component[a];
    b = component[b];

    for (auto& itr : component) {
        if (itr == a) {
            itr = b;
        }
    }

    selected_edges.push_back({a, b});
}

// Just guessed a edge. Need to reset all meta-data
void BasicInteractiveSolver::ResetValidEdges() {
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            valid_edge[i][j] = (component[i] != component[j]);
        }
    }
}

// exclude all edges from the query or include only them :)
pair<IntArr, IntArr> BasicInteractiveSolver::GetIncludedExcluded(int a, int b, int* A, int *B) {
    IntArr exclude = valid_edge; // answer false -> all current edges in the query are invalid
    IntArr include = valid_edge; // include only the query edges. the others are invalid -> answer = true

    for (int i = 0; i < a; i += 1) {
        for (int j = 0; j < b; j += 1) {
            exclude[A[i]][B[j]] = false;
            exclude[B[j]][A[i]] = false;
        }
    }

    for (int i = 0; i < a; i += 1) {
        for (int j = 0; j < b ; j += 1) {
            if (include[A[i]][B[j]] == 1) {
                include[A[i]][B[j]] = 2;
                include[B[j]][A[i]] = 2;
            }
        }
    }

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            if (include[i][j] == 1) {
                include[i][j] = 0;
            } else if (include[i][j] == 2) {
                include[i][j] = 1;
            }
        }
    }

    return {include, exclude};
}

// **********************************************************************************************************************************
//
//   Default Query
//
// **********************************************************************************************************************************

bool BasicInteractiveSolver::Query(int a, int b, int* A, int *B) {
    if (IsAlreadyGood(a, b, A, B)) {
        return true;
    }

    if (a == 0 or b == 0) {
        return false;
    }

    auto incexc = GetIncludedExcluded(a, b, A, B);

    auto& include = incexc.first;
    auto& exclude = incexc.second;

    auto inf_inc = GetAMInformation(include, component);
    auto inf_exc = GetAMInformation(exclude, component);

    double inc = true_coef * MaxScoreFromAMInfo(inf_inc);
    double exc = false_coef * MaxScoreFromAMInfo(inf_exc);

    Expect(!(exc < -1 and inc < -1), "Bug in interaction! Err #2");

    if (exc < inc) {
        valid_edge = include;
        return true;
    } else {
        valid_edge = exclude;
        return false;
    }
}

// **********************************************************************************************************************************
//
//   Default Cost Estimator
//
// **********************************************************************************************************************************

int BasicInteractiveSolver::MaxScoreFromAMInfo(AdjacencyMatrixInformation am_info) {
    if (am_info.num_edges == 0) {
        return -2.0;
    }

    return 1.0 * full_num_edges * am_info.num_edges +
           1.0 * log_num_edges * log2(am_info.num_edges) +
           1.0 * full_max_edges_2_ctc * am_info.max_edges_2_ctcs +
           1.0 * log_max_edges_2_ctc * log2(am_info.max_edges_2_ctcs) +
           1.0 * full_num_ctc_pairs * am_info.num_ctc_pairs +
           1.0 * log_num_ctc_pairs * log2(am_info.num_ctc_pairs) +
           1.0 * max_rand * (1.0 * rand() / RAND_MAX);
}

// **********************************************************************************************************************************
//
//   User Interaction
//
// **********************************************************************************************************************************

class Interaction {
public:
    bool Query(int n, int m, int* a, int *b);
    void SetEdge(int a, int b);

    Interaction(Solver* solver, int max_steps, int max_score)
        : num_steps(0), solver(solver), max_steps(max_steps), max_score(max_score) { }
    void Fail(const string&);

    int NumVertices() {
        return solver->NumVertices();
    }

private:
    void SetScore(int score, const string& message);

    void DecideScore();

    int num_steps;
    Solver* solver;

    int max_steps, max_score;
};

Interaction* interaction;

void Interaction::SetScore(int score, const string& message) {
    Expect(0 <= score and score <= 10, "Error in interaction, invalid score");

    if (PRINT_SCORE_TO_STDERR) {
        fprintf(stderr, "%d %s\n", score, message.c_str());
    }

    ofstream fout("icc.out");
    fout << score << ' ';
    fout << message << '\n';
    fout.close();

    exit(0);
};

// returnes score by the grader based on the number of
void Interaction::DecideScore() {
    if (num_steps <= max_steps) {
        SetScore(max_score, "Ok! " + to_string(num_steps) + " queries used.");
    } else {
        SetScore(0, "Too many queries! " + to_string(num_steps) + " out of " + to_string(max_steps));
    }
}

bool Interaction::Query(int n, int m, int* a, int *b) {
    num_steps += 1;
    Expect(num_steps <= 2 * max_steps, "Number of queries more than " + to_string(2 * max_steps) + " out of " + to_string(max_steps));

    return solver->Query(n, m, a, b);
}

void Interaction::SetEdge(int a, int b) {
    Expect(solver->SetEdge(a, b), "Wrong road!");
    if (solver->IsOver()) {
        DecideScore();
    }
}

// Called by various methods because reasons.
void Fail(const string& message) {
    interaction->Fail(message);
}

void Interaction::Fail(const string& message) {
    SetScore(0, message);
}
} // namespace ceoi_2016


// **********************************************************************************************************************************
//
//   Main
//
// **********************************************************************************************************************************

extern "C" {
// Implementation of API's SetRoad(int, int)
    void setRoad(int a, int b) {
        using namespace ceoi_2016;
        interaction->SetEdge(a, b);
    }

// Implementation of API's Query(int, int, int*, int*)
    int query(int n, int m, int* a, int* b) {
        using namespace ceoi_2016;
        return interaction->Query(n, m, a, b);
    }


    void InitGrader() {
        using namespace ceoi_2016;
        /*
        * fin should have
        * - solver type
        *   max_steps
        *   points if ok
        */
        ofstream fout("icc.out");
        fout << "0 illegal exit!\n";
        fout.close();

        ifstream fin("icc.in");
        int solver_type;
        fin >> solver_type;
        int max_steps, max_points;
        fin >> max_steps >> max_points;
        Solver* solver;

        if (solver_type == 0) {
            /*
            * fin should have
            * n
            * n - 1 edges
            */
            solver = new BasicSolver(fin);
        } else if (solver_type == 1) {
            /*
            * fin should have n
            *    full_num_edges
            *    log_num_edges

            *    full_max_edges_2_ctc
            *    log_max_edges_2_ctc

            *    full_num_ctc_pairs
            *    log_num_ctc_pairs
            *    max_rand
            *
            *    false_coef
            *    true_coef
            */
            solver = new BasicInteractiveSolver(fin);
        } else {
            Fail("Bug in interaction! Err #3");
            solver = nullptr;
        }

        interaction = new Interaction(solver, max_steps, max_points);
    }

    void GraderExitFail() {
        using namespace ceoi_2016;
        Fail("Not all edges were guessed!");
    }

    int NumVertices() {
        using namespace ceoi_2016;
        return interaction->NumVertices();
    }
}
#endif
