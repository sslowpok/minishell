# minishell
# Description
The objective of this project is to create a simple shell, just like a bash.
# Game rules

1. This shell does not handle unclosed quotes and specified symbols like '' or ';'
2. It has a working history like real bash
3. Implemented all kinds of redirections (">", "<" ">>", "<<")
4. Pipes are working like in real bash
5. Signals (ctrl-D, ctrl-C, ctrl-) working like in bash
6. Global virables are implemnted
7. "$?" (exit status) done

Builtins that are implemented without "execve()" function: \

1. echo (with -n flag)
2. cd without flags (with relatives and absolute path)
3. pwd whithout flags
4. env without flags
5. export without flags
6. unset without flags
7. exit without flags
