#include <stdlib.h>
#include <stdio.h>

int main(void)
{   
	char *ch_ptr = NULL;

	ch_ptr = malloc(100);
	int i=0;

	while (i < 99) 
	{
		ch_ptr = 'A';
		free(ch_ptr);
		printf("%s\n", ch_ptr);
		i++;
	}
	
	return 0;

}
