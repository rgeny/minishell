# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgeny <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/30 15:58:20 by rgeny             #+#    #+#              #
#    Updated: 2021/12/31 16:29:04 by rgeny            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
# ********************************* Minishell ******************************** #
# **************************************************************************** #
CC				= clang
FLAG			= $(DEPF) $(BUILTINF) #-g -Wall -Werror -Wextra
LIBF			= -lreadline
DEPF			= -MMD
INCLUDES		= -I$(INCLUDES_DIR)

SRC_DIR			= srcs/
ENV_DIR			= $(SRC_DIR)env/
MEM_DIR			= $(SRC_DIR)mem/
STR_DIR			= $(SRC_DIR)str/
UTILS_DIR		= $(SRC_DIR)utils/
OBJ_DIR			= objs
INCLUDES_DIR	= includes/

VPATH			= $(SRC_DIR) $(ENV_DIR) $(MEM_DIR) $(STR_DIR) $(UTILS_DIR)

SRC				= $(addsuffix .c,		main \
					$(addprefix env_,	del find init new print assign switch export unset _) \
					$(addprefix str_,	cmp len ndup split join free) \
					$(addprefix utils_,	bzero calloc min itoa atoi) \
					$(addprefix mem_,	cpy set))
OBJ				= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
DEP				= $(OBJ:.o=.d)
EXE				= minishell

# **************************************************************************** #
# ********************************** Builtin ********************************* #
# **************************************************************************** #

BUILTINF		= -D BUILTIN_PATH=\"$(PATH_DIR)$(BUILTIN_DIR)\"

PATH_DIR		= $(shell /usr/bin/pwd)/
BUILTIN_DIR		= builtin
SRC_BUILTIN_DIR	= $(SRC_DIR)builtin/

VPATH			+= $(SRC_BUILTIN_DIR)

SRC_ENV			= builtin_env.c
OBJ_ENV			= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_ENV))
OBJ_BUILTIN		= $(OBJ_ENV)
EXE_ENV			= $(BUILTIN_DIR)/env

# **************************************************************************** #
# ******************************* Compilation ******************************** #
# **************************************************************************** #

all				: $(EXE) builtin

$(EXE)			: $(OBJ)
				$(CC) $(FLAG) $^ -o $@ $(LIBF)

builtin			: $(OBJ_ENV)
				mkdir -p $(BUILTIN_DIR)/
				$(CC) $(FLAG) $(OBJ_ENV) -o  $(EXE_ENV)

$(OBJ_DIR)/%.o	: %.c
				mkdir -p $(OBJ_DIR)
				$(CC) $(FLAG) -c $< $(INCLUDES) -o $@

valgrind		: all
				valgrind --trace-children=yes --suppressions=./ignoreliberror --leak-check=full --show-leak-kinds=all ./$(EXE)

envi			: all	
				env -i valgrind --trace-children=yes --suppressions=./ignoreliberror --leak-check=full --show-leak-kinds=all ./$(EXE)

clean			:
				rm -rf $(OBJ_DIR)

fclean			: clean
				rm $(EXE)
				rm -rf $(BUILTIN_DIR)

re				: fclean all

-include $(DEP)

.PHONY	: all valgrind envi clean fclean re
