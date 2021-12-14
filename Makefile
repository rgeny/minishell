CC				= cc
FLAG			= $(DEPF) #-Wall -Werror -Wextra
LIB				= -lreadline
DEPF			= -MMD
OBJ_DIR			= objs
LIBFT_DIR		= libft/
VPATH			= $(LIBFT_DIR)
SRC				= $(addsuffix .c,	main)
OBJ				= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
DEP				= $(OBJ:.o=.d)
EXE				= minishell
LIBFT			= $(LIBFT_DIR)libft.a

all				: $(EXE)

$(EXE)			: $(OBJ) $(LIBFT)
				$(CC) $(FLAG) $^ -o $@ $(LIB)

$(LIBFT)		:
				make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o	: %.c
				mkdir -p $(OBJ_DIR)
				$(CC) $(FLAG) -c $< -o $@

clean			:
				rm -rf $(OBJ_DIR)
				make clean -C $(LIBFT_DIR)

fclean			: clean
				rm $(EXE) $(LIBFT)

re				: fclean all

-include $(DEP)

.PHONY	: all clean fclean re
