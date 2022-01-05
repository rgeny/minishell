#!/bin/bash

COLOR_RED="\033[0;31m"
COLOR_GREEN="\033[0;32m"
COLOR_BLUE="\033[0;34m"
COLOR_WHITE="\033[0;37m"

INDEX=0

make re -C ../ > /dev/null

function fct()
{
	TEST_MINISHELL=$(printf "$@" | $CMD ../minishell 2>/dev/null)
	RET_MINISHELL=$?
	TEST_BASH=$(printf "$@" | $CMD bash 2>/dev/null)
	RET_BASH=$?

#	printf "Test "$INDEX" : "
	if [ "$TEST_MINISHELL" == "$TEST_BASH" ] && [ "$RET_MINISHELL" == "$RET_BASH" ]
	then
		printf $COLOR_GREEN"$INDEX:OK "
#		printf $COLOR_WHITE"CMD : \n$@\n"
#		printf $COLOR_BLUE
#		printf "\nBash      (ret value : $RET_BASH) : \n$TEST_BASH"
#		printf $COLOR_GREEN
#		printf "\nMinishell (ret value : $RET_MINISHELL) : \n$TEST_MINISHELL\n\n"
	else
		printf $COLOR_RED"$INDEX:KO\n"
		printf $COLOR_WHITE"CMD : \n$@\n"
		printf $COLOR_BLUE
		printf "\nBash    (ret value : $RET_BASH) : \n$TEST_BASH"
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
printf "***** TEST CD *****\n"
fct "cd"
fct "cd a a"
fct "cd ../../../../../../../..\npwd"
fct "cd /mnt/nfs/homes/rgeny\npwd"
fct "cd $HOME/Desktop"
fct "unset HOME\ncd"
fct "export HOME=\ncd"
fct "cd too many arguments"
fct "cd ./path_not_found"
fct "cd ..\ncd -\npwd"
fct "cd ..\nunset OLDPWD\ncd -\npwd"
fct "mkdir t1\nmkdir t1/t2\ncd t1/t2\nrm -rf ../../t1\ncd .."
fct "mkdir t1\nmkdir t1/t2\ncd t1/t2\nrm -rf ../../t1\ncd ..\npwd"
fct "mkdir t1\nmkdir t1/t2\ncd t1/t2\nrm -rf ../../t1\ncd ..\nunset PWD\npwd"
fct "export CDPATH=/mnt/nfs\ncd homes/..\npwd"
fct "export CDPATH=/mnt/nfs/\ncd homes/..\npwd"
fct "pwd\nexport CDPATH=\ncd .\npwd"
fct "pwd\nexport CDPATH=\ncd ..\npwd"

###########################################################
########################## ECHO ###########################
###########################################################
INDEX=0
printf "\n\n***** TEST ECHO *****\n"
fct "echo"
fct "echo a b"
fct "echo -n"
fct "echo -n a"
fct "echo a -n"
fct "echo -nn a"
fct "echo -nnnm"
fct "echo -nnn -n -a"
fct "echo -nn -a a -nn"
fct "echo a\necho b"
fct "echo -n a\necho b"

###########################################################
########################### ENV ###########################
###########################################################
INDEX=0
printf "\n\n***** TEST ENV *****\n"
CMD="env -i "
fct "env"

unset CMD
