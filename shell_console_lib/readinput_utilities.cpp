#include "readinput.h"

#include <algorithm>

std::string &shell_ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), shell_isnonwhitespace));
	return s;
}

std::string &shell_rtrim(std::string &s) {
	if (s.empty())return s;
	s.erase(std::find_if(s.rbegin(), s.rend(), shell_isnonwhitespace).base(), s.end());
	return s;
}

std::string &shell_trim(std::string &s){
	return shell_rtrim(shell_ltrim(s));
}