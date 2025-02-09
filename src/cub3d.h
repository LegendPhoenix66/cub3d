/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:15:31 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/08 22:17:39 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# define DESTROY_NOTIFY 17

# include "garbage_collector/gc.h"
# include "../libft/libft.h"
#include <mlx.h>
#include <stdio.h>

typedef struct s_window
{
    void		*mlx;
    void		*win;
    int			height;
    int			width;
}				t_window;

// check_args.c
void	check_args(int argc, char **argv);

// hook_handler.c
int esc_handler(int keycode, void *mlx);

#endif //CUB3D_H
