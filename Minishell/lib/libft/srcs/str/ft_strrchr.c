/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:09:12 by gd-harco          #+#    #+#             */
/*   Updated: 2022/11/10 16:09:12 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @brief Locate the last occurrence of the character c in the string s.
 * @param s The string to be searched in.
 * @param c The character to be searched for.
 * @return A pointer to the last occurrence of character in the string. \n
 * If the value is not found, the function returns a null pointer.
 */

char	*ft_strrchr(const char *s, int c)
{
	int	x;

	x = ft_strlen(s);
	while (x >= 0)
	{
		if (s[x] == (c % 256))
			return ((char *) s + x);
		x--;
	}
	return (NULL);
}
