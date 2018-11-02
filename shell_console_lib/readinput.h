#ifndef SHELL_READINPUT_H_20181101
#define SHELL_READINPUT_H_20181101

#include <string>

inline bool shell_iswhitespace(char c){return (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\v' == c || '\f' == c); }
inline bool shell_isnonwhitespace(char c){ return !(' ' == c || '\t' == c || '\n' == c || '\r' == c || '\v' == c || '\f' == c); }

std::string &shell_ltrim(std::string &s);
std::string &shell_rtrim(std::string &s);
std::string &shell_trim(std::string &s);

std::string shell_expect_a_command(std::string client, const std::string msg);
std::string shell_expect_an_input(const std::string msg);

#endif