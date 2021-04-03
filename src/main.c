/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 04:34:01 by yait-el-          #+#    #+#             */
/*   Updated: 2019/12/23 22:36:09 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void		resolution(t_mlix *mlix)
{
	mlix->opencl.constants[0] = mlix->key.zoom_rn;
	mlix->opencl.constants[1] = mlix->key.zoom_rx;
	mlix->opencl.constants[2] = mlix->key.zoom_in;
	mlix->opencl.constants[3] = mlix->key.zoom_ix;
	mlix->opencl.constants[4] = mlix->mouse_x;
	mlix->opencl.constants[5] = mlix->maxiterations;
	mlix->opencl.constants[6] = mlix->mouse_y;
	mlix->opencl.constants[7] = mlix->shape;
	mlix->opencl.constants[8] = mlix->key.red;
	mlix->opencl.constants[9] = mlix->key.blue;
	mlix->opencl.constants[10] = mlix->key.green;
}

void		load_para(t_mlix *mlix)
{
	mlix->key.left_button = 0;
	mlix->active = 0;
	mlix->kesem = 0;
	mlix->key.zoom_rn = 2;
	mlix->key.zoom_rx = -2;
	mlix->key.zoom_in = 2;
	mlix->key.zoom_ix = -2;
	mlix->ret = 0;
	mlix->key.zoom = 0.09;
	mlix->key.position_x = 0;
	mlix->key.position_y = 0;
	mlix->key.red = 0;
	mlix->key.blue = 0;
	mlix->key.green = 0;
	mlix->maxiterations = 100;
}

void		menu(int ac, char **av, t_mlix *mlix)
{
	if (ac == 2 && !av[1][1] && av[1][0] < '7' && av[1][0] > '0')
		mlix->shape = av[1][0] - 48;
	else
	{
		ft_putendl("\nChose one of the following types of fractals:\
				\n 1 - Mandelbrot \n 2 - Julia \n 3 - cubic Mandelbar\
				\n 4 - Mandelbrot 4th Order  \n 5 - cubic Mandelbrot\
				\n 6 - Partial Cubic Buffalo Real \n");
		exit(0);
	}
}

int			main(int ac, char **av)
{
	t_mlix	mlix;

	menu(ac, av, &mlix);
	load_para(&mlix);
	mlix.ptr = mlx_init();
	mlix.win = mlx_new_window(mlix.ptr, 1273, 1000, "FRACTOL");
	mlix.imgptr2 = mlx_png_file_to_image(mlix.ptr,
			"src/img.png", &mlix.w, &mlix.h);
	mlix.imgptr = mlx_new_image(mlix.ptr, WIN_X, WIN_Y);
	mlix.img = mlx_get_data_addr(mlix.imgptr,
			&mlix.bits_per_pixel, &mlix.size_line, &mlix.endian);
	mlx_put_image_to_window(mlix.ptr, mlix.win, mlix.imgptr2, 0, 0);
	opencl(&mlix);
	mlx_hook(mlix.win, 2, 0, keyhooks, &mlix);
	mlx_hook(mlix.win, 4, 0, mouse_press, &mlix);
	mlx_hook(mlix.win, 6, 0, mouse_move, &mlix);
	mlx_loop(mlix.ptr);
	return (0);
}
