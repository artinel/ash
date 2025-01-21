#include"command.h"
#include<std/io.h>
#include<sys/dir.h>

//Built-in commmands

void clear(){
	prints("\033[2J\033[H");
}

void pwd(){
	char buffer[512];
	get_cwd(buffer, sizeof(buffer));
	prints("%s\n",buffer);
}
