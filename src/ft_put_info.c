/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 23:26:35 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/03 17:46:51 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			ft_putstry(t_e *e, char *str)
{
	e->txt_shift.y += 15;
	mlx_string_put(e->mlx, e->win, e->txt_shift.x, e->txt_shift.y, 0xffffff, str);
	free(str);
}

/*
** ft_realloc_str
*/

char			*ft_rs(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

static int		calc_kill_rate(t_e *e)
{
	int		i;
	int		count_z;
	int		count_killed_z;

	i = -1;
	count_z = 0;
	count_killed_z = 0;
	while (++i < e->spr_num)
	{
		if (e->spr[i].c == 'z')
			count_z++;
		if (e->spr[i].c == 'Z')
			count_killed_z++;
	}
	if (count_z != 0 && count_killed_z != 0)
		return (((double)count_killed_z / (double)(count_z + count_killed_z))
				* 100);
	else
		return (0);
}

static int		secrets(t_e *e)
{
	int		i;
	int		j;
	int		secrets_count;

	i = -1;
	secrets_count = 0;
	while (e->map[++i] != 0)
	{
		j = -1;
		while (e->map[i][++j] != '\0')
			if (e->map[i][j] == '7')
				secrets_count++;
	}
	return (secrets_count);
}

static void		win_info(t_e *e)
{
	int		points;

	points = e->pl.points;
	e->txt_shift = point_in(300, 300);
	ft_putstry(e, ft_strdup("YOU WIN"));
	ft_putstry(e, ft_rs(ft_rs(ft_strdup("kill rate:  "),
					ft_itoa(calc_kill_rate(e))), ft_strdup("%")));
	if (calc_kill_rate(e) == 100)
	{
		ft_putstry(e, ft_strdup("kills   bonus:  10000"));
		points += 10000;
	}
	if (secrets(e) == 0)
	{
		ft_putstry(e, ft_strdup("secrets bonus:  10000"));
		points += 10000;
	}
	else
		ft_putstry(e, ft_strdup("there are secret spots on map"));
	ft_putstry(e, ft_rs(ft_strdup("FINAL SCORE:  "), ft_itoa(points)));
	e->txt_shift = point_in(300, 600);
	ft_putstry(e, ft_strdup("EXIT"));
	e->txt_shift = point_in(15, 0);
}

static void		pause_info(t_e *e)
{
	e->txt_shift = point_in(15, 0);
	ft_putstry(e, ft_strdup("GAME PAUSED"));
	e->txt_shift = point_in(15, 45);
	ft_putstry(e, ft_strdup("Controls:"));
	ft_putstry(e, ft_strdup("WASD - movement"));
	ft_putstry(e, ft_strdup("<-   - turn left"));
	ft_putstry(e, ft_strdup("->   - turn right"));
	ft_putstry(e, ft_strdup("SPACE- shoot"));
	ft_putstry(e, ft_strdup("E    - opent door"));
	e->txt_shift = point_in(300, 600);
	ft_putstry(e, ft_strdup("EXIT"));
	e->txt_shift = point_in(15, 0);
}

static void		game_mode_info(t_e *e)
{
	e->txt_shift.x = 15;
	ft_putstry(e, ft_rs(ft_strdup("FPS:    "), ft_itoa(e->fps)));
	ft_putstry(e, ft_rs(ft_strdup("HP:     "), ft_itoa(e->pl.hp)));
	ft_putstry(e, ft_rs(ft_strdup("AMMO:   "), ft_itoa(e->pl.ammo)));
	ft_putstry(e, ft_rs(ft_strdup("POINTS: "), ft_itoa(e->pl.points)));
	ft_putstry(e, ft_rs(ft_strdup("e->k.menu: "), ft_itoa(e->k.menu)));
}

void			ft_put_info(t_e *e)
{
	(e->k.menu == 0) ? game_mode_info(e) : 23;
	(e->k.menu == 1) ? pause_info(e) : 23;
	(e->k.menu == 2) ? win_info(e) : 23;
	e->txt_shift.y = 0;
}
