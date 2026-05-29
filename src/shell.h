#pragma once

#include <string>
#include <vector>

namespace shell {

std::vector<std::string> split_words(const std::string& text);
bool is_builtin(const std::string& command);
std::string find_executable_in_path(const std::string& command);
void handle_echo(const std::vector<std::string>& args);
void handle_type(const std::vector<std::string>& args);
int run();

} // namespace shell
