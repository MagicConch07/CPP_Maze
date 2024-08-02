#include "Core.h"
#include "define.h"

int main() {
	int fuck = clock();
	while (true) {
		int dt = 1.0/(clock() - fuck);
		fuck = clock();
	}

	return 0;
}