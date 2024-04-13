SRC			=	philos.c \
				dinner.c \
				put_it.c \
				atoint.c \
				errors.c \
				usleep.c \
				parsin.c \
				initia.c \
				single.c \
				monitor.c \
				utilss.c

GREEN		=	'\033[32m'
NONE		=	'\033[0m'
CC			=	cc
NAME		=	philo
HEADER		=	mand/srcs/philos.h mand/srcs/struct.h
OBJ			=	$(SRC:.c=.o)
CFLAGS		=	-Wall -Wextra -Werror -pthread -g -fsanitize=thread

all: $(NAME) clean

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN) "\n compilation done" $(NONE)

%.o: %.c philos.h struct.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(GREEN) "... Compiling\t$<\t[OK]" $(RESET)

clean:
	@rm -f $(OBJ)
	@echo $(GREEN) "clean done\n" $(NONE)

fclean: clean
	@rm -f $(NAME)
	@echo $(GREEN) "fclean done\n" $(NONE)

re: fclean all
	@echo $(GREEN) "re done\n" $(NONE)

.PHONY: clean
