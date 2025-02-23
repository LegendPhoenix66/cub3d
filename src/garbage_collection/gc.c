/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:20:50 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/23 17:13:08 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	*gc_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	create_memory_block(ptr, size);
	return (ptr);
}

void	*gc_realloc(void *ptr, size_t new_size)
{
	t_memory_block	*block;
	void			*new_ptr;
	size_t			bytes_to_copy;

	if (ptr == NULL)
		return (gc_malloc(new_size));
	block = find_memory_block(ptr);
	if (block == NULL)
		return (NULL);
	new_ptr = gc_malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (block->size < new_size)
		bytes_to_copy = block->size;
	else
		bytes_to_copy = new_size;
	ft_memcpy(new_ptr, ptr, bytes_to_copy);
	gc_free(ptr);
	return (new_ptr);
}

char	*gc_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	dup = gc_malloc(len);
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, s, len);
	return (dup);
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
