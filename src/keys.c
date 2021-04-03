/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 03:12:27 by yait-el-          #+#    #+#             */
/*   Updated: 2019/12/23 21:34:26 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void		readcl(t_mlix *mlix)
{
	struct stat	statbuf;

	mlix->fd = open("src/open.cl", O_RDONLY);
	if (mlix->fd == 0)
		return ;
	stat("src/open.cl", &statbuf);
	mlix->opencl.line = (char *)malloc(statbuf.st_size + 1);
	read(mlix->fd, mlix->opencl.line, statbuf.st_size);
	mlix->opencl.line[statbuf.st_size] = '\0';
	close(mlix->fd);
}

void		ft_exit_clean(t_mlix *mlix)
{
	clReleaseContext(mlix->opencl.context);
	free(mlix->opencl.line);
	mlx_destroy_image(mlix->ptr, mlix->imgptr);
	mlx_destroy_image(mlix->ptr, mlix->imgptr2);
}

void		key_help(int key, t_mlix *mlix)
{
	if (key == 124)
	{
		mlix->key.zoom_rn += 0.01 * (mlix->key.zoom_rx - mlix->key.zoom_rn);
		mlix->key.zoom_rx += 0.01 * (mlix->key.zoom_rx - mlix->key.zoom_rn);
	}
	else if (key == 123)
	{
		mlix->key.zoom_rn -= 0.01 * (mlix->key.zoom_rx - mlix->key.zoom_rn);
		mlix->key.zoom_rx -= 0.01 * (mlix->key.zoom_rx - mlix->key.zoom_rn);
	}
	else if (key == 125)
	{
		mlix->key.zoom_in -= 0.01 * (mlix->key.zoom_ix - mlix->key.zoom_in);
		mlix->key.zoom_ix -= 0.01 * (mlix->key.zoom_ix - mlix->key.zoom_in);
	}
	else if (key == 126)
	{
		mlix->key.zoom_in += 0.01 * (mlix->key.zoom_ix - mlix->key.zoom_in);
		mlix->key.zoom_ix += 0.01 * (mlix->key.zoom_ix - mlix->key.zoom_in);
	}
	opencl(mlix);
}

void		key_color(int key, t_mlix *mlix)
{
	if (key == 15)
	{
		mlix->key.red += 2;
		opencl(mlix);
	}
	else if (key == 11)
	{
		mlix->key.blue += 2;
		opencl(mlix);
	}
	else if (key == 5)
	{
		mlix->key.green += 2;
		opencl(mlix);
	}
}

int			keyhooks(int key, t_mlix *mlix)
{
	if (key == 53)
	{
		ft_exit_clean(mlix);
		exit(0);
	}
	else if (key == 1)
	{
		mlix->maxiterations += 10;
		opencl(mlix);
	}
	key_help(key, mlix);
	key_color(key, mlix);
	return (0);
}
