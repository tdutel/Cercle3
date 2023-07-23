/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:42:56 by gd-harco          #+#    #+#             */
/*   Updated: 2022/12/16 18:34:16 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H
# include <stddef.h>
# include <stdbool.h>

size_t	ft_array_length(void **array);
void	**ft_array_dup(void **array, bool free_array, bool dup_strings);
char	**ft_merge_array(char **p_array, char **s_array,
			bool free_array, bool free_line);
void	ft_sort_array(char **array);
void	**ft_add_array_line(void **array, void *content);
void	ft_remove_array_line(void **array, size_t index, bool free_line);

#endif
