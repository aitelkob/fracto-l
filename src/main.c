/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 04:34:01 by yait-el-          #+#    #+#             */
/*   Updated: 2019/12/22 09:43:15 by yait-el-         ###   ########.fr       */
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
	mlix->maxiterations = 100;
}

int			main(int ac, char **av)
{
	t_mlix	mlix;

	(void)ac;
	(void)av;
	mlix.shape = 1;
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
