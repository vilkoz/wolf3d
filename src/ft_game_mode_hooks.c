/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_mode_hooks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:12:45 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/02 23:09:03 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		game_key_press(int	key, t_e *e)
{
	(key == 53) ? exit(0) : (void)e->k.gopa;
	(key == 13) ? e->k.move_y = 1 : (void)e->k.gopa;
	(key == 1) ? e->k.move_y = -1 : (void)e->k.gopa;
	(key == 0) ? e->k.move_x = 1 : (void)e->k.gopa;
	(key == 2) ? e->k.move_x = -1 : (void)e->k.gopa;
	(key == 123) ? e->k.rot = 1 : (void)e->k.gopa;
	(key == 124) ? e->k.rot = -1 : (void)e->k.gopa;
	(key == 115) ? e->k.move_y = -1 : (void)e->k.gopa;//LINUX
	(key == 119) ? e->k.move_y = 1 : (void)e->k.gopa;	//LINUX
	(key == 65361) ? e->k.rot = 1 : (void)e->k.gopa;	//LINUX
	(key == 65363) ? e->k.rot = -1 : (void)e->k.gopa;	//LINUX
	(key == 65307) ? exit(0) : (void)e->k.gopa;		//LINUX
	(key == 97) ? e->k.move_x = 1 : (void)e->k.gopa;	//LINUX
	(key == 100) ? e->k.move_x = -1 : (void)e->k.gopa;//LINUX
}

void		game_key_release(int key, t_e *e)
{
	(key == 13) ? e->k.move_y = 0 : (void)e->k.gopa;
	(key == 1) ? e->k.move_y = 0 : (void)e->k.gopa;
	(key == 0) ? e->k.move_x = 0 : (void)e->k.gopa;
	(key == 2) ? e->k.move_x = 0 : (void)e->k.gopa;
	(key == 123) ? e->k.rot = 0 : (void)e->k.gopa;
	(key == 124) ? e->k.rot = 0 : (void)e->k.gopa;
	(key == 49) ? ft_shoot(e) : (void)e->k.gopa;
	(key == 14) ? ft_open_door(e) : (void)e->k.gopa;
	(key == 46) ? e->k.map += 1 : 23;
	(key == 32) ? ft_open_door(e) : (void)e->k.gopa;	//LINUX
	(key == 119) ? e->k.move_y = 0 : (void)e->k.gopa;	//LINUX
	(key == 115) ? e->k.move_y = 0 : (void)e->k.gopa;	//LINUX
	(key == 65361) ? e->k.rot = 0 : (void)e->k.gopa;	//LINUX
	(key == 65363) ? e->k.rot = 0 : (void)e->k.gopa;	//LINUX
	if (key == 116 && e->k.tex == 1)					//LINUX
		e->k.tex = 0;									//LINUX
	else if (key == 116 && e->k.tex == 0)				//LINUX
		e->k.tex = 1;									//LINUX
	(key == 97) ? e->k.move_x = 0 : (void)e->k.gopa;	//LINUX
	(key == 100) ? e->k.move_x = 0 : (void)e->k.gopa;	//LINUX
}

void		game_move_hook(t_e *e, int x, int y)
{
	int		delta;

	(void)y;
	if (x < e->width && x > 0)
	{
		delta = (e->m.x - x);
		(delta < 0) ? e->k.rot = -1 : 23; 
		(delta > 0) ? e->k.rot = 1 : 23;
		(abs(delta) <= 10) ? e->k.rot = 0 : 23;
		e->m.x = x;
	}
}

void		game_mouse_hook(t_e *e, int key)
{
	if (key == 1)
		ft_shoot(e);
}
