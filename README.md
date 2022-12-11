# heap_detective
This tool uses the taint analysis technique for static analysis and aims to identify points of heap memory usage vulnerabilities in C and C++ languages. The tool uses a common approach in the first phase of static analysis, using tokenization to collect information. 

The second phase has a different approach to common lessons of the legendary dragon book, yes the tool doesn't use AST or resources like LLVM following parsers' and standard tips. The approach present aims to study other ways to detect vulnerabilities, using custom vector structures and typical recursive traversal with ranking following taint point. So the result of the sum of these techniques is the Heap_detective.

The tool follows the KISS principle "Keep it simple, stupid!". There's more than one way to do a SAST tool, I know that. Yes, I thought to use graph database or AST, but this action cracked the KISS principle in the context of this project.

https://antonio-cooler.gitbook.io/coolervoid-tavern/detecting-heap-memory-pitfalls

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

Note: tested in GCC 9 and 11
```
The first argument by command is a directory for recursive analysis.
You can study bad practices in directory "samplers".

# Future features
* Analyser to detect off-by-one vulnerability
* Analyser to detect wild pointer
* Analyser to detect heap overflow vulnerability

## Overview
<img align="center" width="840" height="500" src="https://github.com/CoolerVoid/heap_detective/blob/master/doc/Screenshot_199.png">
<img align="center" width="840" height="720" src="https://github.com/CoolerVoid/heap_detective/blob/master/doc/Screenshot_198.png">
<img align="center" width="840" height="720" src="https://github.com/CoolerVoid/heap_detective/blob/master/doc/Screenshot_196.png"

Output example:
```



Collect action done

  ...::: Heap static route :::...  
File path: samplers/example3.c
Func name: main
Var name: new
line: 10:	array = new obj[100];
Sinks: 
	 line: 10:	array = new obj[100];
	 Taint:  True 
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example3.c
Func name: 	while
Var name: array
line: 27:	array = malloc(1);
Sinks: 
	 line: 27:	array = malloc(1);
	 Taint:  True 
	 In Loop: false
	 line: 28:	array=2;
	 Taint: false
	 In Loop: false
	 line: 30:	array = malloc(3);
	 Taint:  True 
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example5.c
Func name: main
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

  ...::: Heap static route :::...  
