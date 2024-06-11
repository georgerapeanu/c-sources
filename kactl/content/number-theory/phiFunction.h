/**
 * Author: Håkan Terelius
 * Date: 2009-09-25
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Euler's_totient_function
 * Description: \emph{Euler's totient} or \emph{Euler's phi} function is defined as $\phi(n):=\#$ of positive integers $\leq n$ that are coprime with $n$. The \emph{cototient} is $n-\phi(n)$.
 * $\phi(1)=1$, $p$ prime $\Rightarrow \phi(p^k)=(p-1)p^{k-1}$, $m,n$ coprime $\Rightarrow \phi(mn)=\phi(m)\phi(n)$.
 * If $n=p_1^{k_1}p_2^{k_2} ... p_r^{k_r}$ then $\phi(n) = (p_1-1)p_1^{k_1-1}...(p_r-1)p_r^{k_r-1}$.
 * $\phi(n)=n \cdot \prod_{p|n}(1-1/p)$.
 *
 * $\sum_{d|n} \phi(d) = n$, $\sum_{1\leq k \leq n, \gcd(k,n)=1} k = n \phi(n)/2, n>1$
 * 
 * \textbf{Euler's thm}: $a,n$ coprime $\Rightarrow a^{\phi(n)} \equiv 1 \pmod{n}$.
 *
 * \textbf{Fermat's little thm}: $p$ prime $\Rightarrow a^{p-1} \equiv 1 \pmod{p}$ $\forall a$.
 * Status: Tested
 */
#pragma once

const int kLim = 5000000;
int phi[kLim];

void ComputePhi() {
  for (int i = 0; i < kLim; ++i)
	  phi[i] = (i % 2) ? i : i / 2;
	for (int i = 3; i < kLim; i += 2)
		if (phi[i] == i)
			for (int j = i; j < kLim; j += i)
				(phi[j] /= i) *= i - 1;
}
