#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#ifdef _WIN32
  #include <windows.h>
#else
  #include <unistd.h>
#endif

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while(true){
    std::cout << "$ ";
    std::string command;
    std::getline(std::cin, command);
    std::stringstream ss(command);

    ss >> command;

    if(command == "exit"){
      break;
    }
    else if(command == "echo "){
      std::string word;
      while(ss >> word){
        std::cout << word <<" ";
      std::cout << std::endl;
      }
    }
    else if(command == "type "){
      std::string command_to_be_checked;
      ss >> command_to_be_checked;
      std::vector<std::string> builtin_commands = {"echo", "type", "exit"};
      bool found = false;
      for(const auto& builtin_command : builtin_commands){
        if(command_to_be_checked == builtin_command){
          std::cout << command_to_be_checked << " is a shell builtin" << std::endl;
          found = true;
        }
      }
      if(!found){
        std::string path = std::getenv("PATH");
        std::stringstream ss_path(path);
        while(std::getline(ss_path, path, ":")){
          std::string full_path = path + "/"+ command_to_be_checked;
          #ifdef _WIN32
          DWORD attribs = GetFileAttributesA(full_path.c_str());
          if(attribs != INVALID_FILE_ATTRIBUTES && !(attribs & FILE_ATTRIBUTE_DIRECTORY)){
          #else
          if(access(full_path.c_str(), X_OK) == 0){
          #endif
            std::cout << command_to_be_checked << " is " << full_path << std::endl;
            found = true;
            break;
          }
        }
      }
      if(!found){
        std::cout << command_to_be_checked << ": not found" << std::endl;
      }
    }
    else{
      std::cout << command << ": command not found" << std::endl;
    }
  }

}
