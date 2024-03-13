CC = cc

SRCS_RAW =	philo.c\
			utils.c\
			parsing.c\
			monitoring.c\
			routine.c\
			structs.c\
			threads.c\
			time.c

OBJS_DIR = objs/

SRCS_DIR = ./

SRCS = $(SRCS_RAW)

OBJS = $(addprefix $(OBJS_DIR), $(SRCS_RAW:.c=.o))

FLAGS = -Wall -Wextra -Werror -g

NAME = philo

all: 
	@$(MAKE) --no-print-directory -j $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

bonus: all

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re install bonus
