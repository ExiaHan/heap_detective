#ifndef COLLECT_H
#define COLLECT_H
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdbool>
#include <fstream>
#include <cstddef>       
#include "Tokenizer.h"

using namespace std; 

struct sink {
	string value;
 	string line;
 	int line_number;
 	bool taint;
	bool inloop;
};

struct startpoint {
 	string var_name;
 	string line;
 	int line_number;
 	vector<sink> sinks;
};


class Detective
{
public:

// This is array of functions names that use HEAP
// brk(), sbrk() ? at the future
	string heap_in[7] = {"malloc","xmalloc","realloc","xrealloc","calloc","xcalloc","new "}; 
	string heap_out[5] = {"free","xfree","FREE","XFREE","delete "};
	string loop_in[3] = {"for","while","do"};
	string cond[4] = {"if","else","elseif","switch"};

	vector<startpoint> array;
	vector<sink> sinks;

	void get_sinks(string FileName);                                     

};

#endif 
