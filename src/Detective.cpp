// Coded by CoolerVoid
#include "Tokenizer.h"
#include "Detective.h"
using namespace std;

bool Detective::end_exp(string line)
{
	bool test=false;

		if(line.find("}")!=string::npos)
			test=true;

	return test;
}

bool Detective::loop_check(string line)
{

	int x=0;
	bool test=false;

	while(x != int(loop_in.size()))
	{					
		if(line.find(loop_in[x])!=string::npos)
			test=true;
		x++;
	}

	return test;
}

bool Detective::condition_check(string line)
{

	int x=0;
	bool test=false;

	while(x != int(cond.size()))
	{					
		if(line.find(cond[x])!=string::npos)
			test=true;
		x++;
	}

	return test;
}

void Detective::set_target_path(string path)
{
	const bool showHiddenDirs = false;
    	DIR *path_dir;
    	struct dirent *tmp;
    	path_dir = opendir(path.c_str());

    	if(path_dir != NULL)	
        	while((tmp = readdir(path_dir)) != NULL)
		{
            		if(showHiddenDirs ? (tmp->d_type==DT_DIR && string(tmp->d_name) != ".." && string(tmp->d_name) != "." ) : (tmp->d_type==DT_DIR && strstr(tmp->d_name,"..") == NULL && strstr(tmp->d_name,".") == NULL ) )
                		set_target_path(path+tmp->d_name+"/");
            		
            		if(tmp->d_type==DT_REG)
			{ 
				if (files_path.size() != SIZE_MAX)
               				files_path.push_back(path+tmp->d_name);
				else {
					HEAP_DETECTIVE_DEBUG("ERROR: Out of limit in files_path var");
					exit(0);
				}
            		}
        	}

    	closedir(path_dir);
}

void Detective::get_all_sinks()
{
	size_t len_list=files_path.size(),x=0;

	while(x != len_list)
	{
		get_sinks(files_path[x]);
		x++;
	}
}


void Detective::get_sinks(string FileName)
{
	string line;
	ifstream file;
	bool have_var=false,filename_test=false;	
	size_t pos2=0,pos3=0,line_counter=1,found_char=0,count_functions=0;


	sinks.clear();

	file.open(FileName);

		if(file.fail())
		{
			cout << "Error in open file!";
			file.clear();
			return;
		}

	//test=false;	

		while(getline(file, line))
		{

/*
 **TODO add LOOP detector to insert loop element at struct sink..
*/
			loop_counter+=loop_check(line)==true?1:0;
			loop_counter-=(end_exp(line)==true)?1:0;
			have_var=false;
			// loop_counter+=cond_check(line)==true?1:0;
// collect startpoint	 
	
			found_char = line.find_first_of('=');

			if(found_char!=string::npos)
			{
				count_functions=0;


				while(count_functions != heap_in.size())
				{
						
					if(line.find(heap_in[count_functions])!=string::npos)
					{
						Tokenizer str;
						string token;
						str.set(line);
						token = str.next();
      						if(array.size() != SIZE_MAX)
						{	
 							array.push_back(startpoint());
							array[pos].filename = FileName;
							array[pos].var_name = token;
							array[pos].line = line;
							array[pos].line_number = line_counter;
							pos3=pos;
							pos++;
						} else {
							HEAP_DETECTIVE_DEBUG("ERROR: Out of limit in array vector var");
							exit(0);
						}
					}

					count_functions++;
				}

					
// collect sinks	
			}			
			pos2=0;

			while(pos2!=array.size())
			{
				count_functions=0;
				have_var=false;
				filename_test=false;	

				

// check the use of var tainted
				if(line.find(array[pos2].var_name)!=string::npos)
				{
					have_var=true;
					filename_test=(array[pos3].filename==array[pos2].filename)?true:false;
				} 
// Check heap array list
				while(count_functions!=heap_in.size())
				{
					if(!heap_in[count_functions].empty())
						if ( (line.find(heap_in[count_functions],0)!=string::npos) && (filename_test==true) && (have_var==true) && (line.find(array[pos3].var_name,0)!=string::npos))
						{
							sink makestruct2 = {array[pos2].var_name,line,line_counter,true,loop_counter>=1?true:false,false,true};

      							if(array[pos3].sinks.size() != SIZE_MAX) 	
							{
								array[pos3].sinks.push_back(makestruct2);
							        goto END_VIEW_DETECTIVE;
							} else {
								HEAP_DETECTIVE_DEBUG("ERROR: Out of limit in array.sinks vector");
								exit(0);
							}
							goto END_VIEW_DETECTIVE;			
						}	
			
					count_functions++;
				}
				
				count_functions=0;
// collect free
				while(count_functions!=heap_out.size())
				{
					if(!heap_out[count_functions].empty())
						if ( (line.find(heap_out[count_functions],0)!=string::npos)&&(filename_test==true)&&(have_var==true) && (line.find(array[pos3].var_name,0)!=string::npos))
						{
							sink makestruct2 = {array[pos2].var_name,line,line_counter,true,loop_counter>=1?true:false,true,false};

      							if(array[pos3].sinks.size() != SIZE_MAX)
							{
									array[pos3].sinks.push_back(makestruct2);
									goto END_VIEW_DETECTIVE;
							} else {
								HEAP_DETECTIVE_DEBUG("ERROR: Out of limit in array.sinks vector");
								exit(0);
							}
							goto END_VIEW_DETECTIVE;			
						}	
			
					count_functions++;
				}
				count_functions=0;

				if(have_var==true && filename_test==true && (line.find(array[pos3].var_name,0)!=string::npos))
				{
					sink makestruct2 = {array[pos2].var_name,line,line_counter,false,loop_counter>=1?true:false,false,false};
					array[pos3].sinks.push_back(makestruct2);

					goto END_VIEW_DETECTIVE;
				}
				have_var=false;
				filename_test=false;
				pos2++;
			}

			END_VIEW_DETECTIVE:

			found_char=0;	
			line_counter++;

			//loop_counter-=(end_exp(line)==true)?1:0;
		}

        loop_counter=0;
	file.close();
}

