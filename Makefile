

NAME		=	threads


SRC_DIR		= 	src/
SRCS     := $(shell find $(SRC_DIR) -type f -name "*.c")

OBJ_DIR		= objs/
OBJS     := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))



CC			= gcc
FLAGS		= -Wall -Wextra -Werror
INC			=  -I includes/
THREADS		= -lpthread
RM			= rm -rf


DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;31m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
CLEAR = \033[0m
OKLOGO = \033[80G\033[32m[OK]\033[0m\n


# **************************************************************************** #

all:		$(NAME)


$(NAME):  $(OBJS)
	@echo "$(BLUE)COMPILING THREADS.$(CLEAR)"
	@$(CC) $(FLAGS) $(INC) $(OBJS) $(THREADS) -o $(NAME)
	@printf "\033[1;34m$(NAME)\033[25G\033[33mCompile $< $(OKLOGO)"
	@printf "\033[1;34m$(NAME)\033[25G\033[33mLinking $(OKLOGO)"
	@echo "$(MAGENTA)\tUsage: ./thread.hs <num_threads> <nums_per_thread>$(CLEAR)"
	@echo "$(GREEN)WORKER_THREADS COMPILED SUCCESSFUL!$(CLEAR)"
			
			
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@printf "$(GREEN)Compiled: $<$(CLEAR)\n"
			
			
clean:
			@echo "$(YELLOW)FILES REMOVED!$(DEF_COLOR)"
			@$(RM) $(OBJ_DIR)

fclean:		clean
			@$(RM)  $(NAME)
			@echo "$(RED)$(NAME) REMOVED!$(DEF_COLOR)"
			@echo "$(RED)$(NAME_CLIENT) REMOVED!$(DEF_COLOR)"
			@echo "$(RED)$(NAME_SERVER) REMOVED!$(DEF_COLOR)"

re:			fclean all

.PHONY:		all clean fclean re libft print