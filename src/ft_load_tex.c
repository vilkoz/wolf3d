/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 13:26:47 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/02 19:41:25 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** tex[2] is always floor
** tex[3] is always ceil
*/

void				ft_init_path(t_tex  *tex)
{
	tex[0].path = "res/tex/wall0.xpm";
	tex[1].path = "res/tex/wall1.xpm";
	tex[2].path = "res/tex/wood.xpm";
	tex[3].path = "res/tex/floor.xpm";
	tex[4].path = "res/tex/wall2.xpm";
	tex[5].path = "res/tex/eagle.xpm";
	tex[6].path = "res/tex/eagle.xpm";
}

void				ft_init_path_spr(t_spr  *spr, t_lsp *lsp)
{
	t_lsp		*tmp;
	int			i;

	tmp = lsp;
	i = 0;
	while (tmp)
	{
		(tmp->c == 'a') ? spr[i].path = "res/tex/pillar.xpm" : "23";
		(tmp->c == 'b') ? spr[i].path = "res/tex/greenlight.xpm" : "23";
		(tmp->c == 'd') ? spr[i].path = "res/tex/door.xpm" : "23";
		(tmp->c == 'D') ? spr[i].path = "res/tex/door.xpm" : "23";
		(tmp->c == 'z') ? spr[i].path = "res/tex/zombie1.xpm" : "23";
		(tmp->c == 'h') ? spr[i].path = "res/tex/potion.xpm" : "23";
		(tmp->c == 's') ? spr[i].path = "res/tex/shells.xpm" : "23";
		spr[i].pos = tmp->pos;
		spr[i].c = tmp->c;
		spr[i].op = 0;
		spr[i].spr_swp = 0;
		i++;
		tmp = tmp->next;
	}
}

static int			count_lsp(t_lsp *lsp)
{
	t_lsp		*tmp;
	int			i;

	tmp = lsp;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

static t_spr		*init_spr(t_e *e)
{
	t_spr		*spr;
	int			i;
	int			spr_num;

	i = -1;
	spr_num = count_lsp(e->lsp);
	e->spr_num = spr_num;
	spr = (t_spr *)malloc(sizeof(t_spr) * spr_num);
	ft_init_path_spr(spr, e->lsp);
	while (++i < spr_num)
	{
		spr[i].img = mlx_xpm_file_to_image(e->mlx, spr[i].path, &spr[i].w,
				&spr[i].h);
		if (spr[i].c == 'z')
			spr[i].img2 = mlx_xpm_file_to_image(e->mlx, "res/tex/zombie2.xpm",
					&spr[i].w, &spr[i].h);
		if (spr[i].img == NULL)
		{
			perror(spr[i].path);
			return (0);
		}
	}
	return (spr);
}

t_e					*ft_load_tex(t_e *e)
{
	t_tex		*tex;
	int			i;

	i = -1;
	tex = (t_tex *)malloc(sizeof(t_tex) * TEX_NUM);
	ft_init_path(tex);
	while (++i < TEX_NUM)
	{
		tex[i].img = mlx_xpm_file_to_image(e->mlx, tex[i].path, &tex[i].w,
				&tex[i].h);
		if (tex[i].img == NULL)
		{
			perror(tex[i].path);
			return (0);
		}
	}
	e->tex = tex;
	e->spr = init_spr(e);
	ft_load_gif(e);
	return (e);
}
