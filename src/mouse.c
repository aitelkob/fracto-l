/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 03:49:58 by yait-el-          #+#    #+#             */
/*   Updated: 2019/12/23 21:34:24 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void			helpful(t_mlix *mlix, int i)
{
	if (i == 0)
	{
		load_para(mlix);
		opencl(mlix);
	}
	else
	{
		mlix->shape = i;
		load_para(mlix);
		opencl(mlix);
	}
}

int				mouse_move(int x, int y, t_mlix *mlix)
{
	mlix->key.position_x = x;
	mlix->key.position_y = y;
	if (mlix->key.left_button)
	{
		mlix->mouse_x = maps(x, WIN_X, mlix->key.zoom_rx, mlix->key.zoom_rn);
		mlix->mouse_y = maps(y, WIN_Y, mlix->key.zoom_ix, mlix->key.zoom_in);
		opencl(mlix);
	}
	return (0);
}

static void		click_color(int color, t_mlix *mlix)
{
	if (color == 1)
	{
		mlix->key.red += 2;
		opencl(mlix);
	}
	else if (color == 2)
	{
		mlix->key.blue += 2;
		opencl(mlix);
	}
	else if (color == 3)
	{
		mlix->key.green += 2;
		opencl(mlix);
	}
}

static void		helpp(t_mlix *mlix)
{
	if (mlix->key.position_y > 0 && mlix->key.position_y < 115)
		helpful(mlix, 1);
	if (mlix->key.position_y > 136 && mlix->key.position_y < 225)
		helpful(mlix, 2);
	if (mlix->key.position_y > 248 && mlix->key.position_y < 344)
		helpful(mlix, 3);
	if (mlix->key.position_y > 364 && mlix->key.position_y < 460)
		helpful(mlix, 4);
	if (mlix->key.position_y > 478 && mlix->key.position_y < 574)
		helpful(mlix, 5);
	if (mlix->key.position_y > 560 && mlix->key.position_y < 690)
		helpful(mlix, 6);
	if (mlix->key.position_y > 742 && mlix->key.position_y < 1000)
		helpful(mlix, 0);
	if (mlix->key.position_y > 695 && mlix->key.position_y < 737
			&& mlix->key.position_x > 1057 && mlix->key.position_x < 1098)
		click_color(1, mlix);
	if (mlix->key.position_y > 698 && mlix->key.position_y < 739
			&& mlix->key.position_x > 1113 && mlix->key.position_x < 1154)
		click_color(2, mlix);
	if (mlix->key.position_y > 700 && mlix->key.position_y < 741
			&& mlix->key.position_x > 1168 && mlix->key.position_x < 1208)
		click_color(3, mlix);
}

int				mouse_press(int key, int x, int y, t_mlix *mlix)
{
	if (mlix->key.position_x > 1032 && mlix->key.position_x < 1273)
		helpp(mlix);
	else if (key == 5)
	{
		mlix->kesem = 0.9;
		zoom(x, y, mlix);
		mlix->maxiterations++;
		opencl(mlix);
	}
	else if (key == 4)
	{
		mlix->kesem = 1.0 / 0.8;
		zoom(x, y, mlix);
		mlix->maxiterations--;
		opencl(mlix);
	}
	else if (key == 1)
		mlix->key.left_button = !mlix->key.left_button;
	return (0);
}
