NAME = philo
CFLAGS = -Wall -Wextra -Werror -g
CC = cc
RED = '\033[1;31m'
BLUE ='\033[1;34m'
DEF_COLOR = '\033[0;39m'

VPATH = src/

SRCS = philo.c \
		parsing.c \
		monitoring.c \
		utils.c
OBJS = $(SRCS:.c=.o)
OBJDIR = objs/
OBJS_PATH = $(addprefix $(OBJDIR), $(OBJS))

$(OBJDIR)%.o: %.c
			@mkdir -p $(dir $@)
			@cc -c $< -o $@ $(CFLAGS)

$(NAME):	$(OBJS_PATH)
			@echo $(BLUE)"Compiling $(NAME)..."$(DEF_COLOR)
			@cc $(OBJS_PATH) -o $(NAME)

all:		$(NAME)

clean:
			@echo $(RED)"Cleaning object files..."$(DEF_COLOR)
			@rm -rf $(OBJDIR)

fclean:		clean
			@echo $(RED)"Cleaning executable files..."$(DEF_COLOR)
			@rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re