#include<std/io.h>
#include<std/string.h>
#include<sys/time.h>
#include<std/mem.h>
#include<sys/exec.h>
#include<io/file.h>
#include<error.h>
#include"version.h"
#include"command.h"
#include"prompt.h"

void readline();
void process_cmd();
void find_cmd(const char* cmd);
void exec_cmd(const char* cmd, char** args);

int main(int argc, char** argv){
	error_autolog(false);
	if(argc > 1){
		if(str_equ(argv[1], "-v"))
			prints("Ash shell v%s\n", ASH_VERSION);
	}else{
		clear();
		prints("Welcome to Ash version %s\n", ASH_VERSION);
		readline();
	}
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
	}else if(str_equ(cmd, "exit")){
		cmd_exit(0);
	}else{
		if(cmd[0] == '.' && cmd[1] == '/'){
			if(fexists(&cmd[2])){
				exec_cmd(&cmd[2], args);		
			}else{
				printse(T_RED"Command '%s' not found!!!\n"T_NORMAL, cmd);
			}
		}else{
			if(fexists(cmd)){
				exec_cmd(cmd, args);
			}else{
				char* buf = malloc(PROMPT_BUFFER_SIZE + 1);
				sprints(buf, "/bin/%s", cmd);
				if(fexists(buf)){
					exec_cmd(buf, args);
				}else{
					printse(T_RED"Command '%s' not found!!!\n"T_NORMAL, buf);
				}
				free(buf);
			}
		}
	}

	free(args);
}

void readline(){
	char cmd[PROMPT_BUFFER_SIZE];
	while(1){
		get_prompt(cmd);
		process_cmd(cmd);
	}
}

void exec_cmd(const char* cmd, char** args){
	pid_t pid = fork();
		if(pid == 0){
			char* envp[1];
			envp[0] = 0;
			int res = exec(cmd, (const char* const*)args, (const char* const*)envp);
			terminate(res);
		}else{
			siginfo_t info;
			waitid(P_PID, pid, &info, WEXITED, NULL);
		}
}
