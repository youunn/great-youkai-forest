#include <stdbool.h>
#include <stdio.h>

static void solve() {
	int n, m, k;
	int _;
	_ = scanf("%d%d%d", &n, &m, &k);

	int x, y;
	_ = scanf("%d%d", &x, &y);
	int p = (x + y) % 2;

	bool ans = true;
	for (int i = 0; i < k; i++) {
		int xi, yi;
		_ = scanf("%d%d", &xi, &yi);
		int pi = (xi + yi) % 2;
		if (ans && p == pi) {
			ans = false;
		}
	}

	if (ans) {
		puts("YES");
	} else {
		puts("NO");
	}
}

int main() {
	int t;
	int _ = scanf("%d", &t);
	for (; t > 0; t--) {
		solve();
	}
}
