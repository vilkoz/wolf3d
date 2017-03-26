/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:12:29 by vrybalko          #+#    #+#             */
/*   Updated: 2016/11/30 18:31:21 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*tmp;
	t_list		*cur;

	tmp = *alst;
	cur = tmp;
	while (tmp)
	{
		tmp = tmp->next;
		del(cur->content, cur->content_size);
		free(cur);
		cur = tmp;
	}
	*alst = NULL;
}
