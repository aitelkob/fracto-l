/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainv2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 02:27:52 by yait-el-          #+#    #+#             */
/*   Updated: 2019/12/22 09:44:56 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void		image_parameters(t_mlix *mlix)
{
	char	*iter;

	iter = ft_itoa(mlix->maxiterations);
	mlx_string_put(mlix->ptr, mlix->win, 100, 900, 0xFFFfff, "Iterations:");
	mlx_string_put(mlix->ptr, mlix->win, 200, 900, 0xFFFfff, iter);
	iter = ft_itoa(mlix->key.position_x);
	mlx_string_put(mlix->ptr, mlix->win, 250, 900,
			0xffffff, "MOUSE POSITION X:");
	mlx_string_put(mlix->ptr, mlix->win, 380, 900, 0xffffff, iter);
	iter = ft_itoa(mlix->key.position_y);
	mlx_string_put(mlix->ptr, mlix->win, 430, 900,
			0xFFFfff, "MOUSE POSITION Y:");
	mlx_string_put(mlix->ptr, mlix->win, 560, 900, 0xFFFfff, iter);
}

void		clean_cl(t_mlix *mlix)
{
	clFlush(mlix->opencl.command_queue);
	clFinish(mlix->opencl.command_queue);
	clReleaseKernel(mlix->opencl.kernel);
	clReleaseProgram(mlix->opencl.program);
	clReleaseMemObject(mlix->opencl.output);
	clReleaseMemObject(mlix->opencl.buffer);
	clReleaseCommandQueue(mlix->opencl.command_queue);
	free(mlix->opencl.constants);
}

void		setup_cl(t_mlix *mlix)
{
	int ret;

	ret = 0;
	mlix->opencl.constants = (double *)malloc(sizeof(double) * 7);
	ret = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1,
			&mlix->opencl.device_id, NULL);
	if (mlix->active == 0)
	{
		readcl(mlix);
		mlix->buffer_size = WIN_X * WIN_Y * 4;
		mlix->opencl.context = clCreateContext(NULL, 1,
				&mlix->opencl.device_id, NULL, NULL, &ret);
		mlix->active = 1;
	}
	mlix->opencl.command_queue = clCreateCommandQueue(mlix->opencl.context,
			mlix->opencl.device_id, 0, &ret);
	resolution(mlix);
	mlix->opencl.buffer = clCreateBuffer(mlix->opencl.context,
			CL_MEM_READ_WRITE, sizeof(double) * 8, NULL, &ret);
	mlix->opencl.output = clCreateBuffer(mlix->opencl.context,
			CL_MEM_READ_WRITE, mlix->buffer_size, NULL, &ret);
}

void		open_help(t_mlix *mlix)
{
	mlix->ret = clEnqueueWriteBuffer(mlix->opencl.command_queue,
			mlix->opencl.buffer, CL_FALSE, 0,
			sizeof(cl_double) * 8, mlix->opencl.constants, 0, NULL, NULL);
	mlix->opencl.program = clCreateProgramWithSource(mlix->opencl.context, 1,
			(const char**)&mlix->opencl.line, NULL, &mlix->ret);
	mlix->ret = clBuildProgram(mlix->opencl.program, 1,
			&mlix->opencl.device_id, NULL, NULL, NULL);
	mlix->opencl.kernel = clCreateKernel(mlix->opencl.program,
			"fractals", &mlix->ret);
	mlix->ret = clSetKernelArg(mlix->opencl.kernel, 0,
			sizeof(cl_mem), (void *)&mlix->opencl.output);
	mlix->ret = clSetKernelArg(mlix->opencl.kernel, 1,
			sizeof(cl_mem), (void *)&mlix->opencl.buffer);
	mlix->global_item_size[0] = WIN_X;
	mlix->global_item_size[1] = WIN_Y;
	mlix->ret = clEnqueueNDRangeKernel(mlix->opencl.command_queue,
			mlix->opencl.kernel, 2, NULL,
			mlix->global_item_size, NULL, 0, NULL, NULL);
	mlix->ret = clEnqueueReadBuffer(mlix->opencl.command_queue,
			mlix->opencl.output,
			CL_TRUE, 0, mlix->buffer_size, mlix->img, 0, NULL, NULL);
	mlx_put_image_to_window(mlix->ptr, mlix->win, mlix->imgptr, 0, 0);
}

void		opencl(t_mlix *mlix)
{
	setup_cl(mlix);
	open_help(mlix);
	image_parameters(mlix);
	clean_cl(mlix);
}
