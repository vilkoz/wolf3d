/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 18:36:23 by vrybalko          #+#    #+#             */
/*   Updated: 2016/12/19 16:19:29 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lstnew;

	if ((lstnew = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (0);
	if (content)
	{
		if ((lstnew->content = malloc(content_size + 1)) == NULL)
			return (0);
		lstnew->content_size = content_size;
		while ((content_size--) > 0)
		{
			*(char *)(lstnew->content + content_size) =
				*(char *)(content + content_size);
		}
	}
	else
	{
		lstnew->content = NULL;
		lstnew->content_size = 0;
	}
	lstnew->next = NULL;
	return (lstnew);
}
