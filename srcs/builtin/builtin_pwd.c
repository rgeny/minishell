/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 01:37:12 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 04:29:56 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <unistd.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"
#include "builtin.h"

static void	check_arg(char *arg)
{
	if (arg[0] == '-' && arg[1] && arg[1] != '-')
	{
		str_printerr("minishell: pwd: ", arg,
			": invalid option\npwd: usage: pwd\n", 0);
		exit(2);
	}
	else if (arg[0] == '-' && arg[1] == '-' && arg[2])
	{
		str_printerr("minishell: pwd: --: invalid option\n",
			"pwd: usage: pwd\n", 0, 0);
		exit(2);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	path[PATH_CHAR_MAX + 1];
	
	if (argc > 1)
		check_arg(argv[1]);
	getcwd(path, PATH_CHAR_MAX + 1);
	str_printfd(path, 1);
	write(1, "\n", 1);
	return (PWD_DEFAULT);
}*/
/*
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>
#include<errno.h>

#define MAX_SIZE 256

void do_pwd(char*);

int get_inode(char *path)
{
     struct stat info;
     int inode;
     if(stat(path,&info)==-1){
          perror("get inode error");
          exit(errno);
     }
     inode = info.st_ino;
     return inode;
}

void get_name_inode(char name[], int inode)
{
     DIR *dir_ptr;
     struct dirent *ptr;
     if((dir_ptr = opendir("."))==NULL){
          perror("dir open error");
          exit(errno);
     }
     while((ptr = readdir(dir_ptr))!=NULL){
          if(ptr->d_ino==inode){
               strcpy(name,ptr->d_name);
               break;
          }
     }
     closedir(dir_ptr);
     return;
}

int main(int argc, char *argv[])
{
     do_pwd(".");
     printf("\n");
     return 0;
}

void do_pwd(char *path)
{
     int flag=0;
     char name[MAX_SIZE];
     int inode=get_inode(path);
     if(inode!=get_inode("..")){
          chdir("..");
          get_name_inode(name,inode);
          do_pwd(".");
          printf("/%s",name);
     }return;
}*/

#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main (void)
{
	char *dir;
	/* Let this program be used for debugging.  */
	mtrace ();
	dir = getcwd ("/mnt", 0);
	if (dir == NULL)
		perror ("getcwd");
	else
	{
		puts (dir);
		free (dir);
	}
	return (dir == NULL ? EXIT_FAILURE : EXIT_SUCCESS);
}
