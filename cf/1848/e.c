#include <stdio.h>
#include <stdlib.h>

#define N 1000000

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

	int x, q, m;
	scanf("%d%d%d", &x, &q, &m);

	int *inv = malloc((N + 1) * sizeof(int));
	inv[0] = 0;
	inv[1] = 1;
	if (m > N + 1) {
		m = N + 1;
	}
	for (int i = 2; i < m; i++) {
		inv[i] = m_sub(0, m_div(m / i, m % i, m, inv), m);
	}

	int ans = 1;
	int *cnt = malloc((N + 1) * sizeof(int));
	for (int i = 0; i <= N; i++) {
		cnt[i] = 1;
	}
	x >>= __builtin_ctz((unsigned int)x);
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			int c = 1;
			while (x % i == 0) {
				x /= i;
				c += 1;
			}
			ans = m_mul(ans, c, m);
			if (i <= N) {
				cnt[i] = c;
			}
		}
	}
	if (x > 1) {
		ans = m_mul(ans, 2, m);
		if (x <= N) {
			cnt[x] = 2;
		}
	}

	int flag = 0;
	for (; q > 0; q--) {
		int xi;
		scanf("%d", &xi);
		xi >>= __builtin_ctz((unsigned int)xi);

		while (xi > 1) {
			int p = mp[xi];
			xi /= p;

			int *c = &cnt[p];
			if (*c == 0) {
				flag -= 1;
			} else {
				ans = m_div(ans, *c, m, inv);
			}

			*c = m_add(*c, 1, m);
			if (*c == 0) {
				flag += 1;
			} else {
				ans = m_mul(ans, *c, m);
			}
		}

		if (flag > 0) {
			ans = 0;
		}
		printf("%d\n", ans);
	}

	free(mp);
	free(p);
	free(inv);
	free(cnt);
}
