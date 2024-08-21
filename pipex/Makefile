NAME = pipex

CC = cc

CFLAGS =  -Wall -Wextra -fsanitize=address

RM = rm -rf

SRCS = 	main.c\
		utils.c\
		errors.c\

OBJS := ${SRCS:.c=.o} 

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

.o: .c
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJS)
	$(RM) $(NAME)

re : fclean all