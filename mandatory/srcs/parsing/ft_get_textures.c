/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:00:44 by hel-makh          #+#    #+#             */
/*   Updated: 2022/08/16 14:54:16 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	ft_get_rgb_colors(int *color, char **info)
{
	char	**arr;
	int		rgb[3];

	arr = ft_split(info[1], ',');
	if (ft_arrlen(arr) != 3)
		return (printf("Error\nInvalid RGB format.\n"), ft_free_2d(arr), 0);
	if (!ft_isnumber(arr[0]) || !ft_isnumber(arr[1]) || !ft_isnumber(arr[2]))
		return (printf("Error\nInvalid RGB values.\n"), ft_free_2d(arr), 0);
	rgb[0] = ft_atoi(arr[0]);
	rgb[1] = ft_atoi(arr[1]);
	rgb[2] = ft_atoi(arr[2]);
	arr = ft_free_2d(arr);
	if (rgb[0] < 0 || rgb[0] > 255
		|| rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
		return (printf("Error\nInvalid RGB combination.\n"), 0);
	*color = ft_create_trgb(0, rgb[0], rgb[1], rgb[2]);
	return (1);
}

static int	ft_open_image(t_vars *vars, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(vars->mlx.mlx, path,
			&img->width, &img->height);
	if (!img->img)
		return (printf("Error\nCouldn't load texture: %s\n", path), 0);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
	return (1);
}

int	ft_get_textures(t_vars *vars, char **info)
{
	if (!ft_strcmp(info[0], "NO"))
		return (ft_open_image(vars, &vars->map.north, info[1]));
	else if (!ft_strcmp(info[0], "SO"))
		return (ft_open_image(vars, &vars->map.south, info[1]));
	else if (!ft_strcmp(info[0], "WE"))
		return (ft_open_image(vars, &vars->map.west, info[1]));
	else if (!ft_strcmp(info[0], "EA"))
		return (ft_open_image(vars, &vars->map.east, info[1]));
	else if (!ft_strcmp(info[0], "F"))
		return (ft_get_rgb_colors(&vars->map.fl_color, info));
	else if (!ft_strcmp(info[0], "C"))
		return (ft_get_rgb_colors(&vars->map.ce_color, info));
	printf("Error\nInvalid texture information [%s].\n", info[0]);
	return (0);
}
