# Shell Project Architecture

This repository contains a simple POSIX-style shell written in C++.
The implementation is intentionally small so it is easy to read, extend, and learn from.

## Core files

- `src/main.cpp`
  - The program entry point.
  - Calls `shell::run()` to start the interactive shell.

- `src/shell.cpp`
  - Contains the shell runtime loop and command behavior.
  - Reads input, splits words, handles builtins, and runs external commands.

- `src/shell.h`
  - Declares the public shell functions used by `main.cpp`.

- `CMakeLists.txt`
  - Configures the project build.
  - Builds `shell` from the sources in `src/`.

- `your_program.sh`
  - Helper script for local execution in Linux-like environments.

## Shell behavior

The shell implements a simple command REPL:

1. Print a prompt: `$ `
2. Read a line from standard input
3. Split the line into separate words
4. If the command is a builtin, execute it directly
5. Otherwise, search for an executable in `$PATH`
6. Run the executable in a child process with `fork()` and `execv()`
7. Wait for the child process to exit

## Builtin commands

- `echo`: prints the command arguments
- `type`: reports whether a command is a builtin or an external executable
- `exit`: stops the shell

## External command launch

The shell converts `std::vector<std::string>` arguments to a `char*` array and calls `execv()` in the child process.
The parent process uses `waitpid()` to wait for the child to finish.

## Extending the shell

This project is a good starting point for adding more features:

- `cd` and `pwd`
- command history and rehearsal
- quoting and escaping
- piping and redirection
- environment variable expansion
- exit status handling for external commands

## Concepts covered

- `std::stringstream`
  - Used to parse the command line into individual words.
  - Converts raw input into tokens for the shell to process.

- `std::vector<std::string>`
  - Stores parsed command arguments dynamically.
  - Makes it easy to collect and iterate over shell arguments.

- `fork()`
  - Creates a new child process from the running shell.
  - Parent continues the shell loop, child executes the external program.

- `access()`
  - Checks whether a file exists and can be executed.
  - Used to verify every candidate path in `$PATH`.

- `execv()` / `execvp()`
  - Replace the current process image with a new program.
  - `execv()` requires a full path and explicit argument array.
  - `execvp()` searches `$PATH` automatically.

- `waitpid()`
  - Waits for the child process to finish.
  - Allows the shell to capture the exit status and continue.

- `strerror(errno)`
  - Converts error codes into readable messages.
  - Used for reporting why `fork()` or `exec` failed.

- `$PATH` handling
  - The shell searches directories listed in `PATH`.
  - This is how it finds programs like `ls`, `cat`, or other commands.

- Builtin command detection
  - The shell distinguishes between builtins and external programs.
  - Builtins are executed directly without forking.

- C++/C interoperability
  - The shell converts `std::string` into `char*` pointers for `execv()`.
  - This bridges modern C++ containers with POSIX system calls.

