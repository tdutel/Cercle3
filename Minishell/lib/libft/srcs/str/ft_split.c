/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:42:00 by gd-harco          #+#    #+#             */
/*   Updated: 2022/11/07 14:10:21 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static char		**free_all(char **dest, size_t i);
static size_t	get_word_length(const char *s, char charset);
static size_t	get_nb_word(char const *s, char c);
static size_t	go_to_next_word(const char *s, char c);

/**
 * @function ft_split.c
 * @brief Allocates (with malloc(3)) and returns an array of strings
 * obtained by splitting ’s’ using the character ’c’ as a delimiter.
 * The array is ended by a NULL pointer.
 * @param s The string to split
 * @param c The delimiter character
 * @return The newly allocated array of strings \n NULL if the allocation fails.
 * @warning The array must be freed with ft_free_split, not free/ft_free_array.
 * @author gd-harco
 */

char	**ft_split(char const *s, char c)
{
	size_t	nb_word;
	size_t	i;
	size_t	len;
	char	**dest;

	if (s == NULL)
		return (NULL);
	nb_word = get_nb_word(s, c);
	dest = malloc(sizeof(char *) * (nb_word + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < nb_word)
	{
		s = s + go_to_next_word(s, c);
		len = get_word_length(s, c);
		dest[i] = ft_substr(s, 0, len);
		if (!dest[i])
			return (free_all(dest, i));
		s = s + len;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

static char	**free_all(char **dest, size_t i)
{
	while (i--)
		free(dest[i]);
	free(dest);
	return (NULL);
}

static size_t	get_word_length(const char *s, char charset)
{
	size_t	x;

	x = 0;
	while (s[x] && s[x] != charset)
		x++;
	return (x);
}

static size_t	get_nb_word(char const *s, char c)
{
	size_t	nb_word;
	size_t	x;

	x = 0;
	nb_word = 0;
	while (s[x])
	{
		if (s[x] != c)
			nb_word++;
		while (s[x] && s[x] != c)
			x++;
		if (s[x])
			x++;
	}
	return (nb_word);
}

static size_t	go_to_next_word(const char *s, char c)
{
	size_t	x;

	x = 0;
	while (s[x] == c)
		x++;
	return (x);
}
