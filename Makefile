# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tokino <tokino@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/30 15:58:20 by rgeny             #+#    #+#              #
#    Updated: 2022/02/13 12:24:53 by rgeny            ###   ########.fr        #
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
COMPILEF		= $(DEPF) -g #-Wall -Werror -Wextra
LIBF			= -lreadline
DEPF			= -MMD

# ********************************** OBJ FLAG ******************************** #
OBJF			= $(INCLUDESF) $(PROMPTF)
INCLUDESF		= -I$(INCLUDES_DIR) -I$(TYPEDEF_DIR) -I$(DEFINE_DIR)
#PROMPTF		= -D PROMPT=$(VPROMPT)
#VPROMPT		= \"$(BOLD_CYAN)$(shell whoami)$(DEFAULT):$(BOLD_BLUE)\"

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
OBJ_DIR			= objs
INCLUDES_DIR	= includes/
TYPEDEF_DIR		= typedef/
DEFINE_DIR		= define/
SRC_DIR			= srcs/
ENV_DIR			= $(SRC_DIR)env/
COMMON_DIR		= $(SRC_DIR)common/
STR_DIR			= $(COMMON_DIR)str/
MEM_DIR			= $(COMMON_DIR)mem/
IS_DIR			= $(COMMON_DIR)is/
EXPANDER_DIR	= $(SRC_DIR)expander/
EXE_DIR			= $(SRC_DIR)exe/
LEXER_DIR		= $(SRC_DIR)lexer/
REDIR_DIR		= $(SRC_DIR)redir/
BUILTIN_DIR		= $(SRC_DIR)builtin/
SIGNAL_DIR		= $(SRC_DIR)signal/
ASTERISK_DIR	= $(EXPANDER_DIR)asterisk/
CLEANER_DIR		= $(SRC_DIR)cleaner/
PARSER_DIR		= $(SRC_DIR)parser/
AST_BUILDER_DIR = $(PARSER_DIR)ast_builder/
AST_PRINTER_DIR	= $(PARSER_DIR)ast_printer/
SPACE_DIR		= $(EXPANDER_DIR)space/
CARG_DIR		= $(SRC_DIR)carg/

VPATH			= $(SRC_DIR) $(ENV_DIR) $(MEM_DIR) $(STR_DIR) $(COMMON_DIR) $(GLOBAL_DIR)
VPATH			+=$(EXPANDER_DIR) $(EXE_DIR) $(LEXER_DIR) $(REDIR_DIR) $(IS_DIR) 
VPATH			+=$(BUILTIN_DIR) $(SIGNAL_DIR) $(ASTERISK_DIR) $(CLEANER_DIR) 
VPATH			+=$(PARSER_DIR) $(AST_BUILDER_DIR) $(AST_PRINTER_DIR) $(SPACE_DIR) $(CARG_DIR)

# *********************************** sources ******************************** #

SRC				= $(addsuffix .c,					main \
					$(addprefix env_,				del find init new assign switch) \
					$(addprefix mem_,				cpy set) \
					$(addprefix parser_,			free_ast main) \
						$(addprefix ast_builder_,	command create_node is_given_token \
													main pipeline_list pipeline) \
						$(addprefix ast_printer_,	main asciitree_builder label_builder \
													set_profiles set_edge_length level)\
					$(addprefix cleaner_,			all) \
					$(addprefix str_,				cmp len dup split join free split_first \
													print first_dif) \
					$(addprefix builtin_,			cd exit export unset echo env pwd) \
					$(addprefix common_,			bzero calloc min itoa ato quicksort \
													interactive max error fd) \
					$(addprefix is_,				alnum digit in_charset valid_name) \
					$(addprefix expander_,			args redir var path heredoc quote \
						$(addprefix space_,			args redir tool)) \
						$(addprefix asterisk_,		main dir_list cmp) \
					$(addprefix exe_,				builtin out_process readline main \
													redir pipe cmd subshell) \
					$(addprefix lexer_,				lex token token_constructor \
													print_tokens get_char_type free_tokens) \
					$(addprefix signal_,			current fork ignore heredoc) \
					$(addprefix redir_,				add) \
					$(addprefix carg_,				add del new switch))

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
				$(CC) $(COMPILEF) -c $< $(OBJF) -o $@

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
