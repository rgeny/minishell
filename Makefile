CC				= cc
FLAG			= $(DEPF)# -Wall -Werror -Wextra
LIBF			= -lreadline
DEPF			= -MMD
INCLUDES		= -Iincludes/

SRC_DIR			= srcs/
ENV_DIR			= $(SRC_DIR)env/
MEM_DIR			= $(SRC_DIR)mem/
STR_DIR			= $(SRC_DIR)str/
TOOL_DIR		= $(SRC_DIR)tool/
OBJ_DIR			= objs

VPATH			= $(SRC_DIR) $(ENV_DIR) $(MEM_DIR) $(STR_DIR) $(TOOL_DIR)

SRC				= $(addsuffix .c,		main \
					$(addprefix env_,	add free init new print) \
					$(addprefix str_,	cmp len ndup) \
										cpy set get_min split)
OBJ				= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
DEP				= $(OBJ:.o=.d)
EXE				= minishell

all				: $(EXE)

$(EXE)			: $(OBJ)
				$(CC) $(FLAG) $^ -o $@ $(LIBF)

$(OBJ_DIR)/%.o	: %.c
				mkdir -p $(OBJ_DIR)
				$(CC) $(FLAG) -c $< $(INCLUDES) -o $@

clean			:
				rm -rf $(OBJ_DIR)

fclean			: clean
				rm $(EXE)

re				: fclean all

-include $(DEP)

.PHONY	: all clean fclean re
