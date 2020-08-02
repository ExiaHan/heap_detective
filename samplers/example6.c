#include <stdlib.h>
#include <stdio.h>

int main(void)
{   
	char *X = NULL;
	X = malloc(100);
	int i;
        X = malloc(101);

	for (i = 0; i < 99; i++) 
	{     
		X = 'A';
		printf("%s\n", ch_ptr);
	}
        X=malloc(1023);
	free(X);

	
	return 0;

}
