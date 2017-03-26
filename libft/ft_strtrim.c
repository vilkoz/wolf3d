/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:59:05 by vrybalko          #+#    #+#             */
/*   Updated: 2016/12/01 20:29:11 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static	int		drop_spaces(char const *s)
{
	int		i;

	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	return (i);
}

static	int		drop_rev_spaces(char const *s, int i)
{
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i--;
	return (i);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	i = drop_spaces(s);
	j = ft_strlen(s);
	if (i == j)
	{
		str = (char *)malloc(sizeof(char));
		str[0] = '\0';
		return (str);
	}
	j = drop_rev_spaces(s, j - 1);
	str = ft_strsub(s, i, j - i + 1);
	return (str);
}
