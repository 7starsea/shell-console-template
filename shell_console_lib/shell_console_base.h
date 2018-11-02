#ifndef SHELL_CONSOLE_BASE_H_20181101
#define SHELL_CONSOLE_BASE_H_20181101
#include <string>
#include <map>
#include <vector>

inline bool shell_is_digit(char c){ return ('0' <= c && c <= '9'); }

void format_help_msg(const char * cmd, const char * help_msg, const std::vector<std::string> & examples);

/*
 * base commands: help/?, quit/exit/q, list/ls, switch/sw
 */
class  ShellConsoleBase{
public:
	ShellConsoleBase();
	///等待操作
	void wait_for_operation();

	void add_envi(const std::string & env);
	void remove_envi(const std::string & env);
	std::string current_envi();
public:
	virtual void process_command(const std::vector<std::string > & cmd_vec) {};
	virtual void print_help() {};
	virtual void log(const std::string & cmd_str){};
protected:
	std::string _expect_a_command(const std::string msg="");
	std::string _expect_an_input(const std::string msg = "");
	char _expect_a_yesorno(const std::string msg = "");
protected:
	std::vector<std::string> envs_;
	std::string cur_env_;
private:
	/// 显示所有的 environment
	void __display_all_envi();
	/// 切换 environment
	void __switch_envi(const std::string & env);
};


#endif
