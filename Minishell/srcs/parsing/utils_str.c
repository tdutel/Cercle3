/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:58:50 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/10 18:54:47 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//############################   JOIN_FCT   #################################//

static char	*joningsp(char *result, char *s2, char *s1)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (s1[x])
	{
		result[x] = s1[x];
		x++;
	}
	result[x] = ' ';
	x++;
	while (s2[y])
	{
		result[x] = s2[y];
		x++;
		y++;
	}
	result[x] = '\0';
	return (result);
}

static char	*joning(char *result, char *s2, char *s1)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (s1[x])
	{
		result[x] = s1[x];
		x++;
	}
	while (s2[y])
	{
		result[x] = s2[y];
		x++;
		y++;
	}
	result[x] = '\0';
	return (result);
}

/*
ft_strjoinsp fonction comme un strjoin normal mais le int n permet de
savoir si on espace les 2 str d'un space durant le join : 0 non, 1 oui.
*/

char	*ft_strjoinsp(char *s1, char *s2, int n)
{
	size_t		joined_size;
	char		*result;

	joined_size = (ft_strlen (s1) + ft_strlen (s2));
	if (!s2 && !s1)
		return (NULL);
	if (!s2 && s1)
		return ((ft_strdup(s1)));
	if (!s1 && s2)
		return ((ft_strdup(s2)));
	result = malloc(sizeof(char) * joined_size + 1 + n);
	if (!result)
	{
		ft_free_secure(&s1);
		exit(EXIT_FAILURE);
	}
	if (n == 1)
	{
		joningsp(result, (char *)s2, (char *)s1);
		ft_free_secure(&s1);
		return (result);
	}
	joning(result, (char *)s2, (char *)s1);
	ft_free_secure(&s1);
	return (result);
}

char	*ft_strjoinsp2(char *s1, char *s2, int n, t_var_quote *v_q)
{
	size_t		joined_size;
	char		*result;

	joined_size = (ft_strlen (s1) + ft_strlen (s2));
	if (!s2 && !s1)
		return (NULL);
	if (!s2 && s1)
		return ((ft_strdup(s1)));
	if (!s1 && s2)
		return ((ft_strdup(s2)));
	result = malloc(sizeof(char) * joined_size + 1 + n);
	if (!result)
		exit_free_secure(&s1, &v_q->tmp);
	if (n == 1)
	{
		joningsp(result, (char *)s2, (char *)s1);
		ft_free_secure(&s1);
		return (result);
	}
	joning(result, (char *)s2, (char *)s1);
	ft_free_secure(&s1);
	return (result);
}
