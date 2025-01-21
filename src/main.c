#include<std/io.h>
#include<std/string.h>
#include<sys/time.h>
#include<std/mem.h>
#include"version.h"
#include"command.h"
#include"prompt.h"

void readline();
void process_cmd();

int main(int argc, char** argv){
	clear();
	prints("Welcome to Ash version %s\n", ASH_VERSION);
	readline();
	return 0;
}

void process_cmd(char* cmd){
	char** args = cmd_to_args(cmd);
	//Check for built-in commands
	if(str_equ(cmd, "clear"))
		clear();
	else if(str_equ(cmd, "pwd"))
		pwd();
	else if(str_equ(cmd, "cd")){
		if(args[1])
			cd(args[1]);
		else
			cd("/");
	}else
		prints(T_RED"Command not found!!!\n"T_NORMAL);

	free(args);
}

void readline(){
	char cmd[PROMPT_BUFFER_SIZE];
	while(1){
		get_prompt(cmd);
		process_cmd(cmd);
	}
}
