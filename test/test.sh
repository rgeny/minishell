#!/bin/bash

#CMD=--trace-children=yes --suppressions=../ignoreliberror --leak-check=full --show-leak-kinds=all

COLOR_RED="\033[0;31m"
COLOR_GREEN="\033[0;32m"
COLOR_BLUE="\033[0;34m"
COLOR_WHITE="\033[0;37m"

make re -C ../ > /dev/null
clear

function test_ret_stdout()
{
	TEST_MINISHELL=$(printf "$@" | $CMD ../minishell 2>/dev/null)
	RET_MINISHELL=$?
	TEST_BASH=$(printf "$@" | $CMD bash 2>/dev/null)
	RET_BASH=$?

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
		printf "\nBash      (ret value : $RET_BASH) :\n$TEST_BASH"
		printf $COLOR_RED
		printf "\nMinishell (ret value : $RET_MINISHELL) :\n$TEST_MINISHELL\n"
#		exit
	fi
	printf $COLOR_WHITE
	INDEX=$((INDEX + 1))
}

function test_env()
{
	TEST_MINISHELL=$(printf "$@" | $CMD ../minishell 2>/dev/null)
	LINE_MINISHELL=$(echo "$TEST_MINISHELL" | wc -l)
	RET_MINISHELL=$?
	TEST_BASH=$(printf "$@" | $CMD bash 2>/dev/null)
	LINE_BASH=$(echo "$TEST_BASH" | wc -l)
	RET_BASH=$?

	if [ "$LINE_MINISHELL" == "$LINE_BASH" ] && [ "$RET_MINISHELL" == "$RET_BASH" ]
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
		printf "\nBash      (ret value : $RET_BASH) :\nBash n line      : $LINE_BASH\nTest bash      :\n$TEST_BASH\n"
		printf $COLOR_RED
		printf "\nMinishell (ret value : $RET_MINISHELL) :\nMinishell n line : $LINE_MINISHELL\nTest minishell :\n$TEST_MINISHELL\n"
#		exit
	fi
	printf $COLOR_WHITE
	INDEX=$((INDEX + 1))
}

###########################################################
############################ CD ###########################
###########################################################
if [ ! $1 ] || [ "$1" == "cd" ]
then
		INDEX=0
		printf "***** TEST CD *****\n"
		test_ret_stdout "cd"
		test_ret_stdout "cd a a"
		test_ret_stdout "cd ../../../../../../../..\npwd"
		test_ret_stdout "cd /mnt/nfs/homes/rgeny\npwd"
		test_ret_stdout "cd $HOME/Desktop"
		test_ret_stdout "unset HOME\ncd"
		test_ret_stdout "export HOME=\ncd"
		test_ret_stdout "cd too many arguments"
		test_ret_stdout "cd ./path_not_found"
		test_ret_stdout "cd ..\ncd -\npwd"
		test_ret_stdout "cd ..\nunset OLDPWD\ncd -"
		test_ret_stdout "cd ..\nunset OLDPWD\ncd -\npwd"
		test_ret_stdout "mkdir t1\nmkdir t1/t2\ncd t1/t2\nrm -rf ../../t1\ncd .."
		test_ret_stdout "mkdir t1\nmkdir t1/t2\ncd t1/t2\nrm -rf ../../t1\ncd ..\npwd"
		test_ret_stdout "mkdir t1\nmkdir t1/t2\ncd t1/t2\nrm -rf ../../t1\ncd ..\nunset PWD\npwd"
		test_ret_stdout "export CDPATH=/mnt/nfs\ncd homes/..\npwd"
		test_ret_stdout "export CDPATH=/mnt/nfs/\ncd homes/..\npwd"
		test_ret_stdout "pwd\nexport CDPATH=\ncd .\npwd"
		test_ret_stdout "pwd\nexport CDPATH=\ncd ..\npwd"
		test_ret_stdout "unset PATH\ncd"
		CMD="env -i"
		test_ret_stdout "cd"
		test_ret_stdout "cd a a"
		test_ret_stdout "cd ../../../../../../../..\npwd"
		test_ret_stdout "cd /mnt/nfs/homes/rgeny\npwd"
		test_ret_stdout "cd $HOME/Desktop"
		test_ret_stdout "unset HOME\ncd"
		test_ret_stdout "export HOME=\ncd"
		test_ret_stdout "cd too many arguments"
		test_ret_stdout "cd ./path_not_found"
		test_ret_stdout "cd ..\ncd -\npwd"
		test_ret_stdout "cd ..\nunset OLDPWD\ncd -"
		test_ret_stdout "cd ..\nunset OLDPWD\ncd -\npwd"
		test_ret_stdout "/bin/mkdir t1\n/bin/mkdir t1/t2\ncd t1/t2\n/bin/rm -rf ../../t1\ncd .."
		test_ret_stdout "/bin/mkdir t1\n/bin/mkdir t1/t2\ncd t1/t2\n/bin/rm -rf ../../t1\ncd ..\npwd"
		test_ret_stdout "/bin/mkdir t1\n/bin/mkdir t1/t2\ncd t1/t2\n/bin/rm -rf ../../t1\ncd ..\nunset PWD\npwd"
		test_ret_stdout "export CDPATH=/mnt/nfs\ncd homes/..\npwd"
		test_ret_stdout "export CDPATH=/mnt/nfs/\ncd homes/..\npwd"
		test_ret_stdout "pwd\nexport CDPATH=\ncd .\npwd"
		test_ret_stdout "pwd\nexport CDPATH=\ncd ..\npwd"
		test_ret_stdout "unset PATH\ncd"

		unset CMD
