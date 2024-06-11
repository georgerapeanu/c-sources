/**
 * Author: Simon Lindholm
 * Date: 2015-05-12
 * License: CC0
 * Source: own work
 * Description:
 * Find the smallest i in $[a,b]$ that maximizes $f(i)$, assuming that $f(a) < \dots < f(i) \ge \dots \ge f(b)$.
 * To reverse which of the sides allows non-strict inequalities, change the < marked with (A) to <=, and reverse the loop at (B).
 * To minimize $f$, change it to >, also at (B).
 * Status: tested
 * Usage:
	int ind = TernarySearch(0,n-1,[\&](int i){return a[i];});
 * Time: O(\log(b-a))
 */
#pragma once

template<class Func>
int TernarySearch(int a, int b, Func f) {
	assert(a <= b);
	while (b - a >= 5) {
		int mid = (a + b) / 2;
		if (f(mid) < f(mid + 1)) a = mid; // (A)
		else b = mid + 1;
	}
  for (int i = a + 1; i <= b; ++i)
	  if (f(a) < f(i)) a = i; // (B)
	return a;
}
