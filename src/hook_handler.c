/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:58:40 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/10 21:23:50 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int esc_handler(int keycode, void *mlx)
{
    if (keycode == ESC_KEY)
    {
        #ifdef __linux__
            mlx_loop_end(mlx);
        #else
            mlx_destroy_window(mlx, ((t_game *)mlx)->window.win);
        #endif
        exit(0);
    }
    return (0);
}
