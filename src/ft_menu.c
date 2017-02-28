/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:09:33 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/28 21:05:01 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		dead_screen(t_e *e, int hit)
{
	int		i;
	int		j;
	time_t	t;

	i = -1;
	srand(time(&t));
	while (++i < e->height)
	{
		j = -1;
		while (++j < e->width)
			if (rand() % 8 > hit)
				ft_img_px_put(e, j, i, 0xff0000);
	}
}

void		choose_menu(t_e *e)
{
	(e->pl.hp == 0) ? dead_screen(e, 4) : 23;
	(e->pl.hp == 0) ? e->k.menu = 1 : 23;
}
