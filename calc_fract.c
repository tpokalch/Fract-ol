/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:31:53 by tpokalch          #+#    #+#             */
/*   Updated: 2019/03/09 19:52:15 by tpokalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		color_jul4(double i, double j, t_global g)
{
	double	tmpx;
	double	is;
	double	js;
	int		ret;

	g.c.x = i;
	g.c.y = j;
	ret = -1;
	ret++;
	while (++ret < g.precision)
	{
		is = i * i;
		js = j * j;
		if (is + js > g.bound)
			return (ret);
		tmpx = is * i - i * js - 2 * i * js + g.c.x;
		j = (-j * js + j * is + 2 * is * j) + g.c.y;
		i = tmpx;
	}
	return (0);
}

int		color_jul3(double i, double j, t_global g)
{
	double	tmpx;
	int		ret;
	double	is;
	double	js;

	ret = -1;
	ret++;
	while (++ret < g.precision)
	{
		is = i * i;
		js = j * j;
		if (is + js > g.bound)
			return (ret);
		tmpx = is * i - i * js - 2 * i * js + g.c.x;
		j = (-j * js + j * is + 2 * is * j) + g.c.y;
		i = tmpx;
	}
	return (0);
}

int		color_man(double i, double j, t_global g)
{
	double	tmpx;
	double	is;
	double	js;
	int		ret;

	g.c.x = i;
	g.c.y = j;
	ret = -1;
	ret++;
	while (++ret < g.precision)
	{
		is = i * i;
		js = j * j;
		if (is + js > g.bound)
			return (ret);
		tmpx = is - js + g.c.x;
		j = 2 * i * j + g.c.y;
		i = tmpx;
	}
	return (0);
}

int		color_jul(double i, double j, t_global g)
{
	double	tmpx;
	double	is;
	double	js;
	int		ret;

	ret = -1;
	ret++;
	while (++ret < g.precision)
	{
		is = i * i;
		js = j * j;
		if (is + js > g.bound)
			return (ret);
		tmpx = is - js + g.c.x;
		j = 2 * i * j + g.c.y;
		i = tmpx;
	}
	return (0);
}

void	*fract_to_img(void *p)
{
	t_global	*g;
	int			i;
	int			j;

	g = (t_global *)p;
	j = g->core * HEIGHT / CORES;
	while (j < (g->core + 1) * HEIGHT / CORES)
	{
		i = -1;
		while (++i < WIDTH)
		{
			g->data_ptr[j * WIDTH + i] =
			color_mode(g->color_mode) * g->fract(
			g->center.x + (-WIDTH / 2 + i) / (double)g->zoom,
			g->center.y + (j - HEIGHT / 2) / (double)g->zoom, *g);
		}
		j++;
	}
	return (NULL);
}
