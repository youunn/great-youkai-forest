#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef uint64_t u64;

static inline u64 max(u64 a, u64 b) { return a > b ? a : b; }
static inline u64 min(u64 a, u64 b) { return a > b ? b : a; }
static inline u64 chmax(u64 *a, u64 b) { return *a = max(*a, b); }

static inline void next(u64 *s, u64 *k, u64 *r) {
	*s += *r;
	*r = *s % 10;
	*k -= 1;
}

static inline u64 f(u64 x, u64 s, u64 k) {
	// ans is a quadratic function about x
	u64 s1 = s + 20 * x;
	u64 k1 = k - 4 * x;
	u64 ans = s1 * k1;
	return ans;
}

static u64 ternary_search_maximum(u64 l, u64 r, u64 s, u64 k) {
	u64 d = (r - l);
	u64 fl = f(l, s, k);
	u64 fr = f(r, s, k);
	u64 m = max(fl, fr);

	if (d == 2) {
		chmax(&m, f(l + 1, s, k));
	}
	d /= 3;
	if (d == 0) {
		return m;
	}

	if (fl > fr) {
		r -= d;
	} else {
		l += d;
	}

	return ternary_search_maximum(l, r, s, k);
}

static void solve() {
	u64 s, k;
	int _ = scanf("%" SCNu64 "%" SCNu64, &s, &k);
	assert(_ == 2);

	u64 ans = s * k;
	u64 r = s % 10;

	if (r % 2 == 1) {
		next(&s, &k, &r);
		chmax(&ans, s * k);
	}
	if (r == 0) {
		printf("%" PRIu64 "\n", ans);
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (k == 0) {
			break;
		}
		u64 m = ternary_search_maximum(0, k / 4, s, k);
		chmax(&ans, m);
		next(&s, &k, &r);
	}

	printf("%" PRIu64 "\n", ans);
}

int main() {
	int t;
	int _ = scanf("%d", &t);
	assert(_ == 1);
	for (; t > 0; t--) {
		solve();
	}
}
