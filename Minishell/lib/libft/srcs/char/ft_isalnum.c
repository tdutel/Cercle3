/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:46:39 by gd-harco          #+#    #+#             */
/*   Updated: 2022/10/28 18:46:39 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "char.h"

bool	ft_isalnum(int c)
{
	if (((c >= 97 && c <= 122) || (c >= 65 && c <= 90) \
				|| (c >= 48 && c <= 57)))
		return (true);
	return (false);
}
