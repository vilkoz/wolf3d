/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:09:33 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/03 18:18:24 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		dead_screen(t_e *e, int hit, int c)
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
				ft_img_px_put(e, j, i, c);
	}
}

void			win_menu_mouse_hook(int key, int x, int y, t_e *e)
{
	if (key == 1 && x > 290 && x < 460 && y > 600 && y < 660)
		exit(0);
	(void)e;
}

void			pause_mouse_hook(int key, int x, int y, t_e *e)
{
	if (key == 1 && x > 290 && x < 460 && y > 600 && y < 660)
		exit(0);
	(void)e;
}

void			pause_key_hook(int key, t_e *e)
{
	if (key == 53)
		e->k.menu = 0;
	if (key == 12)
		exit(0);
}

void		choose_menu(t_e *e)
{
	(e->pl.hp == 0) ? dead_screen(e, 4, 0xff0000) : 23;
	(e->pl.hp == 0) ? e->k.menu = 1 : 23;
	(e->k.menu == 2) ? dead_screen(e, 4, 0x00cc00) : 23;
	(e->k.menu == 1) ? dead_screen(e, 6, 0x005500) : 23;
}
