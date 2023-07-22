#include <stdio.h>

int main() {
	int n, p, q;
	scanf("%d%d%d", &n, &p, &q);
	int m = 100000;
	for (int i = 0; i < n; i++) {
		int d;
		scanf("%d", &d);
		if (d < m) {
			m = d;
		}
	}
	if (q + m < p) {
		p = q + m;
	}
	printf("%d\n", p);
}
