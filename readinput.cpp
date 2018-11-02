#include "readinput.h"
#include <stdio.h>  /// printf
#include <iostream>

std::string shell_expect_a_command(std::string client, const std::string msg){
	printf("[Admin]%s:%s$ ", client.c_str(), msg.c_str());
	std::string cmd_str;
	char c;

	std::cin >> std::noskipws >> c;
	while (shell_iswhitespace(c)){
		if (c == '\n')	printf("[Admin]%s:%s$ ", client.c_str(), msg.c_str());
		std::cin >> std::noskipws >> c;
	}

	std::getline(std::cin, cmd_str);
	cmd_str.insert(cmd_str.begin(), c);

	return cmd_str;
}

std::string shell_expect_an_input(const std::string msg){
	printf("%s: ", msg.c_str());
	std::string cmd_str;
	char c;

	std::cin >> std::noskipws >> c;
	while (shell_iswhitespace(c)){
		if (c == '\n')	printf("%s: ", msg.c_str());
		std::cin >> std::noskipws >> c;
	}

	std::getline(std::cin, cmd_str);
	cmd_str.insert(cmd_str.begin(), c);
	return cmd_str;
}



