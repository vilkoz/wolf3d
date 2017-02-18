/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:29:35 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/19 00:08:54 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_vline(t_e *e, t_p p1, t_p p2, int rgb)
{
	int			i;

	i = (p1.y > 0) ? p1.y : 0;
	p2.y = (p2.y > e->height) ? e->height - 1 : p2.y;
	while (i < p2.y)
	{
		ft_img_px_put(e, p1.x, i, rgb);
		i++;
	}
}

static void	cast_a_ray(t_e *e, t_ray *ray, t_p *map)
{
	while (ray->hit == 0)
	{
		if (ray->sdist.x < ray->sdist.y)
		{
			ray->sdist.x += ray->ddist.x;
			map->x += ray->step.x;
			ray->side = (ray->step.x < 0) ? 0 : 2;
		}
		else
		{
			ray->sdist.y += ray->ddist.y;
			map->y += ray->step.y;
			ray->side = (ray->step.y < 0) ? 1 : 3;
		}
		if (e->map[(int)map->y][(int)map->x] > '0')
			ray->hit = 1;
	}
}

static void	ray_init(t_e *e, t_ray *ray, t_p *map, int i)
{
	ray->hit = 0;
	ray->cam_x = 2 * i / (double)e->width - 1;
	ray->pos = init_point(e->pl.pos.x, e->pl.pos.y);
	ray->dir.x = e->pl.dir.x + e->pl.plane.x * ray->cam_x;
	ray->dir.y = e->pl.dir.y + e->pl.plane.y * ray->cam_x;
	*map = init_point((int)(ray->pos.x), (int)(ray->pos.y));
	ray->ddist.x = sqrt(1 + ray->dir.y * ray->dir.y
			/ (ray->dir.x * ray->dir.x));
	ray->ddist.y = sqrt(1 + ray->dir.x * ray->dir.x
			/ (ray->dir.y * ray->dir.y));
	ray->step.x = (ray->dir.x < 0) ? -1 : 1;
	if (ray->dir.x < 0)
		ray->sdist.x = (ray->pos.x - map->x) * ray->ddist.x;
	else
		ray->sdist.x = (map->x + 1. - ray->pos.x) * ray->ddist.x;
	ray->step.y = (ray->dir.y < 0) ? -1 : 1;
	if (ray->dir.y < 0)
		ray->sdist.y = (ray->pos.y - map->y) * ray->ddist.y;
	else
		ray->sdist.y = (map->y + 1. - ray->pos.y) * ray->ddist.y;
}

void		ft_raycast(t_e *e)
{
	int			i;
	t_ray		ray;
	t_p			map;

	i = -1;
	while (++i < e->width)
	{
		ray_init(e, &ray, &map, i);
		cast_a_ray(e, &ray, &map);
		if (ray.side == 0 || ray.side == 2)
			ray.wall_d = (map.x - ray.pos.x + (1 - ray.step.x) / 2) / ray.dir.x;
		else
			ray.wall_d = (map.y - ray.pos.y + (1 - ray.step.y) / 2) / ray.dir.y;
		ray.l_height = (int)(e->height * 2 / ray.wall_d);
		ray.d_start = -ray.l_height / 2 + e->height / 2;
		ray.d_end = ray.l_height / 2 + e->height / 2;
		if (e->map[(int)map.y][(int)map.x] >= '0')
		{
			if (ray.side == 0)
				ray.color = 0x00ff00;
			if (ray.side == 1)
				ray.color = 0xffff00;
			if (ray.side == 2)
				ray.color = 0x0000ff;
			if (ray.side == 3)
				ray.color = 0x00ffff;
		}
		ft_vline(e, point_in(i, 0), point_in(i, ray.d_start),
				0x33);
		ft_vline(e, point_in(i, ray.d_start), point_in(i, ray.d_end),
		((ray.color >> ((e->height / ray.l_height - 1) / 2)) & 0x7f7f7f));
		ft_vline(e, point_in(i, ray.d_end), point_in(i, e->height - 1),
				0x777777);
	}
}
