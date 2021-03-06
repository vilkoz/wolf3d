/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_mode_hooks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:12:45 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/26 15:52:00 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		game_key_press(int key, t_e *e)
{
	(key == K_W) ? e->k.move_y = 1 : (void)e->k.gopa;
	(key == K_S) ? e->k.move_y = -1 : (void)e->k.gopa;
	(key == K_A) ? e->k.move_x = 1 : (void)e->k.gopa;
	(key == K_D) ? e->k.move_x = -1 : (void)e->k.gopa;
	(key == K_LA) ? e->k.rot = 1 : (void)e->k.gopa;
	(key == K_RA) ? e->k.rot = -1 : (void)e->k.gopa;
}

void		game_key_release(int key, t_e *e)
{
	(key == K_W) ? e->k.move_y = 0 : (void)e->k.gopa;
	(key == K_S) ? e->k.move_y = 0 : (void)e->k.gopa;
	(key == K_A) ? e->k.move_x = 0 : (void)e->k.gopa;
	(key == K_D) ? e->k.move_x = 0 : (void)e->k.gopa;
	if (key == K_W || key == K_S || key == K_A || key == K_D)
	{
		e->bob_param.x = 0;
		e->bob = 0;
	}
	(key == K_LA) ? e->k.rot = 0 : (void)e->k.gopa;
	(key == K_RA) ? e->k.rot = 0 : (void)e->k.gopa;
	(key == K_SP) ? ft_shoot(e) : (void)e->k.gopa;
	(key == K_E) ? ft_open_door(e) : (void)e->k.gopa;
	(key == K_M) ? e->k.map += 1 : 23;
	(key == K_T) ? e->k.tex += 1 : 23;
}

void		game_loop_hook(t_e *e)
{
	calc_speed(e);
	(e->k.move_x != 0) ? ft_move(e) : (void)e->k.gopa;
	(e->k.move_y != 0) ? ft_move(e) : (void)e->k.gopa;
	(e->k.rot != 0) ? ft_rotate(e) : (void)e->k.gopa;
	ft_raycast(e);
	ft_move_enemies(e);
	put_gun(e);
	(e->k.map % 2 == 1) ? ft_print_map(e) : (void)e->k.gopa;
	choose_menu(e);
}

void		game_move_hook(t_e *e, int x, int y)
{
	int		delta;

	(void)y;
	if (x < e->width && x > 0 && y > 0 && y < e->height)
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
