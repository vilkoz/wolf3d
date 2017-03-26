/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 18:01:23 by vrybalko          #+#    #+#             */
/*   Updated: 2016/12/01 18:05:35 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lst_push_back(t_list *begin, t_list *elem)
{
	t_list		*tmp;

	if (begin && elem)
	{
		tmp = begin->next;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
		return (begin);
	}
	return (NULL);
}
