# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgeny <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/30 15:58:20 by rgeny             #+#    #+#              #
#    Updated: 2022/01/01 11:41:08 by rgeny            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# ************************************ cmd *********************************** #
# **************************************************************************** #

RM				= rm -rf
NEW_DIR			= mkdir -p
VALGRIND		= valgrind
VALGRINDF		= --trace-children=yes --suppressions=$(IGNORE_FILE) --leak-check=full --show-leak-kinds=all
ENV				= env -i
IGNORE_FILE		= $(shell pwd)/ignoreliberror

# **************************************************************************** #
# ********************************* Minishell ******************************** #
# **************************************************************************** #

CC				= clang
FLAG			= $(DEPF) -g #-Wall -Werror -Wextra
OBJ_FLAG		= $(INCLUDES) $(PROMPTF)
LIBF			= -lreadline
DEPF			= -MMD
INCLUDES		= -I$(INCLUDES_DIR)
PROMPTF			= -D PROMPT=$(VPROMPT)
VPROMPT			= \"$(shell whoami)@$(shell hostname -s):\"

SRC_DIR			= srcs/
ENV_DIR			= $(SRC_DIR)env/
MEM_DIR			= $(SRC_DIR)mem/
STR_DIR			= $(SRC_DIR)str/
UTILS_DIR		= $(SRC_DIR)utils/
GLOBAL_DIR		= $(SRC_DIR)global/
OBJ_DIR			= objs
INCLUDES_DIR	= includes/

VPATH			= $(SRC_DIR) $(ENV_DIR) $(MEM_DIR) $(STR_DIR) $(UTILS_DIR) $(GLOBAL_DIR)

SRC_STR			= $(addsuffix .c, $(addprefix str_, cmp len ndup split join free printerr printfd))
OBJ_STR			= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_STR))
SRC				= $(addsuffix .c,			main \
					$(addprefix env_,		del find init new print assign switch new_) \
					$(addprefix utils_,		bzero calloc min itoa ato isdigit readline) \
					$(addprefix mem_,		cpy set) \
					$(addprefix global_,	pwd) \
					$(SRC_BUILTIN))

OBJ				= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC)) $(OBJ_STR)
DEP				= $(OBJ:.o=.d)

EXE				= minishell

# **************************************************************************** #
# ********************************** Builtin ********************************* #
# **************************************************************************** #

PATH_DIR		= $(shell /usr/bin/pwd)/
BUILTIN_DIR		= builtin
SRC_BUILTIN_DIR	= $(SRC_DIR)builtin/

VPATH			+= $(SRC_BUILTIN_DIR)

SRC_BUILTIN		= $(addprefix builtin_, export unset exit cd)
SRC_ENV			= builtin_env.c
OBJ_ENV			= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_ENV))
SRC_ECHO		= $(addsuffix .c,builtin_echo str_cmp str_len)
OBJ_ECHO		= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_ECHO))
SRC_PWD			= $(addsuffix .c,builtin_pwd str_printfd str_printerr str_len global_pwd str_free str_split str_ndup utils_calloc utils_bzero utils_min str_cmp mem_cpy mem_set)
OBJ_PWD			= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_PWD))
OBJ_BUILTIN		= $(OBJ_ENV) $(OBJ_ECHO) $(OBJ_PWD)

EXE_ENV			= $(BUILTIN_DIR)/env
EXE_ECHO		= $(BUILTIN_DIR)/echo
EXE_PWD			= $(BUILTIN_DIR)/pwd

# **************************************************************************** #
# ******************************* Compilation ******************************** #
# **************************************************************************** #

all				: $(EXE) builtin

$(EXE)			: $(OBJ)
				$(CC) $(FLAG) $^ -o $@ $(LIBF)

builtin			: $(OBJ_BUILTIN)
				$(NEW_DIR) $(BUILTIN_DIR)/
				$(CC) $(FLAG) $(OBJ_ENV) -o $(EXE_ENV)
				$(CC) $(FLAG) $(OBJ_ECHO) -o $(EXE_ECHO)
				$(CC) $(FLAG) $(OBJ_PWD) -o $(EXE_PWD)

$(OBJ_DIR)/%.o	: %.c
				$(NEW_DIR) $(OBJ_DIR)
				$(CC) $(FLAG) -c $< $(OBJ_FLAG) -o $@

valgrind		: all
				$(VALGRIND) $(VALGRINDF)  ./$(EXE)

envi			: all	
				$(ENV) $(VALGRIND) $(VALGRINDF) ./$(EXE)

clean			:
				$(RM) $(OBJ_DIR)

fclean			: clean
				$(RM) $(EXE) $(BUILTIN_DIR)

re				: fclean all

-include $(DEP)

.PHONY	: all valgrind envi clean fclean re
