#include <stdio.h>
#include <stdlib.h>

#define N 1200000

static inline int m_add(int a, int b, int m) { return (a + b) % m; }
static inline int m_sub(int a, int b, int m) { return (a % m - b % m + m) % m; }
static inline int m_mul(int a, int b, int m) { return 1ll * a * b % m; }
static inline int m_div(int a, int b, int m, int *inv) {
	return m_mul(a, inv[b % m], m);
}

int main() {
	int *mp = malloc((N + 1) * sizeof(int));
	int *p = malloc((N / 10) * sizeof(int));
	for (int i = 0; i <= N; i++) {
		mp[i] = 0;
	}
	int index = 0;
	for (int i = 2; i <= N; i++) {
		int *m = &mp[i];
		if (*m == 0) {
			*m = i;
			p[index] = i;
			index += 1;
		}
		for (int j = 0; j < index; j++) {
			int cp = p[j];
			int n = i * cp;
			if (n > N) {
				break;
			}
			mp[n] = cp;
			if (cp == *m) {
				break;
			}
		}
	}
	free(p);

	int x, q, m;
	scanf("%d%d%d", &x, &q, &m);

	int *inv = malloc((N + 1) * sizeof(int));
	inv[1] = 1;
	for (int i = 2; i < m && i <= N; i++) {
		inv[i] = m_sub(0, m_div(m / i, m % i, m, inv), m);
	}

	// 奇因数个数
	int ans = 1;
	// 分解质因数
	int *fact = malloc((N + 1) * sizeof(int));
	for (int i = 0; i <= N; i++) {
		// 次数为0
		fact[i] = 1;
	}
	x >>= __builtin_ctz((unsigned int)x);
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			int c = 1;
			while (x % i == 0) {
				x /= i;
				c = m_add(c, 1, m);
			}
			ans = m_mul(ans, c, m);
			if (i <= N) {
				fact[i] = c;
			}
		}
	}
	if (x > 1) {
		const int c = 2;
		ans = m_mul(ans, c, m);
		if (x <= N) {
			fact[x] = c;
		}
	}

	int div0 = 0;
	int xi;
	for (; q > 0; q--) {
		scanf("%d", &xi);
		xi >>= __builtin_ctz((unsigned int)xi);

		while (xi > 1) {
			int p = mp[xi];
			xi /= p;

			// ans / c * (c + 1)

#if 0
if (p > N) {
	// fprintf(stderr, "p: %d\n", p);
}
#endif

			int *c = &fact[p];

			if (*c == 0) {
				div0 -= 1;
			} else {

#if 0			
if (*c > N) {
	fprintf(stderr, "c: %d\n", *c);
}
#endif

				ans = m_div(ans, *c, m, inv);
			}

			*c = m_add(*c, 1, m);
			if (*c == 0) {
				div0 += 1;
			} else {
				ans = m_mul(ans, *c, m);
			}
		}

		if (div0 > 0) {
			printf("%d\n", 0);
		} else {
			printf("%d\n", ans);
		}
	}

	free(mp);
	free(inv);
	free(fact);
}
