#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while(true){
    std::cout << "$ ";
    std::string command;
    std::getline(std::cin, command);
    if(command == "exit"){
      break;
    }
    else if(command.substr(0,4) == "echo "){
      std::cout << command.substr(5) << std::endl;
    }
    else if(command.substr(0,4) == "type "){
      std::string command_to_be_checked;
      command_to_be_checked = command.substr(command.substr(5).find(" ") - 5);
      if(command_to_be_checked == "echo"){
        std::cout << "echo is a shell builtin" << std::endl;
      }
      else if(command_to_be_checked == "type"){
        std::cout << "type is a shell builtin" << std::endl;
      }
      else if(command_to_be_checked == "exit"){
        std::cout << "exit is a shell builtin" << std::endl;
      }
      else{
        std::cout << command_to_be_checked << "invalid_command: not found" << std::endl;
      }
    }
    else{
      std::cout << command << ": command not found" << std::endl;
    }
  }

}
