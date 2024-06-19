#----		Project		----#
NAME		=	philosophers

#----		Compiler		----#
CC			=	clang
CC_FLAGS	=	-Wall -Wextra -Werror

#----		Commands		----#
RM			=	rm -rf

#----		Directories		----#
OBJ_DIR		=	.objFiles
SRC_DIR		=	srcs
INC_DIR		=	includes

#----		Files			----#
SRC_FILES	:=  $(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES	:=  $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
INC_FILES	:=  $(wildcard $(INC_DIR)/*.h)

#----		Colors			----#
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
RESET		=	\e[0m

#----		Progress bar	----#
TOTAL		:=  $(words $(SRC_FILES))
COUNT		:=  0

#----		Library			----#


.PHONY: all clean fclean re

#----		Rules			----#
all: $(LIBFT) $(NAME)

$(NAME): $(OBJ_FILES)
	 @$(CC) $(OBJ_FILES) -o $(NAME)
	 @printf "\n\n$(GREEN) - Executable ready: $(NAME)\n$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	 @mkdir -p $(dir $@)
	 @$(CC) $(CC_FLAGS) -I $(INC_DIR) -c $< -o $@
	 @$(eval COUNT=$(shell expr $(COUNT) + 1))
	 @$(eval PERCENT=$(shell expr $(COUNT) \* 100 / $(TOTAL)))
	 @printf "$(GREEN) - Compiling: [%-0s] %d%%$(RESET)\r" "$$(printf '▉%.0s' $$(seq 1 $$(expr $(PERCENT) \* 50 / 100)))" $(PERCENT)

$(LIBFT):
	 @make -C $(LIBFT_DIR)

clean:
	 @$(RM) $(OBJ_DIR)
	 @printf "$(YELLOW) - Object files removed.\n$(RESET)"

fclean: clean
	 @$(RM) $(NAME)
	 @printf "$(YELLOW) - Executable removed: $(NAME)\n\n$(RESET)"

re: fclean all