void Detective::view_sinks()
{
	size_t x=0,y=0;

	while(x != array.size())
	{

		cout << "\n \u001b[4m\u001b[44m ...::: Heap static route :::...  \u001b[0m\n";	
		cout << "File path: " << array[x].filename << "\n";			
		cout << "Var name: " << array[x].var_name << "\n";			
		cout << "line: " << array[x].line_number << ":" << array[x].line << "\n";			
		cout << "Sinks: \n";

		while(y != array[x].sinks.size() )
		{
//			cout << "\t Var name: " << array[x].sinks[y].value << "\n";			
			cout << "\t line: " << array[x].sinks[y].line_number << ":" << array[x].sinks[y].line << "\n";
			cout << "\t Taint: " << ((array[x].sinks[y].taint==true)?"\u001b[41;1m True \u001b[0m":"false") << "\n";	
			cout << "\t In Loop: " << ((array[x].sinks[y].inloop==true)?"\u001b[46;1m True \u001b[0m":"false") << "\n";
			y++;
		}

		y=0;			
		x++;
	}


}


void Detective::list_var_by_filename(string filename, string varname)
{

	size_t x=0,y=0;

	if(array.empty())
		return;
	while(x != array.size())
	{

		if((!strcmp(array[x].filename.c_str(),filename.c_str())) && !strcmp(array[x].var_name.c_str(),varname.c_str()))
		{

			cout << "line: " << array[x].line_number << ":" << array[x].line << "\n";		

			while ( y != array[x].sinks.size()) 
			{
				if(array[x].sinks[y].line_number != array[x].line_number && array[x].sinks[y].line_number != array[x].sinks[y-1].line_number)
					cout << "line: " << array[x].sinks[y].line_number << ":" << array[x].sinks[y].line << "\n";
				y++;
			}
			y=0;
		}
		x++;
	}

}



void Detective::double_free()
{
	size_t x=0,y=0;
	short int counter_free=0;

	while(x != array.size())
	{

		while(y != array[x].sinks.size() )
		{

			if(array[x].sinks[y].liberate==true)
				counter_free+=array[x].sinks[y].inloop==true?5:1;
		
			if(counter_free>=2)
			{
				cout << "\n \u001b[4m\u001b[44m ...::: Double free analyser :::...  \u001b[0m\n";	
				cout << "File path: " << array[x].filename << "\n";		
				cout << "\u001b[41;1m Double free found! \u001b[0m \n";	

				if(counter_free>=5)
					cout << "Maybe the function to liberate memory can be in a loop context!\n";

				list_var_by_filename(array[x].filename , array[x].var_name );			
				counter_free=0;
			}
			y++;
		}
		counter_free=0;
		y=0;			
		x++;
	}
}




void Detective::use_after_free()
{
	size_t x=0,y=0;
	short int counter_free=0;
	size_t number_line=0;
	string last_var="";
	string free_line="";

	while(x != array.size())
	{

		while(y != array[x].sinks.size() )
		{

			if(counter_free && array[x].line_number != array[x].sinks[y].line_number )
			{

				if((!strcmp(array[x].var_name.c_str(),last_var.c_str())) && number_line > array[x].line_number && number_line < array[x].sinks[y].line_number )
				{


					cout << "\n \u001b[4m\u001b[44m ...::: Use after free analyser :::...  \u001b[0m\n";	
					cout << "File path: " << array[x].filename << "\n";		
					cout << "\u001b[41;1m Use after free found \u001b[0m \n";
					list_var_by_filename(array[x].filename , array[x].var_name );			
				}		
			}


			if(array[x].sinks[y].liberate==true)
			{
				counter_free+=1;
				last_var=array[x].var_name;
				free_line=array[x].sinks[y].line;
				number_line=array[x].sinks[y].line_number;
			}
			y++;
		}
//		counter_free=0;
		y=0;			
		x++;
	}
}

// free all context from memory
void Detective::clear_sinks()
{
	array.clear();
	files_path.clear();
        sinks.clear();
	heap_in.clear();
	heap_out.clear();
	loop_in.clear();
	cond.clear();
}
