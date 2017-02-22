/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 13:26:47 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/22 17:58:48 by vrybalko         ###   ########.fr       */
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
}

void				ft_init_path_spr(t_spr  *spr, t_lsp *lsp)
{
	t_lsp		*tmp;
	int			i;

	tmp = lsp;
	i = 0;
	while (tmp)
	{
		if (tmp->c == 'a')
			spr[i].path = "res/tex/pillar.xpm";
		if (tmp->c == 'b')
			spr[i].path = "res/tex/greenlight.xpm";
		spr[i].pos = tmp->pos;
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
	return (e);
}
