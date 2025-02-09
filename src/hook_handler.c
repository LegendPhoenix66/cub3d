/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:58:40 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/09 10:58:40 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/keysym.h>

int esc_handler(int keycode, void *mlx)
{
    if (keycode == XK_Escape)
    {
        mlx_loop_end(mlx);
    }
    return (0);
}
