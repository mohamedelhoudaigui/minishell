#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int	a;

	a = access(".", F_OK);
	printf("%d\n", a);
	return (0);
}