/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 21:26:19 by vrybalko          #+#    #+#             */
/*   Updated: 2016/11/30 20:44:07 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = ft_strlen(s);
	if (c == '\0' && str[i] == '\0')
		return (&str[i]);
	while (i != -1)
	{
		if (str[i] == c)
			return (&str[i]);
		i--;
	}
	return (NULL);
}
