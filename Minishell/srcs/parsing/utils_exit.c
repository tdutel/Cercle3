/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:22:43 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/11 13:59:01 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_free(t_var *var, t_token *tkn, t_token *tkn2)
{
	free_var(var);
	free(var->sig);
	token_clear(&tkn);
	token_clear(&tkn2);
	exit(EXIT_FAILURE);
}

void	exit_free_secure(char **str1, char **str2)
{
	ft_free_secure(str1);
	ft_free_secure(str2);
	exit(EXIT_FAILURE);
}

void	exit_trunc(t_var *var)
{
	free_var(var);
	free(var->sig);
	free(var->new_tkn);
	exit(EXIT_FAILURE);
}

void	exit_sig(void)
{
	ft_dprintf(STDERR_FILENO, MALLOC_ERR"main.c\n");
	exit(EXIT_FAILURE);
}
