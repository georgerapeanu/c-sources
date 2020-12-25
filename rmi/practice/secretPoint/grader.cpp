#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "secret_point.h"

const int MAX_QUERIES = 1000;
const int MIN_XY = -10000;
const int MAX_XY = +10000;

int queries;
double secret_x, secret_y;

void score_and_exit(const double pts, const char *verdict) {
  printf("Verdict: %s\n", verdict);
  printf("Score: %f\n", pts);
  exit(0);
}

void too_many_queries() {
  score_and_exit(0, "Too many queries!");
}

void bounds_exceeded() {
  score_and_exit(0, "Exceeded bounds of the queried point!");
}

void wrong_answer() {
  score_and_exit(0, "Wrong answer!");
}

void correct_answer(int queries) {
  char message[101];
  sprintf(message, "OK! You used %d queries.", queries);
  score_and_exit(1, message);
}


double get_distance(double query_x, double query_y) {
  if (!(MIN_XY <= query_x && query_x <= MAX_XY
      && MIN_XY <= query_y && query_y <= MAX_XY)) {
    bounds_exceeded();
  }
  queries++;
  if (queries > MAX_QUERIES) {
    too_many_queries();
  }
  return sqrt(fabs((query_x - secret_x) * (query_x - secret_x)
                 + (query_y - secret_y) * (query_y - secret_y)));
}

void the_secret_point_is(double guess_x, double guess_y) {
  double dist = sqrt(fabs((guess_x - secret_x) * (guess_x - secret_x)
                        + (guess_y - secret_y) * (guess_y - secret_y)));
  if (dist <= 1e-6) {
    correct_answer(queries);
  } else {
    wrong_answer();
  }
}

int main(int argc, char **argv) {
  queries = 0;

  assert(scanf("%lf%lf", &secret_x, &secret_y) == 2);
  find_secret_point();

  return 0;
}
