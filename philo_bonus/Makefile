CC = cc

SRCS_RAW =	philo_bonus.c\
			utils_bonus.c\
			parsing_bonus.c\
			monitoring_bonus.c\
			routine_bonus.c\
			structs_bonus.c\
			threads_bonus.c\
			time_bonus.c\
			semaphores_bonus.c

OBJS_DIR = objs/

SRCS_DIR = ./

SRCS = $(SRCS_RAW)

OBJS = $(addprefix $(OBJS_DIR), $(SRCS_RAW:.c=.o))

FLAGS = -Wall -Wextra -Werror -g

NAME = philo_bonus

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
