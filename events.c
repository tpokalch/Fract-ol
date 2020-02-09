/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 20:44:59 by tpokalch          #+#    #+#             */
/*   Updated: 2019/03/09 20:06:56 by tpokalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		color_mode(int mode)
{
	if (mode == 0)
		return (800250);
	else if (mode == 1)
		return (0x0F0F0F);
	else if (mode == 2)
		return (0x0F000F);
	else if (mode == 3)
		return (0x00000F);
	else if (mode == 4)
		return (0x01040F);
	else
		return (0x000F0F);
}

void	start_threads(t_global *g)
{
	t_global	p[CORES];
	int			i;

	i = -1;
	while (++i < CORES)
	{
		copy(&p[i], g);
		p[i].core = i;
		pthread_create(&p[i].tid[i], NULL, fract_to_img, &p[i]);
	}
	i = -1;
	while (++i < CORES)
		pthread_join(p[i].tid[i], NULL);
	mlx_put_image_to_window(g->m_p, g->w_p, g->img_ptr, 0, 0);
}

int		mouse_press(int kk, int x, int y, void *param)
{
	t_global *g;

	g = param;
	ft_bzero((int *)g->data_ptr, g->sz_l * HEIGHT);
	if (kk == 1)
		return (g->zoom_mode = (g->zoom_mode + 1) % 2);
	if (g->zoom_mode)
	{
		g->m_pos.x = g->center.x + (x - WIDTH / 2) / (double)g->zoom;
		g->m_pos.y = g->center.y + (y - HEIGHT / 2) / (double)g->zoom;
	}
	if (kk == 4)
	{
		g->center.x = g->m_pos.x - (g->m_pos.x - g->center.x) / (double)g->zoom;
		g->center.y = g->m_pos.y - (g->m_pos.y - g->center.y) / (double)g->zoom;
		g->zoom = g->zoom / (double)1.05;
	}
	else if (kk == 5)
	{
		g->center.x = g->m_pos.x - (g->m_pos.x - g->center.x) / (double)g->zoom;
		g->center.y = g->m_pos.y - (g->m_pos.y - g->center.y) / (double)g->zoom;
		g->zoom = g->zoom * 1.05;
	}
	start_threads(g);
	return (1);
}

int		key_press(int kk, void *param)
{
	t_global *g;

	g = param;
	ft_bzero((int *)g->data_ptr, g->sz_l * HEIGHT);
	if (kk == 123 || kk == 124)
		(g->center).x += (2 * (kk == 124) - 1) * 10 / (double)g->zoom;
	else if (kk == 125 || kk == 126)
		(g->center).y += (2 * (kk == 125) - 1) * 10 / (double)g->zoom;
	else if (kk == 2 || kk == 0)
		(g->c).x = (g->c.x) + (2 * (kk == 2) - 1) * 1 / (double)(g->zoom);
	else if (kk == 13 || kk == 1)
		(g->c.y) = (g->c.y) + (2 * (kk == 13) - 1) * 1 / (double)(g->zoom);
	else if (kk == 53)
	{
		mlx_destroy_image(g->m_p, g->img_ptr);
		exit(1);
	}
	else if (kk == 35 || kk == 37)
		(g->precision) = (g->precision) + (2 * (kk == 35) - 1) * 2;
	else if (kk == 8)
		g->color_mode = (g->color_mode + 1) % 6;
	start_threads(g);
	return (1);
}

int		mouse_move(int x, int y, void *param)
{
	t_global *g;

	g = param;
	ft_bzero((int *)g->data_ptr, g->sz_l * HEIGHT);
	if (!g->zoom_mode)
	{
		g->c.x = g->center.x + (x - HEIGHT / 2) / (double)g->zoom;
		g->c.y = g->center.y + (HEIGHT / 2 - y) / (double)g->zoom;
	}
	start_threads(g);
	return (1);
}
