/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 17:13:21 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/04 11:12:52 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		key_press(int key, t_e *e)
{
	(e->k.menu == 0) ? game_key_press(key, e) : 23;
	if (key == 30)
		exit(0);
	return (0);
}

int		key_release(int key, t_e *e)
{
	if (key == 53 && e->k.menu == 0)
		e->k.menu = 1;
	else if (e->k.menu == 1)
		pause_key_hook(key, e);
	(e->k.menu == 0) ? game_key_release(key, e) : 23;
	if ((key == 53 && e->k.menu == 2) || (key == 53 && e->k.menu == 3))
		exit(0);
	return (0);
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
	(e->k.menu == 0) ? game_mouse_hook(e, key) : 23;
	(e->k.menu == 2) ? win_menu_mouse_hook(key, x, y, e) : 23;
	(e->k.menu == 1) ? pause_mouse_hook(key, x, y, e) : 23;
	return (0);
}

int		move_hook(int x, int y, t_e *e)
{
	(void)y;
	(e->k.menu == 0) ? game_move_hook(e, x, y) : 23;
	return (0);
}
