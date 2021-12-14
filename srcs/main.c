#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "env.h"

int main(int argc, char *argv[], char *envp[])
{
	t_env	*env = 0;
	char	*name;
	char	*value;

	env_init(&env, envp);
	env_print(env);
	env_free(env);
/*    char *s;
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
    }*/
}
