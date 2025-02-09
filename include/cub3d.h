/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuehara <kuehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 07:35:50 by kuehara           #+#    #+#             */
/*   Updated: 2025/02/09 08:18:33 by kuehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include "gc.h"
# include "libft.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

typedef struct s_game
{
	void	*mlx;
	void	*win;
}				t_game;

/*function declaration*/
int		is_valid_extension(const char *filename);
int		key_hook(int keycode, t_game *game);
int		exit_hook(t_game *game);

#endif
