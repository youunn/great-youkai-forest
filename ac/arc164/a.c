#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define su32 "%" SCNu32
#define su64 "%" SCNu64

typedef uint32_t u32;
typedef uint64_t u64;

static void solve() {
	u64 n, k;
	int _ = scanf(su64 su64, &n, &k);

	if ((n - k) % 2 == 1) {
		puts("No");
		return;
	}

	while (n > 0) {
		if (k < n % 3) {
			puts("No");
			return;
		}

		k -= n % 3;
		n /= 3;
	}

	puts("Yes");
}

int main() {
	u32 t;
	int _ = scanf(su32, &t);
	for (; t > 0; t--) {
		solve();
	}
}
