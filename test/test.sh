#!/bin/bash

COLOR_RED="\033[0;31m"
COLOR_GREEN="\033[0;32m"
COLOR_BLUE="\033[0;34m"
COLOR_WHITE="\033[0;37m"

INDEX=0

make -C ../ > /dev/null

function fct()
{
	TEST_MINISHELL=$(printf "$@" | $CMD ../minishell 2>/dev/null)
	RET_MINISHELL=$?
	TEST_BASH=$(printf "$@" | $CMD bash 2>/dev/null)
	RET_BASH=$?

	printf "Test "$INDEX" : "
	if [ "$TEST_MINISHELL" == "$TEST_BASH" ] && [ "$RET_MINISHELL" == "$RET_BASH" ]
	then
		printf $COLOR_GREEN"OK\n"
	else
		printf $COLOR_RED"KO\n"
		printf $COLOR_BLUE
		printf "Bash (ret value : $RET_BASH) : \n$TEST_BASH"
		printf $COLOR_RED
		printf "\nMinishell (ret value : $RET_MINISHELL) : \n$TEST_MINISHELL\n"
		exit
	fi
	printf $COLOR_WHITE
	INDEX=$((INDEX + 1))
}

###########################################################
############################ CD ###########################
###########################################################
printf "*****TEST CD*****\n"
fct "cd ../../../../../../../..\npwd"
fct "cd /mnt/nfs/homes/rgeny\npwd"
fct "cd $HOME/Desktop"
fct "unset HOME\ncd"
fct "export HOME=\ncd"
fct "cd too many arguments"
fct "cd ./path_not_found"

###########################################################
########################### ENV ###########################
###########################################################
INDEX=0
printf "\n*****TEST ENV*****\n"
CMD="env -i "
fct "env"

unset CMD
