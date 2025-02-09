/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:19:53 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/07 16:19:53 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stddef.h>

/* Data Structures */
typedef struct s_memory_block
{
	void					*ptr;
	struct s_memory_block	*next;
}							t_memory_block;

/* Function Declarations */
void						*gc_malloc(size_t size);
void						gc_free(void *ptr);
void						gc_clean(void);
t_memory_block				**get_memory_list_ptr(void);

#endif // GC_H
