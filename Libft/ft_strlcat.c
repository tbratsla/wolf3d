/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:38:11 by tbratsla          #+#    #+#             */
/*   Updated: 2018/10/26 14:38:11 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t i;
	size_t j;
	size_t x;
	size_t y;

	x = ft_strlen((char*)src);
	i = 0;
	j = 0;
	y = ft_strlen((char*)dst);
	while (dst[i])
		i++;
	if (y > dstsize)
		return (x + dstsize);
	while (src[j] && dstsize - 1 > i)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (x + y);
}
