/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 12:29:11 by tbratsla          #+#    #+#             */
/*   Updated: 2019/07/20 12:29:11 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		length;
	char	buff;

	i = 0;
	length = ft_strlen(str) - 1;
	while (length > i)
	{
		buff = str[i];
		str[i] = str[length];
		str[length] = buff;
		length--;
		i++;
	}
	return (str);
}
