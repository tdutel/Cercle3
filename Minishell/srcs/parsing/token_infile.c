/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:44:06 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/05 21:53:18 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	heredoc_infile(t_var *var)
{
	char	*tmp;

	if (var->s[var->i][2] != '\0')
	{
		tmp = ft_substr(var->s[var->i], 2, ft_strlen(var->s[var->i]));
		var->new_tkn->content[0] = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		var->i++;
		var->new_tkn->content[0] = ft_strdup(var->s[var->i]);
	}
	var->new_tkn->type = HERE_DOC;
}

static void	fill_infile(t_var *var)
{
	char	*tmp;

	if (var->s[var->i][1] && var->s[var->i][1] == '<')
	{
		heredoc_infile(var);
	}
	else if (var->s[var->i][1] != '\0')
	{
		var->new_tkn->type = FILE_IN;
		tmp = ft_substr(var->s[var->i], 1, ft_strlen(var->s[var->i]));
		var->new_tkn->content[0] = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		var->new_tkn->type = FILE_IN;
		var->new_tkn->content[0] = ft_strdup(var->s[++var->i]);
	}
}

static void	heredoc_quote_infile(t_var *var, t_varenv *v_e)
{
	if (var->s[var->i][2] != '\0')
	{
		quote_manager_inout(var, v_e);
		var->quote_cmd = true;
		var->new_tkn->content[0] = ft_strdup(var->quote);
		ft_free_secure(&var->quote);
	}
	else
	{
		var->i++;
		v_e->j++;
		quote_manager(var, v_e);
		var->quote_cmd = true;
		var->new_tkn->content[0] = ft_strdup(var->quote);
		ft_free_secure(&var->quote);
	}
	var->new_tkn->type = HERE_DOC;
}

static void	fill_quote_infile(t_var *var)
{
	t_varenv	v_e;

	v_e.j = var->i;
	if (var->s[var->i][1] && var->s[var->i][1] == '<')
	{
		heredoc_quote_infile(var, &v_e);
	}
	else if (var->s[var->i][1] != '\0')
	{
		var->new_tkn->type = FILE_IN;
		quote_manager_inout(var, &v_e);
		var->quote_cmd = true;
		var->new_tkn->content[0] = ft_strdup(var->quote);
		ft_free_secure(&var->quote);
	}
	else
	{
		var->i++;
		v_e.j++;
		var->new_tkn->type = FILE_IN;
		quote_manager(var, &v_e);
		var->quote_cmd = true;
		var->new_tkn->content[0] = ft_strdup(var->quote);
		ft_free_secure(&var->quote);
	}
}

int	token_infile(t_var *var)
{
	if ((var->s[var->i][1] == '\0' && !var->s[var->i + 1])
	|| (var->s[var->i][1] == '<' && var->s[var->i][2] == '\0'
	&& !var->s[var->i + 1]))
		return (-1);
	if (is_quote_in(var->s[var->i]) == 0
		&& ((is_quote_in(var->s[var->i + 1]) == 0)
			|| (var->s[var->i][1] == '<' && var->s[var->i][2] == '\0'
		&& is_quote_in(var->s[var->i + 1]) == 0)))
	{
		fill_infile(var);
	}
	else
	{
		fill_quote_infile(var);
	}
	var->new_tkn->content[1] = NULL;
	return (0);
}
