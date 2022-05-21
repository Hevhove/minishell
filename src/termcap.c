/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:46:58 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/21 18:19:08 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_term_var(t_list **env)
{
	t_list	*head;
	char	*tmp;
	char	*term_var;

	head = *env;
	while (ft_strncmp((*env)->content, "TERM=", 5) != 0)
		*env = (*env)->next;
	term_var = ft_substr((*env)->content, 5, ft_strlen((*env)->content) - 5);
	*env = head;
	printf("%s\n", term_var);
	free(term_var);
	return (term_var);
}

int	init_term(t_list **env)
{
	int		ret;
	char	*term_type;

	if (isatty(STDIN_FILENO) != 1)
		exit (-1);
	term_type = get_term_var(env);
	if (term_type == NULL)
	{
		printf("TERM must be set (see 'env').\n");
		return (-1);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		printf("Could not access to the termcap database..\n");
		return (-1);
	}
	else if (ret == 0)
	{
		printf("Terminal type '%s' is not defined in termcap database (or have too few informations).\n", term_type);
		return (-1);
	}
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
	
// 	int		ret;
// 	t_list	**env;

// 	env = (t_list **)malloc(sizeof(t_list));
// 	if (!env)
// 		return (1);
// 	*env = NULL;
// 	env_init(env, envp);
// 	ret = init_term(env);
// 	ft_clear_env(env);
// 	return (ret);
// }