/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 03:12:27 by yait-el-          #+#    #+#             */
/*   Updated: 2019/12/22 05:48:37 by yait-el-         ###   ########.fr       */
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
	else if (key == 49)
		helpful(mlix, 0);
	else if (key == 83)
		helpful(mlix, 1);
	else if (key == 84)
		helpful(mlix, 2);
	else if (key == 85)
		helpful(mlix, 3);
	else if (key == 86)
		helpful(mlix, 4);
	else if (key == 87)
		helpful(mlix, 5);
	else if (key == 88)
		helpful(mlix, 1);
	return (0);
}
