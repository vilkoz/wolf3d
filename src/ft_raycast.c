/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:29:35 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/18 00:51:35 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		ft_raycast(t_e *e)
{
	int			i;
	t_ray		ray;
	t_p			map;

	i = -1;
	while (++i < e->width)
	{
		ray.hit = 0;
		ray.cam_x = 2 * i / (double)e->width - 1;
		ray.pos = init_point(e->pl.pos.x, e->pl.pos.y);
		ray.dir.x = e->pl.dir.x + e->pl.plane.x * ray.cam_x;
		ray.dir.y = e->pl.dir.y + e->pl.plane.y * ray.cam_x;
		map = init_point((int)(ray.pos.x), (int)(ray.pos.y));
		ray.ddist.x = sqrt(1 + ray.dir.y * ray.dir.y / (ray.dir.x * ray.dir.x));
		ray.ddist.y = sqrt(1 + ray.dir.x * ray.dir.x / (ray.dir.y * ray.dir.y));
		if (ray.dir.x < 0)
		{
			ray.step.x = -1;
			ray.sdist.x = (ray.pos.x - map.x) * ray.ddist.x;
		}
		else
		{
			ray.step.x = 1;
			ray.sdist.x = (map.x + 1. - ray.pos.x) * ray.ddist.x;
		}
		if (ray.dir.y < 0)
		{
			ray.step.y = -1;
			ray.sdist.y = (ray.pos.y - map.y) * ray.ddist.y;
		}
		else
		{
			ray.step.y = 1;
			ray.sdist.y = (map.y + 1. - ray.pos.y) * ray.ddist.y;
		}
		while (ray.hit == 0)
		{
			if (ray.sdist.x < ray.sdist.y)
			{
				ray.sdist.x += ray.ddist.x;
				map.x += ray.step.x;
				ray.side = 0;
			}
			else
			{
				ray.sdist.y += ray.ddist.y;
				map.y += ray.step.y;
				ray.side = 1;
			}
			if (e->map[(int)map.y][(int)map.x] > '0' && e->map[(int)map.y][(int)map.x] != 'P')
				ray.hit = 1;
		}
		if (ray.side == 0)
			ray.wall_d = (map.x - ray.pos.x + (1 - ray.step.x) / 2) / ray.dir.x;
		else
			ray.wall_d = (map.y - ray.pos.y + (1 - ray.step.y) / 2) / ray.dir.y;
		ray.l_height = (int)(e->height / ray.wall_d);
		ray.d_start = -ray.l_height / 2 + e->height / 2;
		ray.d_end = ray.l_height / 2 + e->height / 2;
		if (e->map[(int)map.y][(int)map.x] == '1')
			ray.color = 0xffff00;
		if (e->map[(int)map.y][(int)map.x] == '2')
			ray.color = 0xff;
		ft_draw_line(e, point_in(i, ray.d_start), point_in(i, ray.d_end), ray.color);
	}
}
