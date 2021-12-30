CC				= cc
FLAG			= -g $(DEPF) -Wall -Werror -Wextra
LIBF			= -lreadline
DEPF			= -MMD
INCLUDES		= -Iincludes/

SRC_DIR			= srcs/
ENV_DIR			= $(SRC_DIR)env/
MEM_DIR			= $(SRC_DIR)mem/
STR_DIR			= $(SRC_DIR)str/
UTILS_DIR		= $(SRC_DIR)utils/
OBJ_DIR			= objs

VPATH			= $(SRC_DIR) $(ENV_DIR) $(MEM_DIR) $(STR_DIR) $(UTILS_DIR)

SRC				= $(addsuffix .c,		main \
					$(addprefix env_,	del find init new print assign switch export) \
					$(addprefix str_,	cmp len ndup split join free) \
					$(addprefix utils_,	bzero calloc min itoa atoi) \
					$(addprefix mem_,	cpy set))
OBJ				= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
DEP				= $(OBJ:.o=.d)
EXE				= minishell

all				: $(EXE)

$(EXE)			: $(OBJ)
				$(CC) $(FLAG) $^ -o $@ $(LIBF)

$(OBJ_DIR)/%.o	: %.c
				mkdir -p $(OBJ_DIR)
				$(CC) $(FLAG) -c $< $(INCLUDES) -o $@

valgrind		: all
				valgrind --trace-children=yes --suppressions=./ignoreliberror --leak-check=full --show-leak-kinds=all ./$(EXE)

clean			:
				rm -rf $(OBJ_DIR)

fclean			: clean
				rm $(EXE)

re				: fclean all

-include $(DEP)

.PHONY	: all clean fclean re
