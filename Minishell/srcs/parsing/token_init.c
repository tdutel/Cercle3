/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:28:40 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/05 23:01:16 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	token_init_bis(t_var *var);

t_token	*token_init(t_var *var)
{
	var->new_tkn = malloc(sizeof(t_token));
	if (!var->new_tkn || var_init(var) == false)
	{
		ft_free_split_secure(&var->s);
		ft_free_split_secure(&var->spipe);
		free(var->new_tkn);
		return (NULL);
	}
	if (token_init_bis(var) == 1)
		return (NULL);
	var->new_tkn->next = NULL;
	return (var->new_tkn);
}

static int	token_init_bis(t_var *var)
{
	if (var->s && var->s[var->i] && var->s[var->i][0] == '<')
	{
		if (token_infile(var) == -1)
		{
			free(var->new_tkn);
			return (1);
		}
	}
	else if (var->s && var->s[var->i] && var->s[var->i][0] == '>')
	{
		if (token_outfile(var) == -1)
		{
			free(var->new_tkn);
			return (1);
		}
	}
	else if (var->s && var->s[var->i])
	{
		if (is_builtin(var->s[var->i]) == true)
			token_builtin(var);
		else
			token_cmd(var);
		token_arg(var);
	}
	return (0);
}
