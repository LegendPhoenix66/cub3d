/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:42:16 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/10 16:49:16 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

/* Function to get the memory list */
t_memory_block	**get_memory_list_ptr(void)
{
	static t_memory_block	*memory_list = NULL;

	return (&memory_list);
}

t_memory_block	*create_memory_block(void *ptr)
{
	t_memory_block	*block;
	t_memory_block	**memory_list_ptr;

	block = malloc(sizeof(t_memory_block));
	if (block == NULL)
	{
		free(ptr);
		return (NULL);
	}
	block->ptr = ptr;
	memory_list_ptr = get_memory_list_ptr();
	block->next = *memory_list_ptr;
	*memory_list_ptr = block;
	return (block);
}
