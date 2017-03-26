/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 18:28:28 by vrybalko          #+#    #+#             */
/*   Updated: 2016/11/30 21:09:55 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	unsigned char	*mem;
	size_t			i;

	mem = malloc(size);
	i = 0;
	if (mem == NULL)
		return (NULL);
	else
		while (i < size)
		{
			*(mem + i) = 0;
			i++;
		}
	return (mem);
}
