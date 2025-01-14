/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_player_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:41:39 by hel-makh          #+#    #+#             */
/*   Updated: 2022/08/17 10:00:24 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_get_player_angle(t_vars *vars)
{
	int		x;
	int		y;

	x = vars->player.pos.x;
	y = vars->player.pos.y;
	if (vars->map.map[y][x] == 'N')
		vars->player.angle = M_PI_2;
	else if (vars->map.map[y][x] == 'S')
		vars->player.angle = M_PI + M_PI_2;
	else if (vars->map.map[y][x] == 'E')
		vars->player.angle = M_PI;
	else if (vars->map.map[y][x] == 'W')
		vars->player.angle = 0;
}

void	ft_get_player_position(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map.map[i])
	{
		j = 0;
		while (vars->map.map[i][j])
		{
			if (ft_strchr("NSEW", vars->map.map[i][j]))
			{
				vars->player.pos.x = (double)j + 0.5;
				vars->player.pos.y = (double)i + 0.5;
				ft_get_player_angle(vars);
			}
			else if (vars->map.map[i][j] == COLLECTIBLE)
				ft_collectible_lstadd_front(&vars->map.collectibles,
					ft_collectible_lstnew(j, i));
			else if (vars->map.map[i][j] == O_DOOR)
				ft_door_lstadd_front(&vars->map.doors,
					ft_door_lstnew(j, i, vars->map.door.frames - 1));
			j ++;
		}
		i ++;
	}
}
