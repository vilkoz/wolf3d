/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:29:35 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/09 02:43:58 by vrybalko         ###   ########.fr       */
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
		if (s_map(e, (int)map->y, (int)map->x) > '0' &&
				(!ft_isalpha(s_map(e, (int)map->y, (int)map->x))))
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

void		choose_color(t_e *e, t_ray ray, t_p map, int i)
{
	if (s_map(e, (int)map.y, (int)map.x) >= '0')
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
	ft_vline(e, init_point(i, 0), init_point(i, ray.d_start),
			0x33);
	ft_vline(e, init_point(i, ray.d_start), init_point(i, ray.d_end),
			add_shade(e, ray, ray.color));
	ft_vline(e, init_point(i, ray.d_end), init_point(i, e->height - 1),
			0x777777);
}

void		ft_raycast(t_e *e)
{
	int			i;
	t_ray		ray;
	t_p			map;
#ifdef linux
# pragma omp parallel private(i, ray, map)
# pragma omp for schedule(dynamic)
#endif
	for (i = 0; i < e->width; i++)
	{
		ray_init(e, &ray, &map, i);
		cast_a_ray(e, &ray, &map);
		if (ray.side == 0 || ray.side == 2)
			ray.wall_d = (map.x - ray.pos.x + (1 - ray.step.x) / 2) / ray.dir.x;
		else
			ray.wall_d = (map.y - ray.pos.y + (1 - ray.step.y) / 2) / ray.dir.y;
		ray.l_height = (int)(e->height / ray.wall_d);
		ray.d_start = -ray.l_height / 2 + e->height / 2;
		ray.d_end = ray.l_height / 2 + e->height / 2;
		e->z[i] = ray.wall_d;
		(e->k.tex % 2 == 1) ? choose_color(e, ray, map, i) :
			tex_put(e, ray, map, i);
	}
	put_sprite(e);
}
