NAME =	pipex

CC = cc
CFLAGS =	-Wall -Wextra -Werror
RM =		rm -rf

SRC_DIR =		./src/
SRC_DIR_BONUS =	./src_bonus/
OBJ_DIR =		./obj/
OBJ_DIR_BONUS =	./obj_bonus/
INC_DIR =		./includes/
PRINTF_DIR	=	./printf/

SRC_LIST =		main.c \
				utils.c \
				ft_split.c \
				ft_strjoin.c \
				ft_strncmp.c \
				ft_sstrlen.c \
				errors.c \
				children.c \
				paths.c

SRC_LIST_BONUS =	main_bonus.c \
					errors.c \
					ft_sstrlen.c \
					utils.c \
					ft_split.c \
					paths.c \
					cmd.c

OBJ_LIST =			$(SRC:%.c=%.o)
OBJ_LIST_BONUS =	$(SRC_BONUS:%.c=%.o)

HEADERS_LIST =	pipex.h \
				error.h

HEADERS_LIST_BONUS =	pipex_bonus.h \
						error.h

SRC =		$(addprefix $(SRC_DIR), $(SRC_LIST))
SRC_BONUS =	$(addprefix $(SRC_DIR_BONUS), $(SRC_LIST_BONUS))
OBJ =		$(addprefix $(OBJ_DIR), $(notdir $(OBJ_LIST)))
OBJ_BONUS =	$(addprefix $(OBJ_DIR_BONUS), $(notdir $(OBJ_LIST_BONUS)))
HEADERS =	$(addprefix $(INC_DIR), $(HEADERS_LIST))
HEADERS_BONUS =	$(addprefix $(INC_DIR), $(HEADERS_LIST_BONUS))
PRINTF	=	$(addprefix $(PRINTF_DIR), libftprintf.a)

.PHONY: all clean fclean re bonus

all:	$(PRINTF) $(NAME)

$(PRINTF):
		make -C ./printf/

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(PRINTF) -o $(NAME)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)

$(OBJ_DIR_BONUS):
		mkdir $(OBJ_DIR_BONUS)
	
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADERS) | $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)%.o:	$(SRC_DIR_BONUS)%.c $(HEADERS_BONUS) | $(OBJ_DIR_BONUS)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)

fclean:	clean
		$(RM) $(NAME) $(PRINTF)


bonus:	$(OBJ_BONUS)
		$(CC) $(CFLAGS) $(OBJ_BONUS) $(PRINTF) -o $(NAME)



# $(NAME_BONUS):	$(OBJ_BONUS)
# 		$(CC) $(CFLAGS) $(OBJ_BONUS) $(PRINTF) -o $(NAME_BONUS)

# $(OBJ_DIR_BONUS):
# 		@mkdir $(OBJ_DIR_BONUS)

# $(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c $(HEADERS_BONUS) | $(OBJ_DIR_BONUS)
# 		$(CC) $(CFLAGS) -c $< -o $@


re:		fclean $(OBJ_DIR) all