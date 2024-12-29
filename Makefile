CC          = cc
CFLAGS      = -Wall -Wextra -Werror #-g -fsanitize=address
XFLAGS      = -lreadline -lncurses
NAME        = minishell
SOURCE_FILES =  main.c parsing/lexical.c parsing/new_token.c parsing/quotes.c\
				parsing/redirection.c parsing/env.c\
				parsing/expand.c parsing/syntax.c parsing/organize_cmd.c\
				parsing/final_commande.c parsing/heredoc.c parsing/signales.c\
				parsing/more_analyse.c\
				parsing/heredoc2.c parsing/array.c parsing/analyse_util.c\
				parsing/analyse_utils2.c parsing/lexical_utils.c parsing/organize_utils.c\
				parsing/quotes_utils.c parsing/syntax_util.c\
				execution/execution.c execution/redirection.c execution/pipe.c \
				execution/builtins/basic_list.c execution/builtins/builtins.c execution/builtins/cd.c execution/builtins/echo.c \
				execution/builtins/env.c execution/builtins/exit.c execution/builtins/export.c execution/builtins/pwd.c \
				execution/builtins/unset.c execution/utils.c execution/builtins/basic_list_1.c execution/builtins/basic_list_2.c \
				execution/execution_utils.c execution/pipe_handle_error.c
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

#parsing/utils1.c parsing/dollar.c\
				parsing/fd.c parsing/heredoc2.c parsing/analyse2.c\
				parsing/remove_quotes.c parsing/syntax2.c\