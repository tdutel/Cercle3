/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:15:00 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/10 19:20:20 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*token_last(t_token *token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}

void	token_add_back(t_token **token, t_token *new)
{
	t_token	*tail;

	if (!token)
		return ;
	if (*token)
	{
		tail = token_last(*token);
		tail->next = new;
	}
	else
		*token = new;
}

// t_token	*tknnew(t_var *var)
// {
// 	t_token	*new;

// 	new = malloc(sizeof(t_token));
// 	if (!new)
// 		return (NULL);
// 	new->next = NULL;
// 	new = token_init(var);
// 	return (new);
// }

void	token_memcpy(t_token *dest, const t_token *src)
{
	int	i;

	if (dest == NULL || src == NULL)
		return ;
	i = 0;
	while (i < 2)
	{
		if (src->content[i] != NULL)
			dest->content[i] = ft_strdup(src->content[i]);
		else
			dest->content[i] = NULL;
		i++;
	}
	dest->type = src->type;
	if (src->next != NULL)
	{
		dest->next = malloc(sizeof(t_token));
		if (dest->next != NULL)
			token_memcpy(dest->next, src->next);
	}
	else
	{
		dest->next = NULL;
	}
}

void	token_clear(t_token **tkn)
{
	int	i;

	i = 0;
	if (*tkn == NULL)
		return ;
	while (i < 2)
	{
		if ((*tkn)->content[i] != NULL)
		{
			ft_free_secure(&(*tkn)->content[i]);
		}
		i++;
	}
	token_clear(&((*tkn)->next));
	free(*tkn);
	*tkn = NULL;
}

t_token	*token_pipe(void)
{
	t_token	*tmp;

	tmp = malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->type = PIPE;
	tmp->content[0] = ft_strdup("|");
	tmp->content[1] = NULL;
	tmp->next = NULL;
	return (tmp);
}

// void	token_clear_one(t_token **tkn)
// {
// 	int	i;

// 	i = 0;
// 	if (*tkn == NULL)
// 		return ;
// 	while (i < 2)
// 	{
// 		if ((*tkn)->content[i] != NULL)
// 		{
// 			ft_free_secure(&(*tkn)->content[i]);
// 			// (*tkn)->content[i] = NULL;
// 		}
// 		i++;
// 	}
// 	free(*tkn);
// 	*tkn = NULL;
// }

// void	token_clear(t_token **tkn)
// {
// 	t_token	*buffer;

// 	if (!tkn)
// 		return ;
// 	while (tkn)
// 	{
// 		buffer = (*tkn)->next;
// 		ft_free_array((void **)(*tkn)->content);
// 		// free(tkn->content);
// 		// free(tkn->content[1]);
// 		free(*tkn);
// 		*tkn = buffer;
// 	}
// }
