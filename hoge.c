#include "src/coord.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	t_coord	coord;

	coord = malloc(sizeof(t_coord));
	coord_assign(&coord, 3, 5);
	printf("%f\n", coord.x);
}
