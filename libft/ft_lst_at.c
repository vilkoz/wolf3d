/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 18:11:49 by vrybalko          #+#    #+#             */
/*   Updated: 2016/12/02 16:19:49 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	t_list			*tmp;
	unsigned int	i;

	tmp = begin_list;
	i = 1;
	while (tmp->next != 0 && i < nbr)
	{
		tmp = tmp->next;
		i++;
	}
	if (i < nbr)
		return (0);
	return (tmp);
}
