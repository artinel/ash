#include"prompt.h"
#include<std/io.h>
#include<sys/dir.h>
#include<std/string.h>
#include<std/mem.h>

void get_prompt(char* buffer){
	char cwd[512];
	get_cwd(cwd, sizeof(cwd));
	prints(T_GREEN"(%s%s%s)-> "T_NORMAL, T_YELLOW, cwd, T_GREEN);
	scans(buffer, PROMPT_BUFFER_SIZE, 0);
}

char** cmd_to_args(char* cmd){
	int len = str_len(cmd);
	int num_spaces = str_rep(cmd, ' ', '\0');

	char** argv = malloc(sizeof(char*) * (num_spaces + 1));
	int cur_item = 0;
	argv[0] = cmd;

	for(int i = 0; i < len; i++){
		if(cmd[i] == '\0'){
			argv[++cur_item] = cmd + i + 1;
		}
	}
	argv[++cur_item] = 0;
	return argv;
}
