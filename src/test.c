/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:10:54 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/04/19 17:54:09 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define MAXCOM 1000
#define MAXLIST 100

#define clear() printf("\033[H\033[J")

void	init_shell()
{
	clear();
	printf("\n\n\n\n******************"
        "************************");
	printf("\n\n\n\t****MY SHELL****");
    printf("\n\n\t-USE AT YOUR OWN RISK-");
    printf("\n\n\n\n*******************"
        "***********************");
	char	*username = getenv("USER");
	printf("\n\n\nUSER is: @%s", username);
    printf("\n");
    sleep(1);
    clear();
}

int	takeInput(char *str)
{
	char	*buf;

	buf = readline("\n>>> ");
	printf("current buffer is: %s\n", buf);
	rl_replace_line("replaced", 1);
	printf("current buffer is: %s\n", buf);
	if (strlen(buf) != 0)
	{
		add_history(buf);
		strcpy(str, buf);
		return (0);
	}
	else
		return (1);
}

void	printDir()
{
	char	cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\nDir: %s", cwd);
}

void	execArgs(char **parsed)
{
	pid_t	pid = fork();

	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return ;
	}
	else if (pid == 0)
	{
		if (execvp(parsed[0], parsed) < 0)
			printf("\nCouldn't execute command..");
		exit(0);
	}
	else
	{
		wait(NULL);
		return ;
	}
}

void	execArgsPiped(char **parsed, char **parsedpipe)
{
	int		pipefd[2];
	pid_t	p1;
	pid_t	p2;

	if (pipe(pipefd) < 0)
	{
		printf("\nPpipe couldn't be initialized");
		return ;
	}
	p1 = fork();
	if (p1 < 0)
	{
		printf("Couldn't fork");
		return ;
	}
	if (p1 == 0) // child 1 executing, only nedds to write at the write end
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCould not execute command 1..");
            exit(0);
		}
	}
	else
	{
		p2 = fork(); // parent executing
		if (p2 < 0)
		{
			printf("\nCould not fork");
            return ;
		}
		if (p2 == 0) // child 2executing, only nedds to read at the read end
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execvp(parsedpipe[0], parsedpipe) < 0)
			{
				printf("\nCould not execute command 2..");
                exit(0);
			}
		}
		else // parent exxecuting, waiting for 2 children
		{
			wait(NULL);
			wait(NULL);
		}
	}
}

void	openHelp()
{
	puts("\n***WELCOME TO MY SHELL HELP***"
        "\nCopyright @ Suprotik Dey"
        "\n-Use the shell at your own risk..."
        "\nList of Commands supported:"
        "\n>cd"
        "\n>ls"
        "\n>exit"
        "\n>all other general commands available in UNIX shell"
        "\n>pipe handling"
        "\n>improper space handling");
  
    return ;
}

int	ownCmdHandler(char **parsed)
{
	int		NoOfOwnCmds;
	int		i;
	int		switchOwnArg;
	char	*username;

	NoOfOwnCmds = 4;
	char	*ListOfOwnCmds[NoOfOwnCmds];
	switchOwnArg = 0;
	ListOfOwnCmds[0] = "exit";
	ListOfOwnCmds[1] = "cd";
	ListOfOwnCmds[2] = "help";
	ListOfOwnCmds[3] = "hello";
	i = 0;
	while (i < NoOfOwnCmds)
	{
		if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0)
		{
			switchOwnArg = i + 1;
			break;
		}
		i++;
	}
	if (switchOwnArg == 1)
	{
			printf("\nGoodbye\n");
        	exit(0);
	}
	else if	(switchOwnArg == 2)
	{
		chdir(parsed[1]);
		return (1);
	}
	else if (switchOwnArg == 3)
	{
		openHelp();
		return (1);
	}
	else if (switchOwnArg == 4)
	{
		username = getenv("USER");
		printf("\nHello %s.\nMind that this is "
            "not a place to play around."
            "\nUse help to know more..\n",
            username);
		return (1);
	}
	else
		return (0);
	return (0);
}

int	parsePipe(char *str, char **strpiped)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		strpiped[i] = strsep(&str, "|"); // can be replaced by ft_split
		if (strpiped[i] == NULL)
			break;
		i++;
	}
	if (strpiped[1] == NULL)
		return (0); // return 0 if no pipe is found
	else
		return (1);
}

void	parseSpace(char *str, char **parsed)
{
	int	i;

	i = 0;
	while (i < MAXLIST)
	{
		parsed[i] = strsep(&str, " ");
		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) == 0)
			i--;
		i++;
	}
}

int	processString(char *str, char **parsed, char **parsedpipe)
{
	char	*strpiped[2];
	int		piped;

	piped = parsePipe(str, strpiped);
	if (piped)
	{
		parseSpace(strpiped[0], parsed);
		parseSpace(strpiped[1], parsedpipe);
	}
	else
		parseSpace(str, parsed);
	if (ownCmdHandler(parsed))
		return (0);
	else
		return (1 + piped);
}

int	main()
{
	char	inputString[MAXCOM];
	char	*parsedArgs[MAXLIST];
	char	*parsedArgsPiped[MAXLIST];
	int		execFlag;
	
	execFlag = 0;
	init_shell();
	while (1)
	{
		printDir(); // print shell line
		if (takeInput(inputString)) // take input
			continue;
		// printf("current buffer is: %s\n", inputString);
		// rl_replace_line("replaced", 0);
		// printf("current buffer is: %s\n", inputString);
		execFlag = processString(inputString, parsedArgs, parsedArgsPiped); // process
		// execFlag return 0 if there is no cmd
		// or it is a builtin command,
		// 1 if it is a simple cmd
		// 2 if it is including pipe
		if (execFlag == 1)
			execArgs(parsedArgs);
		if (execFlag == 2)
			execArgsPiped(parsedArgs, parsedArgsPiped);
	}

	return (0);
}