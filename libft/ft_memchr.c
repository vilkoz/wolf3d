/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 20:34:56 by vrybalko          #+#    #+#             */
/*   Updated: 2016/11/30 16:24:17 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*str;
	unsigned char			symbol;

	str = (unsigned char *)s;
	symbol = (unsigned char)c;
	while (n--)
		if (*str++ == symbol)
			return ((void *)--str);
	return (0);
}
