/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 03:46:03 by yait-el-          #+#    #+#             */
/*   Updated: 2019/12/23 04:57:31 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

static double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

double			maps(double n, double end1, double start2, double end2)
{
	return (((double)n / (double)end1 * (end2 - start2)) + start2);
}

void			zoom(int x, int y, t_mlix *mlix)
{
	double interpolation;
	double xm;
	double ym;

	xm = maps(x, WIN_X, mlix->key.zoom_rx, mlix->key.zoom_rn);
	ym = maps(y, WIN_Y, mlix->key.zoom_ix, mlix->key.zoom_in);
	interpolation = mlix->kesem;
	mlix->key.zoom_rn = interpolate(xm, mlix->key.zoom_rn, interpolation);
	mlix->key.zoom_rx = interpolate(xm, mlix->key.zoom_rx, interpolation);
	mlix->key.zoom_in = interpolate(ym, mlix->key.zoom_in, interpolation);
	mlix->key.zoom_ix = interpolate(ym, mlix->key.zoom_ix, interpolation);
}
