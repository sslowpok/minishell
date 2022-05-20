NAME	=	minishell

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

SRC	=	parser/envp_list_utils.c \
		parser/envp_parser_utils.c \
		parser/parser_block_process_clear.c \
		parser/parser_check_commands.c \
		parser/parser_lexemes_to_bp.c \
		parser/parser_deal_quotes.c \
		parser/parser_lexer.c \
		parser/parser_redir_utils.c \
		parser/parser_utils1.c \
		src/main.c \
		executor/executor_2.c \
		builtins/builtins_echo.c \
		builtins/builtins_env.c \
		builtins/builtins_pwd.c \
		builtins/ft_unset.c \
		builtins/ft_export.c \
		builtins/builtins_exit.c \
		builtins/builtins_exit_help.c \
		executor/signals.c \
		executor/commands.c \
		executor/redirects.c \
		executor/builtin_utils.c \
		executor/utils.c \
		builtins/builtins_cd.c \
		builtins/builtins_cd_help.c

HEADERS	=	includes/envp_parser.h \
			includes/error.h \
			includes/minishell.h \
			includes/parser.h

OBJ	=	$(SRC:.c=.o)

%.o:	%.c	$(HEADERS) Makefile
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)


#LD_FLAGS = -I /Library/Developer/CommandLineTools/SDKs/MacOSX12.3.sdk/usr/include/editline/readline.h

$(NAME):	$(OBJ)
		make bonus -C ./libft/
		$(CC) $(CFLAGS) $(LD_FLAGS) $(OBJ) ./libft/libft.a -o $(NAME) -lreadline

all:	$(NAME)

clean:
		$(RM) $(OBJ)
		make clean -C ./libft/

fclean:	clean
		$(RM) $(NAME)

re:	fclean all