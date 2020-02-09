/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:50:02 by tpokalch          #+#    #+#             */
/*   Updated: 2019/03/09 19:55:25 by tpokalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdio.h>
# include "libft/libft.h"
# include <pthread.h>
# include <math.h>

# define WIDTH 600
# define HEIGHT 600
# define CORES 60

int				mouse_press(int button, int x, int y, void *param);
int				key_press(int kk, void *param);
int				mouse_move(int x, int y, void *param);
void			*fract_to_img(void *p);

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct	s_global
{
	t_vector	c;
	void		*w_p;
	void		*m_p;
	void		*img_ptr;
	int			*data_ptr;
	float		zoom;
	int			precision;
	int			bpp;
	int			sz_l;
	int			e;
	float		bound;
	int			core;
	int			zoom_mode;
	int			color_mode;
	int			fid;
	pthread_t	tid[CORES];
	t_vector	m_pos;
	t_vector	center;
	int			(*fract)(double, double, struct s_global);
}				t_global;

void			copy(t_global *dst, t_global *src);
int				color_mode(int mode);
void			start_threads(t_global *g);
int				color_man(double i, double j, t_global g);
int				color_jul(double i, double j, t_global g);
int				color_jul3(double i, double j, t_global g);
int				color_jul4(double i, double j, t_global g);

#endif
