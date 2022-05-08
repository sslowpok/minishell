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
		executor/executor_2.c

HEADERS	=	includes/envp_parser.h \
			includes/error.h \
			includes/minishell.h \
			includes/parser.h

OBJ	=	$(SRC:.c=.o)

%.o:	%.c	$(HEADERS) Makefile
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)


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