fi

###########################################################
########################## ECHO ###########################
###########################################################
if [ ! $1 ] || [ "$1" == "echo" ]
then
		INDEX=0
		printf "\n\n***** TEST ECHO *****\n"
		test_ret_stdout "echo"
		test_ret_stdout "echo a b"
		test_ret_stdout "echo -n"
		test_ret_stdout "echo -n a"
		test_ret_stdout "echo a -n"
		test_ret_stdout "echo -nn a"
		test_ret_stdout "echo -nnnm"
		test_ret_stdout "echo -nnn -n -a"
		test_ret_stdout "echo -nn -a a -nn"
		test_ret_stdout "echo a\necho b"
		test_ret_stdout "echo -n a\necho b"
		test_ret_stdout "unset PATH\necho"
fi

###########################################################
########################## ENV ############################
###########################################################
if [ ! $1 ] || [ "$1" == "env" ]
then
		INDEX=0
		printf "\n\n***** TEST ENV *****\n"
		test_env "env"
		test_env "env\nexport ABC\nenv"
		test_env "env\nexport ABC=\nenv"
		test_env "env\nexport ABC=4\nenv"
		CMD="env -i"
		test_env "env"
		test_env "env\nexport ABC\nenv"
		test_env "env\nexport ABC=\nenv"
		test_env "env\nexport ABC=4\nenv"
		test_env "unset PWD SHLVL _\nenv"

		unset CMD
fi

###########################################################
######################### EXIT ############################
###########################################################
if [ ! $1 ] || [ "$1" == "exit" ]
then
		INDEX=0
		printf "\n\n***** TEST EXIT *****\n"
		for i in {-2..256}
		do 
			test_ret_stdout "exit $i"
		done
		test_ret_stdout "exit 1986416"
		test_ret_stdout "exit 2147483647"
		test_ret_stdout "exit 2147483648"
		test_ret_stdout "exit -2147483648"
		test_ret_stdout "exit -2147483649"
		test_ret_stdout "exit 9223372036854775807"
		test_ret_stdout "exit 9223372036854775808"
		test_ret_stdout "exit -9223372036854775808"
		test_ret_stdout "exit -9223372036854775809"
		test_ret_stdout "exit 9999999999999999999999999999"
		test_ret_stdout "unset PATH\nexit"
