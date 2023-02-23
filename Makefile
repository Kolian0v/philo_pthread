#r:
#	gcc main.c utils.c exit.c -lmlx -framework OpenGl -framework Appkit -g -Wall -Wextra -Werror 
#	./a.out 4 510 200 200

# -fsanitize=address -g -Wall -Wextra -Werror`


NAME = philo
NAME2 = philo_bonus
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRCS =		main.c\
			exit.c\
			utils.c\
			#philo.h
SRCS_B =	main_bonus.c\
			exit_bonus.c\
			utils_bonus.c
OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $<

all:	$(NAME)

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(SRCS) -o $(NAME)
bonus: $(OBJS_B)
		$(CC) $(FLAGS) $(SRCS) -o $(NAME2)
		
clean:
		rm -f $(OBJS) $(OBJS_B) a.out

fclean:		clean
		rm -f $(NAME) $(NAME2)

re:		fclean all

.PHONY: all clean fclean re bonus
