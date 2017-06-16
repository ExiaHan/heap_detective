#include <stdlib.h>
#include <stdio.h>

int main(void)
{   
	char *ch_ptr = NULL; 
	ch_ptr=malloc(100);

	for (int i = 0; i < 99; i++) 
	{
		ch_ptr = 'A';
		free(ch_ptr);
		printf("%s\n", ch_ptr);
	}
	
	return 0;

}
