# heap_detective
This tool uses the taint analysis technique for static analysis and aims to identify points of heap memory usage vulnerabilities in C and C++ languages. The tool uses a common approach in the first phase of static analysis, using tokenization to collect information. 

The second phase has a different approach to common lessons of the legendary dragon book, yes the tool doesn't use AST or resources like LLVM following parsers' and standard tips. The approach present aims to study other ways to detect vulnerabilities, using custom vector structures and typical recursive traversal with ranking following taint point. So the result of the sum of these techniques is the Heap_detective.

The tool follows the KISS principle "Keep it simple, stupid!". There's more than one way to do a SAST tool, I know that. Yes, I thought to use graph database or AST, but this action cracked the KISS principle in the context of this project.

# Features
* C and C++ tokenizer
* List of heap static routes for each source with taint points for analysis
* Analyser to detect double free vulnerability
* Analyser to detect use after free vulnerability
* Analyser to detect memory leak

To test, read the directory samplers to understand the context, so to run look that following:
```
$ git clone https://github.com/CoolerVoid/heap_detective

$ cd heap_detective

$ make
// to run
$ bin/heap_detective samplers/   
note:
So don't try "$ cd bin; ./heap_detective"
first argv is a directory for recursive analysis
```
The first argument by command is a directory for recursive analysis.
You can study bad practices in directory "samplers".

# Future features
* Analyser to detect off-by-one vulnerability
* Analyser to detect wild pointer
* Analyser to detect heap overflow vulnerability

## Overview
<img align="center" width="840" height="720" src="https://github.com/CoolerVoid/heap_detective/blob/master/doc/screen4.png">
<img align="center" width="840" height="500" src="https://github.com/CoolerVoid/heap_detective/blob/master/doc/Screenshot_21.png">
<img align="center" width="840" height="720" src="https://github.com/CoolerVoid/heap_detective/blob/master/doc/Screenshot_20.png">

