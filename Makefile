# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tokino <tokino@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/30 15:58:20 by rgeny             #+#    #+#              #
#    Updated: 2022/01/06 22:26:07 by buschiix         ###   ########.fr        #
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

CC				= cc
FLAG			= $(DEPF) -g #-Wall -Werror -Wextra
OBJ_FLAG		= $(INCLUDES) $(PROMPTF) $(PATH_BUILTINF)
LIBF			= -lreadline
DEPF			= -MMD
PATHF			= 
INCLUDES		= -I$(INCLUDES_DIR)
PROMPTF			= -D PROMPT=$(VPROMPT)
VPROMPT			= \"$(shell whoami)@$(shell hostname -s):\"
PATH_BUILTINF	= -D PATH_BUILTIN=\"$(shell pwd)/$(BUILTIN_DIR)\"
VPATH_BUILTIN	= $(shell pwd)

SRC_DIR			= srcs/
ENV_DIR			= $(SRC_DIR)env/
LEXER_DIR		= $(SRC_DIR)lexer/
MEM_DIR			= $(SRC_DIR)mem/
STR_DIR			= $(SRC_DIR)str/
UTILS_DIR		= $(SRC_DIR)utils/
GLOBAL_DIR		= $(SRC_DIR)global/
EXPANDER_DIR	= $(SRC_DIR)expander/
EXE_DIR			= $(SRC_DIR)exe/
PARSING_DIR		= $(SRC_DIR)parsing/
PRINT_DIR		= $(SRC_DIR)print/
BUILTIN_DIR		= $(SRC_DIR)builtin/
OBJ_DIR			= objs
INCLUDES_DIR	= includes/

VPATH			= $(SRC_DIR) $(ENV_DIR) $(MEM_DIR) $(STR_DIR) $(UTILS_DIR) $(GLOBAL_DIR) $(EXPANDER_DIR) $(EXE_DIR) $(PARSING_DIR) $(LEXER_DIR) $(PRINT_DIR) $(BUILTIN_DIR)

SRC				= $(addsuffix .c,			main \
					$(addprefix env_,		del find init new print assign switch new_) \
					$(addprefix utils_,		bzero calloc min itoa ato isdigit readline is_in_charset) \
					$(addprefix mem_,		cpy set) \
					$(addprefix global_,	pwd) \
					$(addprefix expander_,	env) \
					$(addprefix exe_,		builtin out_process) \
					$(addprefix parsing_,	path) \
					$(addprefix lexer_,		lex token token_constructor print_tokens get_char_type free_tokens) \
					$(addprefix str_,		cmp len ndup split join free printfd split_first) \
					$(addprefix print_,		error) \
					$(addprefix builtin_,	cd exit export unset echo) \
					$(SRC_BUILTIN))

OBJ				= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
DEP				= $(OBJ:.o=.d)

EXE				= minishell

# **************************************************************************** #
# ******************************* Compilation ******************************** #
# **************************************************************************** #

all				: $(EXE) #builtin

$(EXE)			: $(OBJ)
				$(CC) $(FLAG) $^ -o $@ $(LIBF)

$(OBJ_DIR)/%.o	: %.c
				$(NEW_DIR) $(OBJ_DIR)
				$(CC) $(FLAG) -c $< $(OBJ_FLAG) -o $@

valgrind		: all
				$(VALGRIND) $(VALGRINDF) ./$(EXE)

envi			: all	
				$(ENV) $(VALGRIND) $(VALGRINDF) ./$(EXE)

clean			:
				$(RM) $(OBJ_DIR)

fclean			: clean
				$(RM) $(EXE)

re				: fclean all

-include $(DEP)

.PHONY	: all valgrind envi clean fclean re