fi

###########################################################
######################### EXPORT ##########################
###########################################################
if [ ! $1 ] || [ "$1" == "export" ]
then
		INDEX=0
		printf "\n\n***** TEST EXPORT *****\n"
		test_ret_stdout "export var=a\nexport $var=test\necho $var $a"
		test_ret_stdout "export $var=test"
		test_ret_stdout "export ABC=4\nexport ABC\necho $ABC"
		test_ret_stdout "export ABC\necho $ABC"
		test_ret_stdout "export ABC\nexport ABC=DEF\necho $ABC"
		test_ret_stdout "export A=$HOME\n echo $A"
		test_env "export var\nexport var=q\nexport"
		test_ret_stdout "export \"'\" test=a"
		test_env "export \"'\" test=a\nenv"
		test_env "unset PATH\nexport"
		test_ret_stdout "export 0A"
		test_ret_stdout "export 0B=4"
		test_ret_stdout "export _ABC=17"
		test_ret_stdout "export _A0=17"
		test_ret_stdout "export _0A"
		CMD="env -i"
		test_env "export"
		test_ret_stdout "export var=a\nexport $var=test\necho $var $a"
		test_ret_stdout "export $var=test"
		test_ret_stdout "export ABC=4\nexport ABC\necho $ABC"
		test_ret_stdout "export ABC\necho $ABC"
		test_ret_stdout "export ABC\nexport ABC=DEF\necho $ABC"
		test_ret_stdout "export A=$HOME\n echo $A"
		test_env "export var\nexport var=q\nexport"
		test_ret_stdout "export \"'\" test=a"
		test_env "export \"'\" test=a\nenv"
		test_env "unset PATH\nexport"
		test_ret_stdout "export 0A"
		test_ret_stdout "export 0B=4"
		test_ret_stdout "export _ABC=17"
		test_ret_stdout "export _A0=17"
		test_ret_stdout "export _0A"

		unset CMD
fi

###########################################################
########################## PWD ############################
###########################################################
if [ ! $1 ] || [ "$1" == "pwd" ]
then
		INDEX=0
		printf "\n\n***** TEST PWD *****\n"
		test_ret_stdout "pwd"
		test_ret_stdout "pwd a"
		test_ret_stdout "pwd pwd"
		test_ret_stdout "pwd a b c d e f"
		test_ret_stdout "pwd ls"
		test_ret_stdout "unset PWD\npwd"
		test_ret_stdout "unset PWD\ncd ..\npwd"
		test_ret_stdout "pwd\ncd ..\npwd"
		test_ret_stdout "pwd -"
		test_ret_stdout "pwd -p"
		test_ret_stdout "pwd --"
		test_ret_stdout "pwd --p"
		CMD="env -i"
		test_ret_stdout "pwd"
		test_ret_stdout "pwd a"
		test_ret_stdout "pwd pwd"
		test_ret_stdout "pwd a b c d e f"
		test_ret_stdout "pwd ls"
		test_ret_stdout "unset PWD\npwd"
		test_ret_stdout "unset PWD\ncd ..\npwd"
		test_ret_stdout "pwd\ncd ..\npwd"
		test_ret_stdout "pwd -"
		test_ret_stdout "pwd -p"
		test_ret_stdout "pwd --"
		test_ret_stdout "pwd --p"
fi

###########################################################
######################### UNSET ###########################
###########################################################
if [ ! $1 ] || [ "$1" == "unset" ]
then
		INDEX=0
		printf "\n\n***** TEST UNSET *****\n"
		test_ret_stdout "unset"
		test_ret_stdout "unset a b c d"
		test_ret_stdout "unset PATH\necho $PATH"
		test_ret_stdout "unset PATH\nls"
		test_ret_stdout "unset \"'\" test"
		test_ret_stdout "unset ="
		test_ret_stdout "unset PWD\necho $PWD"
		test_env "export var=1\nexport var1=2\nunset var\nenv"

		unset CMD
fi

printf "\n"
