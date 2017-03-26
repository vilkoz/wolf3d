/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 22:01:35 by vrybalko          #+#    #+#             */
/*   Updated: 2016/11/29 18:32:47 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!to_find[0])
		return ((char *)str);
	while (str[i] != '\0' && (size_t)i <= len)
	{
		while (str[i] == to_find[j] && (size_t)i < len)
		{
			i++;
			j++;
			if (to_find[j] == '\0')
				return ((char *)(str + i - j));
			if (str[i] != to_find[j])
			{
				i = i - j + 1;
				j = 0;
			}
		}
		i++;
	}
	return (0);
}
