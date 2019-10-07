#include <cstdio>
#include <cstdlib>
#include <set>
#include <algorithm>

using namespace std;

#define NMAX 10000
#define MMAX 20000
#define MOVEMAX 20000

void Joi(int N, int M, int A[], int B[], long long X, int T);
long long Ioi(int N, int M, int A[], int B[], int P, int V, int T);

static int N, M, A[MMAX], B[MMAX], P, T;
static long long X;
static int given_msg[NMAX];
static int pos, n_move;
static set<pair<int, int> > edges;

void WrongAnswer(int e)
{
	printf("Wrong Answer[%d]\n", e);
	exit(1);
}

void MessageBoard(int attr, int msg)
{
	if (!(0 <= attr && attr <= N - 1)) {
		WrongAnswer(1);
	}
	if (given_msg[attr] != -1) {
		WrongAnswer(2);
	}
	if (!(msg == 0 || msg == 1)) {
		WrongAnswer(3);
	}
	given_msg[attr] = msg;
}

int Move(int dest)
{
	if (!(0 <= dest && dest <= N - 1)) {
		WrongAnswer(6);
	}
	if (!edges.count({ pos, dest })) {
		WrongAnswer(7);
	}
	++n_move;
	if (n_move > MOVEMAX) {
		WrongAnswer(8);
	}
	pos = dest;
	return given_msg[pos];
}

int main(void)
{
	int i;
	long long max_code;

	scanf("%d%d%lld%d%d", &N, &M, &X, &P, &T);
	for (int i = 0; i < M; ++i) {
		scanf("%d%d", &(A[i]), &(B[i]));
		edges.insert({ A[i], B[i] });
		edges.insert({ B[i], A[i] });
	}
	for (int i = 0; i < N; ++i) {
		given_msg[i] = -1;
	}

	Joi(N, M, A, B, X, T);

	for (i = 0; i < N; ++i) {
		if (given_msg[i] == -1) {
			WrongAnswer(4);
		}
	}
	
	n_move = 0;
	pos = P;
	long long answer = Ioi(N, M, A, B, P, given_msg[P], T);

	if (answer != X) {
		WrongAnswer(5);
	}

	printf("Accepted : #move=%d\n", n_move);
	return 0;
}
