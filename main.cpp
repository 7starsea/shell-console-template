#include "shell_console_lib/shell_console_base.h"

class ShellConsole : public ShellConsoleBase{
public:
    ShellConsole(): ShellConsoleBase(){}

    void process_command(const std::vector<std::string> & cmd_vec)override{
       printf("We are running cmd:%s\n", cmd_vec[0].c_str());
    }

    void print_help()override{
    }

    void log(const std::string & cmd_str)override{
    }
};

int main(int argc, const char* argv[]){
    ShellConsole console;
    console.wait_for_operation();
    return 0;
} 
