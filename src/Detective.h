#ifndef COLLECT_H
#define COLLECT_H
#include <vector>
#include <cstring>
#include <string>
#include <dirent.h>
#include <iostream>
#include <sstream>
#include <cstdbool>
#include <fstream>
#include <cstddef>       
#include "Tokenizer.h"
#include <stdint.h>

// set DEBUG ON
#define BUGVIEW_DETECTIVE 1
#define HEAP_DETECTIVE_DEBUG(x, s...) do { \
 if (!BUGVIEW_DETECTIVE) { break; } \
 time_t t = time(NULL); \
 char *d = ctime(&t); \
 fprintf(stderr, "\n--- DEBUG-START ---\n\n %.*s %s[%d] %s(): \n", \
 (int)strlen(d) - 1, d, __FILE__, \
 __LINE__, __FUNCTION__); \
 fprintf(stderr, x, ## s); \
 fprintf(stderr,"\n\n--- DEBUG-END ---\n"); \
} while (0);

using namespace std; 

struct sink {
	string value;
 	string line;
 	size_t line_number;
 	bool taint;
	bool inloop;
};

struct startpoint {
	string filename;
 	string var_name;
 	string line;
 	size_t line_number;
 	vector<sink> sinks;
};

class Detective
{
public:

// This is array of functions names that use HEAP
// brk(), sbrk() ? at the future
	vector<string> heap_in = {"kmalloc","malloc","xmalloc","snmalloc","realloc","krealloc","xrealloc","calloc","kcalloc","xcalloc","new ","reallocarray","kreallocarray","strdup"}; 
	vector<string> heap_out = {"free","xfree","FREE","XFREE","delete ","kfree"};
	vector<string> loop_in = {"for","while","do"};
	vector<string> cond = {"if","else","elseif","switch"};
	vector<string> files_path; // list of paths to open each file...
	vector<startpoint> array;
	vector<sink> sinks;
	size_t pos=0;
	bool loop_status=false;
	bool cond_status=false;
	int loop_counter=0;
 	bool end_exp(string line);
	void set_target_path(string path);
	void get_all_sinks();
	void get_sinks(string FileName);                                     
	void view_sinks();   
	void clear_sinks();                                     
        bool loop_check(string line);
        bool condition_check(string line);
	// todo add flow end check
};

#endif 
