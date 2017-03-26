/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 17:47:50 by vrybalko          #+#    #+#             */
/*   Updated: 2016/11/30 14:31:36 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		dst_len;
	size_t		src_len;
	int			delta;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	delta = size - dst_len;
	if (delta <= 0)
		return (src_len + size);
	else
	{
		ft_strncat(dst, src, size - 1 - dst_len);
		return (src_len + dst_len);
	}
}
