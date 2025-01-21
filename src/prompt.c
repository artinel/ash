#include"prompt.h"
#include<std/io.h>

void get_prompt(char* buffer){
	prints(T_GREEN"$>"T_NORMAL);
	scans(buffer, PROMPT_BUFFER_SIZE, 0);
}
