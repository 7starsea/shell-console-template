#include "readinput.h"
#include <stdlib.h>
#include <algorithm>

#include <readline/readline.h>
#include <readline/history.h>

std::string shell_expect_a_command(std::string client, const std::string msg){

	std::string shell_prompt("[Admin]"); 
		shell_prompt.append(client);
		shell_prompt.push_back(':');
		shell_prompt.append(msg);
		shell_prompt.append("$ ");

	char* input = NULL;		std::string cmd;
	while (0 == cmd.size() ){
		input = readline(shell_prompt.c_str());
		if (input){
			if (std::any_of(input, input + strlen(input), shell_isnonwhitespace)){
				add_history(input);
				cmd = std::string(input);
			}
			free(input);
		}
	}
	return cmd;
}


std::string shell_expect_an_input(const std::string msg){
	std::string shell_prompt(msg); shell_prompt.append(": ");
	 
	char* input = NULL;		std::string inp;
	while (0 == inp.size()){
		input = readline(shell_prompt.c_str());
		if (input){
			inp = std::string(input);
			free(input);
		}
	}
	return inp;
}