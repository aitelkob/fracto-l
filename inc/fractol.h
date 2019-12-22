/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 06:19:54 by yait-el-          #+#    #+#             */
/*   Updated: 2019/12/22 05:41:29 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <sys/sysctl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <assert.h>
# include <OpenCL/opencl.h>
# define WIN_X 1000
# define WIN_Y 1000

typedef struct			s_key
{
	double				zoom;
	double				zoom_rn;
	double				zoom_rx;
	double				zoom_in;
	double				zoom_ix;
	int					position_x;
	double				altitude;
	int					position_y;
	unsigned int		parallel;
	double				retation_x;
	double				retation_y;
	double				color_h;
	double				color_l;
	int					menu;
	int					left_button;
}						t_key;

typedef struct			s_opencl
{
	char				*line;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_double			*constants;
	cl_mem				buffer;
	cl_mem				output;
	cl_program			program;
	cl_kernel			kernel;
}						t_opencl;

typedef	struct			s_mlix
{
	void				*ptr;
	void				*win;
	void				*imgptr;
	void				*imgptr2;
	int					w;
	int					h;
	char				*img;
	int					ret;
	char				*data_addr;
	int					shape;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	int					active;
	int					xm;
	int					ym;
	double				mouse_x;
	double				mouse_y;
	int					fd;
	size_t				global_item_size[2];
	size_t				local_item_size;
	size_t				buffer_size;
	int					i;
	float				kesem;
	int					maxiterations;
	t_key				key;
	t_opencl			opencl;
}						t_mlix;

int						mouse_press(int key, int x, int y, t_mlix *mlix);
void					helpful(t_mlix *mlix, int i);
void					resolution(t_mlix *mlix);
int						init_opencl(t_mlix *mlix);
void					opencl(t_mlix *mlix);
void					zoom(int x, int y, t_mlix *mlix);
int						keyhooks(int key, t_mlix *mlix);
double					maps(double n, double end1, double start2, double end2);
void					load_para(t_mlix *mlix);
int						mouse_press(int key, int x, int y, t_mlix *mlix);
int						mouse_move(int x, int y, t_mlix *mlix);
char					*ft_itoa(long long int number);
void					readcl(t_mlix *mlix);

#endif
