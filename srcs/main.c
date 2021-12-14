#include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

int main(int argc, char *argv[], char *envp[])
{
    char *s;
    char **cmd;
    while ((s = readline("$>")))
    {
        add_history(s);

        cmd = ft_split(s, " ");
        for (int i = 0; cmd[i]; i++)
            printf("%s\n", cmd[i]);

        int pid = fork();
        if (pid == 0)
        {
            int ret = execve(cmd[0], cmd, envp);
            printf("ret=%d\n", ret);
            exit(127);
        }
        wait(0);
    }
}
