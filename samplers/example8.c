#include <stdlib.h>
#include <stdio.h>

static char *test(char * test)
{   
	char *ch_ptr[10];

	ch_ptr = malloc(10*sizeof(ch_ptr));

	int i=0;
	i=1000;

	if(i) {
	
		free(ch_ptr);	
		ch_ptr[1] = malloc(500);
		ch_ptr[1]=NULL;
	}
	return " ";
}


int main(void)
{   
	char **ch_ptr = NULL;

	ch_ptr = malloc(100);
	int i=0;

	free(ch_ptr);
	
	ch_ptr = malloc(500);

	return 0;

}
