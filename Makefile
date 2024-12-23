CC          = cc
CFLAGS      = -Wall -Wextra -Werror #-g -fsanitize=address
XFLAGS      = -lreadline -lncurses
NAME        = minishell
SOURCE_FILES = parsing/lexical.c parsing/new_token.c parsing/quotes.c\
				parsing/redirection.c parsing/main.c parsing/env.c\
				parsing/expand.c parsing/syntax.c parsing/organize_cmd.c\
				parsing/final_commande.c parsing/heredoc.c parsing/signales.c\
				parsing/more_analyse.c\
				execution/execution.c execution/redirection.c execution/pipe.c \
				execution/builtins/basic_list.c execution/builtins/builtins.c execution/builtins/cd.c execution/builtins/echo.c \
				execution/builtins/env.c execution/builtins/exit.c execution/builtins/export.c execution/builtins/pwd.c \
				execution/builtins/unset.c execution/utils.c
# HEADER      = include/parsing.h
LIBFT       = libft/libft.a
OBJECTS     = $(SOURCE_FILES:.c=.o)

%.o : %.c 
	@$(CC) $(CFLAGS) -c -o $@ $<

all : $(NAME)

$(LIBFT):
	@make -C libft

$(NAME) : $(OBJECTS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(XFLAGS) $(LIBFT)
	@echo "\tThe minishell Program Is Created."

clean :
	@rm -rf $(OBJECTS)
	@echo "\tObject Files Are Removed."
	@make -C libft clean

fclean : clean
	@rm -rf $(NAME)
	@echo "\tThe Executable File Is Removed."
	@make -C libft fclean

re : fclean all

.PHONY : all clean fclean re