```


Collect action done

  ...::: Heap static route :::...  
File path: samplers/example5.c
Var name: ch_ptr
line: 8:	ch_ptr = malloc(100);
Sinks: 
	 line: 8:	ch_ptr = malloc(100);
	 Taint:  True 
	 In Loop: false
	 line: 11:	free(ch_ptr);	
	 Taint:  True 
	 In Loop: false
	 line: 12:	free(ch_ptr);
	 Taint:  True 
	 In Loop: false
	 line: 6:	char *ch_ptr = NULL; 
	 Taint: false
	 In Loop: false
	 line: 6:	char *ch_ptr = NULL;
	 Taint: false
	 In Loop: false
	 line: 6:	char *ch_ptr = NULL;
	 Taint: false
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example2.c
Var name: ch_ptr
line: 7:	ch_ptr=malloc(100);
Sinks: 
	 line: 7:	ch_ptr=malloc(100);
	 Taint:  True 
	 In Loop: false
	 line: 11:		ch_ptr = 'A';
	 Taint: false
	 In Loop:  True 
	 line: 12:		free(ch_ptr);
	 Taint:  True 
	 In Loop:  True 
	 line: 13:		printf("%s\n", ch_ptr);
	 Taint: false
	 In Loop:  True 

  ...::: Heap static route :::...  
File path: samplers/example3.c
Var name: array
line: 10:	array = new int[100];
Sinks: 
	 line: 10:	array = new int[100];
	 Taint:  True 
	 In Loop: false
	 line: 12:	delete array;
	 Taint:  True 
	 In Loop: false
	 line: 14:	array=(int *)2;
	 Taint: false
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example3.c
Var name: array3
line: 18:	array3=realloc(400);
Sinks: 
	 line: 18:	array3=realloc(400);
	 Taint:  True 
	 In Loop: false
	 line: 22:		array3='1';
	 Taint: false
	 In Loop:  True 
	 line: 24:		free(array3);
	 Taint:  True 
	 In Loop:  True 

  ...::: Heap static route :::...  
File path: samplers/example3.c
Var name: array
line: 27:	array=malloc(1);
Sinks: 
	 line: 27:	array=malloc(1);
	 Taint:  True 
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example4.c
Var name: ch_ptr
line: 8:	ch_ptr = malloc(100);
Sinks: 
	 line: 8:	ch_ptr = malloc(100);
	 Taint:  True 
	 In Loop: false
	 line: 13:		ch_ptr = 'A';
	 Taint: false
	 In Loop:  True 
	 line: 14:		free(ch_ptr);
	 Taint:  True 
	 In Loop:  True 
	 line: 15:		printf("%s\n", ch_ptr);
	 Taint: false
	 In Loop:  True 

  ...::: Heap static route :::...  
File path: samplers/example1.c
Var name: buf1R1
line: 13:    buf1R1 = (char *) malloc(BUFSIZER1);
Sinks: 
	 line: 13:    buf1R1 = (char *) malloc(BUFSIZER1);
	 Taint:  True 
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example1.c
Var name: buf2R1
line: 14:    buf2R1 = (char *) malloc(BUFSIZER1);
Sinks: 
	 line: 14:    buf2R1 = (char *) malloc(BUFSIZER1);
	 Taint:  True 
	 In Loop: false
	 line: 16:    free(buf2R1);
	 Taint:  True 
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example1.c
Var name: buf2R2
line: 18:    buf2R2 = (char *) malloc(BUFSIZER2);
Sinks: 
	 line: 18:    buf2R2 = (char *) malloc(BUFSIZER2);
	 Taint:  True 
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example1.c
Var name: buf3R2
line: 19:    buf3R2 = (char *) malloc(BUFSIZER2);
Sinks: 
	 line: 19:    buf3R2 = (char *) malloc(BUFSIZER2);
	 Taint:  True 
	 In Loop: false
	 line: 24:    free(buf3R2);
	 Taint:  True 
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example6.c
Var name: ch_ptr
line: 8:	ch_ptr = malloc(100);
Sinks: 
	 line: 8:	ch_ptr = malloc(100);
	 Taint:  True 
	 In Loop: false
	 line: 11:	free(ch_ptr);
	 Taint:  True 
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example6.c
Var name: ch_ptr
line: 13:	ch_ptr = malloc(500);
Sinks: 
	 line: 13:	ch_ptr = malloc(500);
	 Taint:  True 
	 In Loop: false

>>-----> View end

>>-----> Start double free analyser

  ...::: Double free analyser :::...  
File path: samplers/example5.c
 Double free found!  
line: 8:	ch_ptr = malloc(100);
line: 11:	free(ch_ptr);	
line: 12:	free(ch_ptr);
line: 6:	char *ch_ptr = NULL; 

  ...::: Double free analyser :::...  
File path: samplers/example2.c
 Double free found!  
Maybe the function to liberate memory can be in a loop context!
line: 7:	ch_ptr=malloc(100);
line: 11:		ch_ptr = 'A';
line: 12:		free(ch_ptr);
line: 13:		printf("%s\n", ch_ptr);

  ...::: Double free analyser :::...  
File path: samplers/example3.c
 Double free found!  
Maybe the function to liberate memory can be in a loop context!
line: 18:	array3=realloc(400);
line: 22:		array3='1';
line: 24:		free(array3);

  ...::: Double free analyser :::...  
File path: samplers/example4.c
 Double free found!  
Maybe the function to liberate memory can be in a loop context!
line: 8:	ch_ptr = malloc(100);
line: 13:		ch_ptr = 'A';
line: 14:		free(ch_ptr);
line: 15:		printf("%s\n", ch_ptr);

>>-----> Start use after free analyser

  ...::: Use after free analyser :::...  
File path: samplers/example5.c
 Use after free found  
line: 8:	ch_ptr = malloc(100);
line: 11:	free(ch_ptr);	
line: 12:	free(ch_ptr);
line: 6:	char *ch_ptr = NULL; 

  ...::: Use after free analyser :::...  
File path: samplers/example2.c
 Use after free found  
line: 7:	ch_ptr=malloc(100);
line: 11:		ch_ptr = 'A';
line: 12:		free(ch_ptr);
line: 13:		printf("%s\n", ch_ptr);

  ...::: Use after free analyser :::...  
File path: samplers/example3.c
 Use after free found  
line: 10:	array = new int[100];
line: 12:	delete array;
line: 14:	array=(int *)2;
line: 27:	array=malloc(1);

  ...::: Use after free analyser :::...  
File path: samplers/example4.c
 Use after free found  
line: 8:	ch_ptr = malloc(100);
line: 13:		ch_ptr = 'A';
line: 14:		free(ch_ptr);
line: 15:		printf("%s\n", ch_ptr);


```

