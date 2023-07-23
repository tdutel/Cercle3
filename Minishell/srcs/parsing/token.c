/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:40:27 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/11 12:05:21 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		get_token(t_token *t_new, t_var *var);
static void		token_list_bis(t_var *var, t_token	*t_new);
static void		token_bis(t_token *t_new, t_var *var, t_token *tmp);

static void	init_start(t_var *var)
{
	var->index = 0;
	var->nb_pipe = ft_nb_pipe(var->str);
	var->i = 0;
}

t_token	*get_token_list(t_var *var)
{
	t_token	*t_new;
	t_token	*tmp;

	if (!var->str)
		return (NULL);
	init_start(var);
	tmp = token_init(var);
	if (tmp == NULL)
		return (NULL);
	t_new = malloc(sizeof(t_token));
	if (t_new == NULL)
		return (token_clear(&tmp), NULL);
	token_memcpy(t_new, tmp);
	token_clear(&tmp);
	var->i++;
	if (var->s)
	{
		token_list_bis(var, t_new);
	}
	return (t_new);
}

static void	token_list_bis(t_var *var, t_token	*t_new)
{
	while ((var->index == 0 || var->spipe[var->index - 1])
		&& var->spipe[var->index])
	{
		ft_free_split_secure(&var->s);
		ft_free_split_secure(&var->spipe);
		get_token(t_new, var);
	}
}

static void	get_token(t_token *t_new, t_var *var)
{
	t_token	*tmp;
	t_token	*tnew;

	var_init(var);
	tmp = NULL;
	while ((var->s && var->s[var->i]))
		token_bis(t_new, var, tmp);
	if (var->nb_pipe-- > 0)
	{
		tmp = token_pipe();
		if (!tmp)
			exit_free(var, t_new, NULL);
		tnew = malloc(sizeof(t_token));
		if (!tnew)
			exit_free(var, t_new, tmp);
		token_memcpy(tnew, tmp);
		token_clear(&tmp);
		token_add_back(&t_new, tnew);
	}
	ft_free_split_secure(&var->s);
	ft_free_split_secure(&var->spipe);
	var_init(var);
	var->index++;
	var->i = 0;
}

static void	token_bis(t_token *t_new, t_var *var, t_token *tmp)
{
	t_token	*tnew;

	ft_free_split_secure(&var->s);
	ft_free_split_secure(&var->spipe);
	tmp = token_init(var);
	if (!tmp)
	{
		token_clear(&t_new);
		free_var(var);
		free(var->new_tkn);
		exit(EXIT_FAILURE);
	}
	tnew = malloc(sizeof(t_token));
	if (!tnew)
	{
		token_clear(&t_new);
		token_clear(&tmp);
		free_var(var);
		exit(EXIT_FAILURE);
	}
	token_memcpy(tnew, tmp);
	token_clear(&tmp);
	var->i++;
	if (tnew != NULL && already_cmd(t_new, tnew) != true)
		token_add_back(&t_new, tnew);
}
