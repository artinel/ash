#include"command.h"
#include<std/io.h>
#include<sys/dir.h>
#include<error.h>

//Built-in commmands

void clear(){
	prints("\033[2J\033[H");
}

void pwd(){
	char buffer[512];
	get_cwd(buffer, sizeof(buffer));
	prints("%s\n",buffer);
}

void cd(const char* path){
	short res = 0;
	res = chdir(path);
	if(res < 0){
		res = -res;
		if(res == E_NOFD)
			printse(T_RED"No such file or directory!!!\n"T_NORMAL);
	}
}
