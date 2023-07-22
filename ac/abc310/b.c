#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define bitmask(b) (1 << ((b) % CHAR_BIT))
#define bitslot(b) ((b) / CHAR_BIT)
#define bitset(a, b) ((a)[bitslot(b)] |= bitmask(b))
#define bitclear(a, b) ((a)[bitslot(b)] &= ~bitmask(b))
#define bittest(a, b) ((a)[bitslot(b)] & bitmask(b))
#define bitnslots(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)

enum BitResult {
	Equals,
	AContainsB,
	BContainsA,
	Intersection,
};

enum BitResult check(char a, char b) {
	if (a == b) {
		return Equals;
	}
	int c = a | b;
	if (c == a) {
		return AContainsB;
	}
	if (c == b) {
		return BContainsA;
	}
	return Intersection;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);

	const int x = bitslot(110);
	int *prices = malloc(n * sizeof(int *));
	char **products = malloc(n * sizeof(char *));
	for (int i = 0; i < n; i++) {
		products[i] = malloc(x * sizeof(char));
		char *p = products[i];
		int c;
		scanf("%d%d", &prices[i], &c);
		for (int j = 0; j < c; j++) {
			int f;
			scanf("%d", &f);
			bitset(p, f - 1);
		}
	}

	// TODO: free p and all other pointers
	for (int i = 0; i < n - 1; i++) {
		char *pi = products[i];
		for (int j = i; j < n; j++) {
			char *pj = products[j];
			if (prices[i] > prices[j]) {
				bool flag = true;
				for (int k = 0; k < x; k++) {
					enum BitResult res =
					    check(pi[k], pj[k]);
					if (res == Equals ||
					    res == BContainsA) {
						continue;
					}
					flag = false;
					break;
				}
				if (flag) {
					puts("Yes");
					return 0;
				}
			} else if (prices[i] < prices[j]) {
				bool flag = true;
				for (int k = 0; k < x; k++) {
					enum BitResult res =
					    check(pi[k], pj[k]);
					if (res == Equals ||
					    res == AContainsB) {
						continue;
					}
					flag = false;
					break;
				}
				if (flag) {
					puts("Yes");
					return 0;
				}
			} else {
				bool acb = false;
				bool bca = false;
				bool all_eq = true;
				bool all_pass = true;
				for (int k = 0; k < x; k++) {
					enum BitResult res =
					    check(pi[k], pj[k]);
					if (res == AContainsB) {
						if (!acb) {
							acb = true;
						}
						if (all_eq) {
							all_eq = false;
						}
					} else if (res == BContainsA) {
						if (!bca) {
							bca = true;
						}
						if (all_eq) {
							all_eq = false;
						}
					} else if (res == Equals) {
						// do nothing
					} else {
						all_pass = false;
						break;
					}
					if (acb && bca) {
						all_pass = false;
						break;
					}
				}
				if (!all_eq && all_pass) {
					puts("Yes");
					return 0;
				}
			}
		}
	}

	puts("No");
	return 0;
}
