#include <stdlib.h>
#include <stdio.h>

int main(void)
{   
	char *ch_ptr = NULL;

	ch_ptr = malloc(100);
	int i=0;

	free(ch_ptr);	
	free(ch_ptr);
	
	return 0;

}
