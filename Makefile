# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tokino <tokino@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/30 15:58:20 by rgeny             #+#    #+#              #
#    Updated: 2022/02/01 19:31:59 by tokino           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# ********************************** format ********************************** #
# **************************************************************************** #
DEFAULT			= "\033[00m"
BOLD_BLUE		= "\033[01m\033[34m"
BOLD_CYAN		= "\033[01m\033[36m"

# **************************************************************************** #
# ************************************ cmd *********************************** #
# **************************************************************************** #

# ******************************** Compilation ******************************* #
CC				= cc

# ******************************** COMPIL FLAG ******************************* #
COMPILF			= $(DEPF) -g #-Wall -Werror -Wextra
LIBF			= -lreadline
DEPF			= -MMD

# ********************************** OBJ FLAG ******************************** #
OBJF			= $(INCLUDESF) $(PROMPTF)
INCLUDESF		= -I$(INCLUDES_DIR)
PROMPTF			= -D PROMPT=$(VPROMPT)
VPROMPT			= \"$(BOLD_CYAN)$(shell whoami)$(DEFAULT):$(BOLD_BLUE)\"

# ******************************* Valgrind flag ****************************** #
VALGRIND		= valgrind
VALGRINDF		= --trace-children=yes --suppressions=$(IGNORE_FILE) --leak-check=full --show-leak-kinds=all
ENV				= env -i
IGNORE_FILE		= $(shell pwd)/ignoreliberror

# *********************************** others ********************************* #
RM				= rm -rf
NEW_DIR			= mkdir -p



# **************************************************************************** #
# ********************************* Minishell ******************************** #
# **************************************************************************** #

# ********************************* Directory ******************************** #
SRC_DIR			= srcs/
ENV_DIR			= $(SRC_DIR)env/
LEXER_DIR		= $(SRC_DIR)lexer/
PARSER_DIR		= $(SRC_DIR)parser/
CLEANER_DIR		= $(SRC_DIR)cleaner/
MEM_DIR			= $(SRC_DIR)mem/
STR_DIR			= $(SRC_DIR)str/
UTILS_DIR		= $(SRC_DIR)utils/
GLOBAL_DIR		= $(SRC_DIR)global/
EXPANDER_DIR	= $(SRC_DIR)expander/
ASTERISK_DIR	= $(EXPANDER_DIR)asterisk/
EXE_DIR			= $(SRC_DIR)exe/
PRINT_DIR		= $(SRC_DIR)print/
BUILTIN_DIR		= $(SRC_DIR)builtin/
SIGNAL_DIR		= $(SRC_DIR)signal/
LST_DIR			= $(SRC_DIR)lst/
AST_DIR			= $(SRC_DIR)ast/
OBJ_DIR			= objs
INCLUDES_DIR	= includes/

VPATH			= $(SRC_DIR) $(ENV_DIR) $(MEM_DIR) $(STR_DIR) $(UTILS_DIR) $(GLOBAL_DIR)
VPATH			+=$(EXPANDER_DIR) $(EXE_DIR) $(LEXER_DIR) $(PRINT_DIR) $(LST_DIR) $(AST_DIR)
VPATH			+=$(BUILTIN_DIR) $(SIGNAL_DIR) $(ASTERISK_DIR) $(CLEANER_DIR) $(PARSER_DIR)

# *********************************** sources ******************************** #

SRC				= $(addsuffix .c,			main \
					$(addprefix env_,		del find init new print assign switch new_) \
					$(addprefix utils_,		bzero calloc min max itoa ato quicksort is) \
					$(addprefix mem_,		cpy set) \
					$(addprefix expander_,	var path heredoc main) \
					$(addprefix asterisk_,	main dir_list) \
					$(addprefix exe_,		builtin out_process readline main redir pipe cmd) \
					$(addprefix lexer_,		lex token token_constructor print_tokens get_char_type free_tokens) \
					$(addprefix parser_,	tokens print n_create n_command n_separator free_ast) \
					$(addprefix cleaner_,	all) \
					$(addprefix str_,		cmp len dup split join free split_first) \
					$(addprefix print_,		error fd) \
					$(addprefix builtin_,	cd exit export unset echo env pwd) \
					$(addprefix signal_,	current fork ignore) \
					$(addprefix lst_,		carg) \
					$(addprefix ast_,		fancy_printer asciitree_builder set_profiles set_edge_length print_level)\
					$(SRC_BUILTIN))

# *********************************** others ********************************* #
OBJ				= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
DEP				= $(OBJ:.o=.d)
NAME			= minishell



# **************************************************************************** #
# ******************************* Compilation ******************************** #
# **************************************************************************** #

all				: $(NAME)

$(NAME)			: $(OBJ)
				$(CC) $(COMPILEF) $^ -o $@ $(LIBF)

$(OBJ_DIR)/%.o	: %.c
				$(NEW_DIR) $(OBJ_DIR)
				$(CC) $(COMPILF) -c $< $(OBJF) -o $@

valgrind		: all
				$(VALGRIND) $(VALGRINDF) ./$(NAME)

envi			: all	
				$(ENV) $(VALGRIND) $(VALGRINDF) ./$(NAME)

clean			:
				$(RM) $(OBJ_DIR)

fclean			: clean
				$(RM) $(NAME)

re				: fclean all

-include $(DEP)

.PHONY	: all valgrind envi clean fclean re
