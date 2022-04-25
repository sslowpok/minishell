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
				utils.c

OBJ_LIST	=	$(SRC:%.c=%.o)

HEADERS_LIST	=	minishell.h

SRC		=	$(addprefix $(SRC_DIR), $(SRC_LIST))
OBJ		=	$(addprefix $(OBJ_DIR), $(notdir $(OBJ_LIST)))
HEADERS	=	$(addprefix $(INC_DIR), $(HEADERS_LIST))
LIBFT	=	$(addprefix $(LIBFT_DIR), libft.a)

.PHONY:	all clean fclean re

all:	$(LIBFT) $(NAME)

$(LIBFT):
		make -C ./libft/

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADERS) | $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)

clean:
		@$(RM) $(OBJ_DIR)

fclean:	clean
		@$(RM) $(NAME) $(LIBFT)

re:	fclean $(OBJ_DIR) all