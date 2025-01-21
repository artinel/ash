#include"command.h"
#include<std/io.h>

//Built-in commmands

void clear(){
	prints("\033[2J\033[H");
}
