/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 18:52:15 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/03 18:53:57 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		free_map(char **map)
{
	int		i;

	i = -1;
	while (map[++i] != 0)
		ft_strdel(&map[i]);
}

t_lsp		*lsp_new(t_p pos, char c)
{
	t_lsp		*new;

	new = (t_lsp *)malloc(sizeof(t_lsp));
	new->pos = pos;
	new->c = c;
	return (new);
}

t_lsp		*lsp_add(t_lsp *new, t_lsp *old)
{
	if (new != NULL)
		new->next = old;
	return (new);
}

t_chk_chr	init_chk(int is_solid, char c)
{
	t_chk_chr new;

	new.is_solid = is_solid;
	new.c = c;
	return (new);
}

void		check_char(t_e *e, int y, t_lst *tmp, t_chk_chr s)
{
	char	*pl;
	char	*new1;

	new1 = tmp->line;
	while ((pl = ft_strchr(new1, s.c)) != NULL)
	{
		e->lsp = lsp_add(lsp_new(init_point(pl - tmp->line + 0.5, y + 0.5),
					s.c), e->lsp);
		(!s.is_solid && pl != NULL) ? e->map[y][pl - tmp->line] = ' ' : 23;
		new1 = pl + 1;
	}
}
