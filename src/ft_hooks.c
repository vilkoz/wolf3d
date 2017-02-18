/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 17:13:21 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/18 14:33:00 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		key_press(int key, t_e *e)
{
	(key == 53) ? exit(0) : (void)e->k.gopa;
	(key == 13) ? e->k.move_y = 1 : (void)e->k.gopa;
	(key == 119) ? e->k.move_y = 1 : (void)e->k.gopa; //LINUX
	(key == 1) ? e->k.move_y = -1 : (void)e->k.gopa;
	(key == 115) ? e->k.move_y = -1 : (void)e->k.gopa; //LINUX
	(key == 0) ? e->k.move_x = 1 : (void)e->k.gopa;
	(key == 2) ? e->k.move_x = -1 : (void)e->k.gopa;
	(key == 123) ? e->k.rot = 1 : (void)e->k.gopa;
	(key == 124) ? e->k.rot = -1 : (void)e->k.gopa;
	return (0);
}

int		key_release(int key, t_e *e)
{
	(key == 13) ? e->k.move_y = 0 : (void)e->k.gopa;
	(key == 1) ? e->k.move_y = 0 : (void)e->k.gopa;
	(key == 119) ? e->k.move_y = 0 : (void)e->k.gopa; //LINUX
	(key == 115) ? e->k.move_y = 0 : (void)e->k.gopa; //LINUX
	(key == 0) ? e->k.move_x = 0 : (void)e->k.gopa;
	(key == 2) ? e->k.move_x = 0 : (void)e->k.gopa;
	(key == 123) ? e->k.rot = 0 : (void)e->k.gopa;
	(key == 124) ? e->k.rot = 0 : (void)e->k.gopa;
	return (0);
}

int		loop_hook(t_e *e)
{
	(e->k.move_x != 0) ? ft_move(e) : (void)e->k.gopa;
	(e->k.move_y != 0) ? ft_move(e) : (void)e->k.gopa;
	(e->k.rot != 0) ? ft_rotate(e) : (void)e->k.gopa;
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, e->width, e->height);
	ft_raycast(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

int		mouse_hook(int key, int x, int y, t_e *e)
{
	(void)x;
	(void)y;
	(void)key;
	(void)e;
	return (0);
}

int		move_hook(int x, int y, t_e *e)
{
	(void)x;
	(void)y;
	(void)e;
	return (0);
}