File path: samplers/example1.c
Func name: main
Var name: buf1R1
line: 13:    buf1R1 = (char *) malloc(BUFSIZER1);
Sinks: 
	 line: 13:    buf1R1 = (char *) malloc(BUFSIZER1);
	 Taint:  True 
	 In Loop: false
	 line: 26:    free(buf1R1);
	 Taint:  True 
	 In Loop: false
	 line: 30:    if (buf1R1) {
	 Taint: false
	 In Loop: false
	 line: 31:	free(buf1R1);
	 Taint:  True 
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example2.c
Func name: main
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
File path: samplers/example4.c
Func name: main
Var name: ch_ptr
line: 8:	ch_ptr = malloc(100);
Sinks: 
	 line: 8:	ch_ptr = malloc(100);
	 Taint:  True 
	 In Loop: false
	 line: 13:		ch_ptr = 'A';
	 Taint: false
	 In Loop: false
	 line: 14:		free(ch_ptr);
	 Taint:  True 
	 In Loop: false
	 line: 15:		printf("%s\n", ch_ptr);
	 Taint: false
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example6.c
Func name: main
Var name: ch_ptr
line: 8:	ch_ptr = malloc(100);
Sinks: 
	 line: 8:	ch_ptr = malloc(100);
	 Taint:  True 
	 In Loop: false
	 line: 11:	free(ch_ptr);
	 Taint:  True 
	 In Loop: false
	 line: 13:	ch_ptr = malloc(500);
	 Taint:  True 
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example7.c
Func name: special
Var name: ch_ptr
line: 8:	ch_ptr = malloc(100);
Sinks: 
	 line: 8:	ch_ptr = malloc(100);
	 Taint:  True 
	 In Loop: false
	 line: 15:		free(ch_ptr);	
	 Taint:  True 
	 In Loop: false
	 line: 16:		ch_ptr = malloc(500);
	 Taint:  True 
	 In Loop: false
	 line: 17:		ch_ptr=NULL;
	 Taint: false
	 In Loop: false
	 line: 25:	char *ch_ptr = NULL;
	 Taint: false
	 In Loop: false

  ...::: Heap static route :::...  
File path: samplers/example7.c
Func name: main
Var name: ch_ptr
line: 27:	ch_ptr = malloc(100);
Sinks: 
	 line: 27:	ch_ptr = malloc(100);
	 Taint:  True 
	 In Loop: false
	 line: 30:	free(ch_ptr);
	 Taint:  True 
	 In Loop: false
	 line: 32:	ch_ptr = malloc(500);
	 Taint:  True 
	 In Loop: false

>>-----> Memory leak analyser

  ...::: Memory leak analyser :::...  
File path: samplers/example3.c
Function name: main
 memory leak found!  
line: 10:	array = new obj[100];

  ...::: Memory leak analyser :::...  
File path: samplers/example3.c
Function name: 	while
 memory leak found!  
line: 27:	array = malloc(1);
line: 28:	array=2;
line: 30:	array = malloc(3);

  ...::: Memory leak analyser :::...  
File path: samplers/example5.c
Function name: main
 memory leak found!  
line: 8:	ch_ptr = malloc(100);
line: 11:	free(ch_ptr);	
line: 12:	free(ch_ptr);

  ...::: Memory leak analyser :::...  
File path: samplers/example1.c
Function name: main
 memory leak found!  
line: 13:    buf1R1 = (char *) malloc(BUFSIZER1);
line: 26:    free(buf1R1);
line: 30:    if (buf1R1) {
line: 31:	free(buf1R1);

  ...::: Memory leak analyser :::...  
File path: samplers/example2.c
Function name: main
 memory leak found!  
Maybe the function to liberate memory can be in a loop context!
line: 7:	ch_ptr=malloc(100);
line: 11:		ch_ptr = 'A';
line: 12:		free(ch_ptr);
line: 13:		printf("%s\n", ch_ptr);

  ...::: Memory leak analyser :::...  
File path: samplers/example6.c
Function name: main
 memory leak found!  
line: 8:	ch_ptr = malloc(100);
line: 11:	free(ch_ptr);
line: 13:	ch_ptr = malloc(500);

  ...::: Memory leak analyser :::...  
File path: samplers/example7.c
Function name: special
 memory leak found!  
line: 8:	ch_ptr = malloc(100);
line: 15:		free(ch_ptr);	
line: 16:		ch_ptr = malloc(500);
line: 17:		ch_ptr=NULL;
line: 25:	char *ch_ptr = NULL;

  ...::: Memory leak analyser :::...  
File path: samplers/example7.c
Function name: main
 memory leak found!  
line: 27:	ch_ptr = malloc(100);
line: 30:	free(ch_ptr);
line: 32:	ch_ptr = malloc(500);

>>-----> Start double free analyser

  ...::: Double free analyser :::...  
File path: samplers/example5.c
Function name: main
 Double free found!  
line: 8:	ch_ptr = malloc(100);
line: 11:	free(ch_ptr);	
line: 12:	free(ch_ptr);

  ...::: Double free analyser :::...  
File path: samplers/example1.c
Function name: main
 Double free found!  
line: 13:    buf1R1 = (char *) malloc(BUFSIZER1);
line: 26:    free(buf1R1);
line: 30:    if (buf1R1) {
line: 31:	free(buf1R1);

  ...::: Double free analyser :::...  
File path: samplers/example2.c
Function name: main
 Double free found!  
Maybe the function to liberate memory can be in a loop context!
line: 7:	ch_ptr=malloc(100);
line: 11:		ch_ptr = 'A';
line: 12:		free(ch_ptr);
line: 13:		printf("%s\n", ch_ptr);

>>-----> Start use after free analyser

  ...::: Use after free analyser :::...  
File path: samplers/example5.c
Function name: main
 Use after free found  
line: 8:	ch_ptr = malloc(100);
line: 11:	free(ch_ptr);	
line: 12:	free(ch_ptr);

  ...::: Use after free analyser :::...  
File path: samplers/example1.c
Function name: main
 Use after free found  
line: 13:    buf1R1 = (char *) malloc(BUFSIZER1);
line: 26:    free(buf1R1);
line: 30:    if (buf1R1) {
line: 31:	free(buf1R1);

  ...::: Use after free analyser :::...  
File path: samplers/example2.c
Function name: main
 Use after free found  
line: 7:	ch_ptr=malloc(100);
line: 11:		ch_ptr = 'A';
line: 12:		free(ch_ptr);
line: 13:		printf("%s\n", ch_ptr);

  ...::: Use after free analyser :::...  
File path: samplers/example4.c
Function name: main
 Use after free found  
line: 8:	ch_ptr = malloc(100);
line: 13:		ch_ptr = 'A';
line: 14:		free(ch_ptr);
line: 15:		printf("%s\n", ch_ptr);

  ...::: Use after free analyser :::...  
File path: samplers/example6.c
Function name: main
 Use after free found  
line: 8:	ch_ptr = malloc(100);
line: 11:	free(ch_ptr);
line: 13:	ch_ptr = malloc(500);

  ...::: Use after free analyser :::...  
File path: samplers/example7.c
Function name: special
 Use after free found  
line: 8:	ch_ptr = malloc(100);
line: 15:		free(ch_ptr);	
line: 16:		ch_ptr = malloc(500);
line: 17:		ch_ptr=NULL;
line: 25:	char *ch_ptr = NULL;

  ...::: Use after free analyser :::...  
File path: samplers/example7.c
Function name: main
 Use after free found  
line: 27:	ch_ptr = malloc(100);
line: 30:	free(ch_ptr);
line: 32:	ch_ptr = malloc(500);




```

