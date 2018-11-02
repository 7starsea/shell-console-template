#include "shell_console_base.h"
#include <algorithm>
#include <stdio.h>
#include <cstdlib>
#include "readinput.h"


bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

void split_by(const std::string& s, std::vector<std::string> & v){
	std::string buff;

	const std::size_t n = s.size();
	for (std::size_t i = 0; i < n; ++i){
		if (shell_iswhitespace(s[i])){
			if (buff.size() > 0){
				v.push_back(buff); buff.clear();
			}
		}
		else{
			buff.push_back(s[i]);
		}
	}
	if (buff.size() > 0) v.push_back(buff);
}

void format_help_msg(const char * cmd, const char * help_msg, const std::vector<std::string> & examples){
	printf("%-10s: %s\n", cmd, help_msg);
	for (auto it = examples.begin(); it != examples.end(); ++it){
		printf("%-12s%s\n", " ", it->c_str());
	}
}
void print_base_help(){
	std::vector<std::string>  examples;

	format_help_msg("help,?", "print help message", examples);
	format_help_msg("list,ls", "list all envs/clients", examples);
	format_help_msg("exit", "close console or exit current env/client", examples);
	format_help_msg("quit,q", "an alias for exit", examples);
	
	examples.emplace_back("switch [env/client];  sw [env/client]");
	format_help_msg("switch,sw", "switch/enter to env", examples);
}

ShellConsoleBase::ShellConsoleBase()
	:envs_(), cur_env_()
{};


std::string ShellConsoleBase::_expect_an_input(const std::string msg){
	return shell_expect_an_input(msg);
}
std::string ShellConsoleBase::_expect_a_command(const std::string msg){
	return shell_expect_a_command(cur_env_, msg);
}

char ShellConsoleBase::_expect_a_yesorno(const std::string msg){
	std::string yesorno = shell_expect_an_input(msg);
	while (!(1 == yesorno.size() && ('y' == yesorno[0] || 'Y' == yesorno[0] ||
		'n' == yesorno[0] || 'N' == yesorno[0])))
	{
		printf(">>> Invalid input %s, must be either y/Y or n/N.\n", yesorno.c_str());
		yesorno = shell_expect_an_input(msg);
	}
	return yesorno[0];
}

void ShellConsoleBase::remove_envi(const std::string & env){
	auto it = std::find(envs_.begin(), envs_.end(), env);
	if (it != envs_.end()){
		envs_.erase(it);
		if (0 == cur_env_.compare(env)){
			cur_env_ = "";
		}
	}
}
void ShellConsoleBase::add_envi(const std::string & env){
	auto it = std::find(envs_.begin(), envs_.end(), env);
	if (it == envs_.end()){
		envs_.push_back(env);
	}
	if (0 == cur_env_.size()){
		cur_env_ = env;
	}
}


//等待操作
void ShellConsoleBase::wait_for_operation(){
	while (1){	
		std::string cmd_str = _expect_a_command();
		log(cmd_str);

		shell_trim(cmd_str);

		std::string::iterator new_end = std::unique(cmd_str.begin(), cmd_str.end(), BothAreSpaces);
		cmd_str.erase(new_end, cmd_str.end());

		std::vector<std::string > cmd_vec;
		split_by(cmd_str, cmd_vec);

		const std::string cmd = cmd_vec[0];
		if (0 == cmd.compare("quit") || 0 == cmd.compare("exit") || 0 == cmd.compare("q")){
			if (cur_env_.size() > 0){
				cur_env_.clear();
			}
			else{
				printf("exiting...\n");
				break;
			}
		}
		else if (0 == cmd.compare("list") || 0 == cmd.compare("ls")){
			__display_all_envi();
		}
		else if (0 == cmd.compare("help") || 0 == cmd.compare("?")){
			print_base_help();
			print_help();
		}
		else if (0 == cmd.compare("switch") || 0 == cmd.compare("sw")){
			if (cmd_vec.size() >= 2){
				__switch_envi(cmd_vec[1]);
			}
			else{
				printf(">>> switch(sw) command needs an argument (env/client).\n");
			}
		}
		else{
			/// all other commands goes here.
			process_command(cmd_vec);
		}
	}
}


//显示所有的client
void ShellConsoleBase::__display_all_envi(){
	if (envs_.size() == 0){
		printf("There is no env/client!\n");
	}
	else{
		int cout_number = 0;
		for (auto it = envs_.begin(); it != envs_.end(); ++it){
			printf("%d.%s ", cout_number + 1, it->c_str());

			++cout_number;
			if (cout_number % 3 == 0){
				printf("\n");
			}
		}
		if (cout_number % 3 != 0){
			printf("\n");
		}
	}
}


void ShellConsoleBase::__switch_envi(const std::string & env){
	int ind = -1;
	if (env.size() > 0 && std::all_of(env.begin(), env.end(), shell_is_digit)){
		ind = std::atoi(env.c_str());
	}
	if (ind >= 1 && ind <= (int)envs_.size()){
		cur_env_ = envs_[ind - 1];
	}
	else{
		auto it = std::find(envs_.begin(), envs_.end(), env);
		if (it == envs_.end()){
			printf(">>> unrecognized env/client %s.\n >>> please use [show] command to see all envs/clients.\n", env.c_str());
		}
		else{
			cur_env_ = env;
		}
	}
}





