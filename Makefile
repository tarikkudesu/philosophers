SRC			=	$(addprefix mand/, \
				srcs/philos.c \
				help/put_it.c \
				help/atoint.c \
				help/errors.c \
				pars/parsin.c \
				srcs/initdata.c)

GREEN		=	'\033[32m'
NONE		=	'\033[0m'
CC			=	cc
NAME		=	philo
HEADER		=	mand/srcs/philos.h mand/srcs/struct.h
OBJ			=	$(SRC:.c=.o)
CFLAGS		=	-Wall -Wextra -Werror -g

all: $(NAME) clean

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN) "\n compilation done" $(NONE)

%.o: %.c mand/srcs/philos.h mand/srcs/struct.h
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
