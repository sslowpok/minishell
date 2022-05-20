NAME	=	minishell

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

SRC_DIR	=	./src/
OBJ_DIR	=	./obj/
INC_DIR	=	./includes/
LIBFT_DIR	=	./libft/

SRC_LIST	=	main.c \
				cmd.c \
				errors.c \
				main_pipex.c \
				paths.c \
				utils.c \
				parser_lexer.c \
				parser_lexemes_to_bp.c \
				parser_utils1.c \
				parser_redir_utils.c \
				parser_block_process_clear.c \
				envp_parser_utils.c \
				envp_list_utils.c \
				parser_check_commands.c \
				parser_deal_quotes.c \
				builtins_echo.c \
				builtins_env.c \
				builtins_pwd.c \
				builtins_cd.c \
				builtins_cd_help.c \
				builtins_exit.c \
				builtins_exit_help.c 


OBJ_LIST	=	$(SRC:%.c=%.o)

HEADERS_LIST	=	minishell.h

SRC		=	$(addprefix $(SRC_DIR), $(SRC_LIST))
OBJ		=	$(addprefix $(OBJ_DIR), $(notdir $(OBJ_LIST)))
HEADERS	=	$(addprefix $(INC_DIR), $(HEADERS_LIST))
LIBFT	=	$(addprefix $(LIBFT_DIR), libft.a)

RL_INCLUDE  =   ~/.brew/opt/readline/include
RL_LIB      =   ~/.brew/opt/readline/lib

.PHONY:	all clean fclean re

all:	$(LIBFT) $(NAME)

$(LIBFT):
		make bonus -C ./libft/

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADERS) | $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ) Makefile
		$(CC) $(CFLAGS) -lreadline -L $(RL_LIB) -I $(RL_INCLUDE) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)

clean:
		@$(RM) $(OBJ_DIR)
		make clean -C ./libft/

fclean:	clean
		@$(RM) $(NAME) $(LIBFT)

re:	fclean $(OBJ_DIR) all