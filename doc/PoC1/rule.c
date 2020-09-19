#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  OPEN,CLOSE,COUNTER,END
};

char *ReadLines(char * NameFile);


int parse_ion(char** p, char** lex)
{
    char* marker;

    for (;;) {
    *lex = *p;
        /*!re2c
        re2c:define:YYCTYPE  = "char";
        re2c:define:YYCURSOR = *p;
        re2c:define:YYMARKER = marker;
        re2c:yyfill:enable   = 0;
        re2c:yych:conversion = 0;
        re2c:indent:top      = 1;
        "open".*            { return OPEN; }
        "close".*               { return CLOSE; }
        "\x0a"              { return COUNTER; }
        "\x00"               { return END; }
        [^]                  { continue; }
    */
    }
    free(lex);
    free(marker);
}


int main() 
{
    char *p = ReadLines("extest.c");
    char *last = p;
    int test=0,result=0,line_number=1,opens=0,closes=0;
    puts(p);


    while(!result )
	switch (parse_ion(&p, &last)) 
	{
        	case OPEN:
		opens++;
	    	test=1;	
	    	printf("OPEN function at line %d\n",line_number); //   (line_number>2)?line_number+3:line_number);
            	break;


	        case CLOSE:
		closes++;
	        test=0;
     	        printf("CLOSE function at line %d\n",line_number);
   	        break;

        	case COUNTER:
	    	line_number++;
            	break;

        	case END:
	    	result=1;	
            	break;
        }

    if(opens!=closes)
	puts("\n Here be dragons here!\n");
    else
	puts("\n Cannot detect pitfalls here!");


    return 0;
}



char *ReadLines(char * NameFile)
{
	FILE * arq=NULL;

	arq = fopen(NameFile, "rx");

	if( arq == NULL )
	{
		puts("error in to open() file"); 	 
		exit(0);
	}

	char *lineBuffer=calloc(1,1); 
	char line[512];
	memset(line,0,511);

	while( fgets(line,sizeof line,arq) )  
	{
		lineBuffer=realloc(lineBuffer,strlen(lineBuffer)+strlen(line)+2);
		strncat(lineBuffer,line,strlen(lineBuffer)-1);
	}

 
	if( fclose(arq) == EOF )
	{
		printf("Error in close() file %s",NameFile);
		exit(0);
	}

	arq=NULL;

	lineBuffer[strlen(lineBuffer)-1]='\0';

	return lineBuffer;
}
