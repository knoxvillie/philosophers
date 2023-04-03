#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	int	*a;
	int	i;

	a = (int *)malloc(sizeof(int) * (1));
	i = fork();
	*a = i;
	printf("Process number :%d array: %d end: %p\n", i, *a, a);
	if (!i)
		printf("fazendo um monte de coisa %d\n", i);
	printf("fazendo mais coisas %d\n", i);
	return 0;
}
