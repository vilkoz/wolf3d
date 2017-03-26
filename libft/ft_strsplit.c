/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:20:36 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/24 00:16:38 by tor              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		char_strlen(char const *s, char c, int i)
{
	int		n;

	n = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		n++;
	}
	return (i);
}

static int		count_words(char const *s, char c)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (s[++i])
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			n++;
	return (n);
}

static char		*put_word(char const *s, char c, int *i)
{
	char	*word;
	int		j;

	word = (char *)malloc(sizeof(char) * (char_strlen(s, c, *i) + 1));
	if (word)
	{
		j = 0;
		while (s[*i] != c && s[*i])
		{
			word[j] = s[*i];
			(*i)++;
			j++;
		}
		word[j] = '\0';
		return (word);
	}
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**out;
	int		i;
	int		j;

	if (s == NULL || !c)
		return (0);
	i = 0;
	j = 0;
	if ((out = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1))) == 0)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			if ((out[j] = put_word(s, c, &i)) == NULL)
				return (NULL);
			j++;
		}
		else
			i++;
	}
	out[j] = NULL;
	return (out);
}
