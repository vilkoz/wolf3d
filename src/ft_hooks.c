/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 17:13:21 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/02 19:27:16 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		key_press(int key, t_e *e)
{
	(key == 53) ? exit(0) : (void)e->k.gopa;
	(e->k.menu == 0) ? game_key_press(key, e) : 23;
	return (0);
}

int		key_release(int key, t_e *e)
{
	(e->k.menu == 0) ? game_key_release(key, e) : 23;
	return (0);
}

void	calc_speed(t_e *e)
{
	double old_time;
	double frame_time;

	old_time = e->time;
	e->time = clock();
	frame_time = (e->time - old_time) / CLOCKS_PER_SEC;
	e->fps = (int)(1. / frame_time);
	e->pl.ms = frame_time * 5;
	e->pl.rs = frame_time * 3;
	if (e->k.move_x && e->k.move_y)
		e->pl.ms *= e->pl.ms;
}

int		loop_hook(t_e *e)
{
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, e->width, e->height);
	(e->k.menu == 0) ? game_loop_hook(e) : 23;
	choose_menu(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	ft_put_info(e);
	return (0);
}

int		mouse_hook(int key, int x, int y, t_e *e)
{
	(void)x;
	(void)y;
	(e->k.menu == 0) ? game_mouse_hook(e, key) : 23;
	return (0);
}

int		move_hook(int x, int y, t_e *e)
{
	(void)y;
	(e->k.menu == 0) ? game_move_hook(e, x, y) : 23;
	return (0);
}
