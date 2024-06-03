NAME = philo_bonus
CFLAGS = -Wall -Wextra -Werror
CC = cc
FILES = $(shell find . -type f -name "*.c" | wc -l | sed 's/^[[:space:]]*//;s/[[:space:]]*$$//')
CALC = $(shell echo $$((($(COUNT) * 100) / $(FILES))))
RESETLINE = \r\033[K
BLUE = \033[1;34m
YELLOW = \033[0;33m
RED = \033[0;31m
DEF_COLOR = \033[0m
COUNT = 1

VPATH = src/

SRCS = philo_bonus.c \
		parsing_bonus.c \
		monitoring_bonus.c \
		utils_bonus.c
OBJS = $(SRCS:.c=.o)
OBJDIR = objs/
OBJS_PATH = $(addprefix $(OBJDIR), $(OBJS))

$(OBJDIR)%.o: %.c
			@mkdir -p $(dir $@)
			@cc -c $< -o $@ $(CFLAGS)
			@echo "$(RESETLINE)$(BLUE)$@ $(COUNT)/$(FILES) $(CALC)/100%$(DEF_COLOR)\c"
			@if [ $(COUNT) -eq $(FILES) ]; then echo ""; fi
			$(eval COUNT := $(shell echo $$(($(COUNT) + 1))))

$(NAME):	msg_mand $(OBJS_PATH)
			@cc $(OBJS_PATH) -o $(NAME) -fsanitize=address

all:		$(NAME)

clean:
			@echo $(RED)"Cleaning object files..."$(DEF_COLOR)
			@rm -rf $(OBJDIR)

fclean:		clean
			@echo $(RED)"Cleaning executable files..."$(DEF_COLOR)
			@rm -f $(NAME)

re:			fclean all

msg_mand:
			@echo "$(YELLOW)Compiling Philosopher Mandotory$(DEF_COLOR)"

.PHONY: all clean fclean re