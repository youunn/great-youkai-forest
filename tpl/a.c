#include <stdio.h>

static void solve() {
	printf("%d\n", 1);
}

int main() {
	int t;
	int _ = scanf("%d", &t);
	for (; t > 0; t--) {
		solve();
	}
}
