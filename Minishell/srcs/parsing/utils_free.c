/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:46:03 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/12 13:45:59 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_secure(char **elem)
{
	if (*elem != NULL)
		free(*elem);
	*elem = NULL;
}

void	ft_free_split_secure(char ***splitted_element)
{
	size_t	i;

	if (*splitted_element == NULL)
		return ;
	i = 0;
	while ((*splitted_element)[i])
	{
		free((*splitted_element)[i]);
		i++;
	}
	free(*splitted_element);
	*splitted_element = NULL;
}

void	free_var(t_var *var)
{
	ft_free_secure(&var->str_in);
	ft_free_secure(&var->str);
	ft_free_split_secure(&var->s);
	ft_free_split_secure(&var->spipe);
}

void	ft_free_sig(t_sig **sig)
{
	if ((!*sig))
		return ;
	if ((*sig)->int_prompt)
		free((*sig)->int_prompt);
	(*sig)->int_prompt = NULL;
	if ((*sig)->int_exec)
		free((*sig)->int_exec);
	(*sig)->int_exec = NULL;
	if ((*sig)->int_parent)
		free((*sig)->int_parent);
	(*sig)->int_parent = NULL;
	if ((*sig)->int_here_doc)
		free((*sig)->int_here_doc);
	(*sig)->int_here_doc = NULL;
	if ((*sig)->quit_prompt)
		free((*sig)->quit_prompt);
	(*sig)->quit_prompt = NULL;
	if ((*sig)->quit_exec)
		free((*sig)->quit_exec);
	(*sig)->quit_exec = NULL;
	if ((*sig)->quit_parent)
		free((*sig)->quit_parent);
	(*sig)->quit_parent = NULL;
	free((*sig));
	(*sig) = NULL;
}
// void	free_var_quote(t_var_quote *v_q)
// {
// 	ft_free_secure(&v_q->tmp);
// 	ft_free_split_secure(&v_q->split_tmp);
// }

// void	ft_free_split_secure(char **splitted_element)
// {
// 	size_t	i;

// 	if (splitted_element == NULL)
// 		return ;
// 	i = 0;
// 	while ((splitted_element)[i])
// 	{
// 		ft_free_secure((&splitted_element)[i]);
// 		// splitted_element[i] = NULL;
// 		i++;
// 	}
// 	ft_free_secure(splitted_element);
// 	splitted_element = NULL;
// }

// void	ft_free_split_secure2(char ***splitted_element)
// {
// 	size_t	i;

// 	if (*splitted_element == NULL)
// 		return ;
// 	i = 0;
// 	while ((*splitted_element)[i])
// 	{
// 		ft_free_secure((splitted_element)[i]);
// 		i++;
// 		// splitted_element[i++] = NULL;
// 	}
// 	ft_free_secure(*splitted_element);
// 	splitted_element = NULL;
// }
