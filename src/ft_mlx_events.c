/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:26:45 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/26 17:05:34 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	calc_speed(t_e *e)
{
	s_t		time_val;
	double	old_time;
	double	frame_time;

	old_time = e->time;
	gettimeofday(&time_val, NULL);
	e->time = time_val.tv_usec;
	frame_time = ((e->time - old_time) > 0 ? (e->time - old_time) :
			e->time - old_time + 1000000) / 1000000;
	e->fps = (int)(1. / frame_time);
	e->pl.ms = frame_time * 5;
	e->pl.rs = frame_time * 3;
	//printf("ms = %f, rs = %f, fps = %f, frametime = %f\n", e->pl.ms, e->pl.rs, 1/frame_time, frame_time);
	if (e->k.move_x && e->k.move_y)
		e->pl.ms *= e->pl.ms;
}

int		exit_hook(t_e *e)
{
	free_map(e->map);
	exit(0);
	return (0);
}

void	ft_mlx_events(t_e *e)
{
	keys_init(&(e->k));
	mlx_hook(e->win, 2, 1, key_press, e);
	mlx_hook(e->win, 3, 2, key_release, e);
	mlx_mouse_hook(e->win, mouse_hook, e);
	mlx_hook(e->win, 6, 65, move_hook, e);
	mlx_hook(e->win, 17, 1L << 17, exit_hook, e);
}
