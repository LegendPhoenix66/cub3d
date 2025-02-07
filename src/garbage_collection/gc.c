/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:20:50 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/07 16:20:50 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include <stdlib.h>

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

void	*gc_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	create_memory_block(ptr);
	return (ptr);
}

void	gc_free(void *ptr)
{
	t_memory_block	*current;
	t_memory_block	*prev;
	t_memory_block	*memory_list_head;
	t_memory_block	**memory_list_ptr;

	memory_list_ptr = get_memory_list_ptr();
	memory_list_head = *memory_list_ptr;
	current = memory_list_head;
	prev = NULL;
	while (current != NULL)
	{
		if (current->ptr == ptr)
		{
			if (prev == NULL)
				*memory_list_ptr = current->next;
			else
				prev->next = current->next;
			free(current->ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	gc_clean(void)
{
	t_memory_block	*current;
	t_memory_block	*next_block;
	t_memory_block	*memory_list_head;
	t_memory_block	**memory_list_ptr;

	memory_list_ptr = get_memory_list_ptr();
	memory_list_head = *memory_list_ptr;
	current = memory_list_head;
	while (current != NULL)
	{
		next_block = current->next;
		free(current->ptr);
		free(current);
		current = next_block;
	}
	*memory_list_ptr = NULL;
}
