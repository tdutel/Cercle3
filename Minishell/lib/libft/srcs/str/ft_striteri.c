/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:12:30 by gd-harco          #+#    #+#             */
/*   Updated: 2022/12/05 10:38:23 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @function ft_striteri
 * @brief Applies the function f to each character of the string passed
 * @param s The string on which to iterate.
 * @param f The function to apply to each character of s and its index.
 * @author gd-harco
 */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	x;

	x = 0;
	if (s)
	{
		while (s[x])
		{
			f((x), &(s[x]));
			x++;
		}
	}
}
