#include <stdio.h>

char *Read_file_unsafe(char * NameFile)
{
	FILE * arq=NULL;

	arq = fopen(NameFile, "rx");

	if( arq == NULL )
	{
		exit(1);
	}

	char *lineBuffer=calloc(1,1);
	char line[2048];

	while( fgets(line,sizeof line,arq) )
	{
		lineBuffer=realloc(lineBuffer,strlen(lineBuffer)+strlen(line));
		strncat(lineBuffer,line,2048);
	}

	arq=NULL;

	lineBuffer[strlen(lineBuffer)-1]='\0';


	char *tmp=lineBuffer;

	return tmp;
}


char *Read_file_safe(char * NameFile)
{
	FILE * arq=NULL;

	arq = fopen(NameFile, "rx");

	if( arq == NULL )
	{
		exit(1);
	}

	char *lineBuffer=calloc(1,1); 
	char line[2048];

	while( fgets(line,sizeof line,arq) )  
	{
		lineBuffer=realloc(lineBuffer,strlen(lineBuffer)+strlen(line));
		strncat(lineBuffer,line,2048);
	}

 
	fclose(arq);
	arq=NULL;

	lineBuffer[strlen(lineBuffer)-1]='\0';


	char *tmp=lineBuffer;
	free(lineBuffer);

	return tmp;
}
