/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:13:16 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/10 18:40:10 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	var_init(t_var *var)
{
	var->spipe = ft_split(var->str, '|');
	var->s = ft_split(var->spipe[var->index], ' ');
	var->quote = NULL;
	var->quote_cmd = false;
	if (!var->spipe || !var->s || !var->s[var->i])
		return (false);
	return (true);
}

bool	is_builtin(char *str)
{
	if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0)
		return (true);
	else
		return (false);
}

bool	has_in_out(char **s, int j)
{
	if (j == 0)
	{
		if ((s[j][0] == '<') || (s[j][0] == '<' && s[j][1] == '<')
		|| (s[j][0] == '>') || (s[j][0] == '>' && s[j][1] == '>'))
			return (true);
		else
			return (false);
	}
	else if (j > 0)
	{
		if ((s[j][0] == '<') || (s[j][0] == '<' && s[j][1] == '<')
		|| (s[j][0] == '>') || (s[j][0] == '>' && s[j][1] == '>')
		|| (s[j - 1][0] == '<' && s[j - 1][1] == '\0')
		|| (s[j - 1][0] == '>' && s[j - 1][1] == '\0')
		|| (s[j - 1][0] == '<' && s[j - 1][1] == '<' && s[j - 1][2] == '\0')
		|| (s[j - 1][0] == '>' && s[j - 1][1] == '>' && s[j - 1][2] == '\0'))
			return (true);
	}
	return (false);
}

char	*check_var(t_var *var, t_varenv *v_e)
{
	char	*tmp;

	v_e->j = var->i;
	if (is_env_in(*var, v_e->j) == true && var->quote_cmd == false)
	{
		ft_free_secure(&var->s_p);
		tmp = ft_trunc(var->s[0], 0, "$", *var);
		env_arg(var, v_e);
		tmp = ft_strjoinsp(tmp, var->env, 0);
		ft_free_secure(&var->env);
		return (tmp);
	}
	else
	{
		tmp = ft_strdup(var->s_p);
		ft_free_secure(&var->s_p);
		return (tmp);
	}
}

char	*ft_free_process(char **to_free, char *to_return)
{
	if (*to_free)
		ft_free_secure(&(*to_free));
	return (to_return);
}

/*bool	is_last_infile(char **s, int i)
{
	int	j;

	j = i;
	while (s[j] != NULL && s[j][0] != '|')
		j++;
	j--;
	while (s[j][0] != '<' && j >= 0)
		j--;
	if (i == j)
		return (true);
	else
		return (false);
}*/
