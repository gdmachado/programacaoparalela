#include <stdio.h>

main() {
	int v[] = {10, 20, 30};
	int i;

	for(i = 0; i < 3; i++) {
		printf("valor de v[%d] = %d\n", i, *(v+i));
	}
}
