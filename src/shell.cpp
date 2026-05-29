#include "shell.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <unistd.h>

namespace shell {

namespace {

const std::vector<std::string> builtin_commands = {
  "echo",
  "type",
  "exit"
};

} // namespace

std::vector<std::string> split_words(const std::string& text) {
  std::vector<std::string> words;
  std::stringstream ss(text);
  std::string word;

  while (ss >> word) {
    words.push_back(word);
  }

  return words;
}

bool is_builtin(const std::string& command) {
  for (const auto& builtin : builtin_commands) {
    if (command == builtin) {
      return true;
    }
  }
  return false;
}

std::string find_executable_in_path(const std::string& command) {
  const char* path_env = std::getenv("PATH");
  if (path_env == nullptr) {
    return {};
  }

  std::string path = path_env;
  std::stringstream ss_path(path);
  std::string entry;

  while (std::getline(ss_path, entry, ':')) {
    std::string full_path = entry + "/" + command;
    if (access(full_path.c_str(), X_OK) == 0) {
      return full_path;
    }
  }

  return {};
}

void handle_echo(const std::vector<std::string>& args) {
  for (size_t i = 1; i < args.size(); ++i) {
    std::cout << args[i];
    if (i + 1 < args.size()) {
      std::cout << ' ';
    }
  }
  std::cout << std::endl;
}

void handle_type(const std::vector<std::string>& args) {
  if (args.size() < 2) {
    std::cout << "type: missing operand" << std::endl;
    return;
  }

  const std::string& command_to_check = args[1];
  if (is_builtin(command_to_check)) {
    std::cout << command_to_check << " is a shell builtin" << std::endl;
    return;
  }

  std::string executable = find_executable_in_path(command_to_check);
  if (!executable.empty()) {
    std::cout << command_to_check << " is " << executable << std::endl;
    return;
  }

  std::cout << command_to_check << ": not found" << std::endl;
}

int run() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true) {
    std::cout << "$ " << std::flush;

    std::string line;
    if (!std::getline(std::cin, line)) {
      break; // EOF or input error
    }

    std::vector<std::string> args = split_words(line);
    if (args.empty()) {
      continue; // ignore empty lines
    }

    const std::string& command = args[0];
    if (command == "exit") {
      break;
    }

    if (command == "echo") {
      handle_echo(args);
    } else if (command == "type") {
      handle_type(args);
    } else {
      std::cout << command << ": command not found" << std::endl;
    }
  }

  return 0;
}

} // namespace shell
