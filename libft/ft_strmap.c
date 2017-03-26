/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 13:27:57 by vrybalko          #+#    #+#             */
/*   Updated: 2016/11/29 18:32:04 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char *s, char (*f)(char))
{
	size_t		i;
	size_t		len;
	char		*fresh;

	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		if ((fresh = (char *)malloc(sizeof(char) * len + 1)) == NULL)
			return (NULL);
		while (i < len)
		{
			fresh[i] = f(s[i]);
			i++;
		}
		fresh[i] = '\0';
		return (fresh);
	}
	return (NULL);
}
