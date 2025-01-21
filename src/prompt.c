#include"prompt.h"
#include<std/io.h>
#include<sys/dir.h>

void get_prompt(char* buffer){
	char cwd[512];
	get_cwd(cwd, sizeof(cwd));
	prints(T_GREEN"(%s%s%s)-> "T_NORMAL, T_YELLOW, cwd, T_GREEN);
	scans(buffer, PROMPT_BUFFER_SIZE, 0);
}
