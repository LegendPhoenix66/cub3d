/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:19:53 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/10 16:51:56 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include "../../libft/libft.h"
# include <stddef.h>
# include <stdlib.h>

/* Data Structures */
typedef struct s_memory_block
{
	void					*ptr;
	struct s_memory_block	*next;
}							t_memory_block;

/* Function Declarations */
t_memory_block				*create_memory_block(void *ptr);
void						*gc_malloc(size_t size);
void						gc_free(void *ptr);
void						*gc_realloc(void *ptr, size_t new_size);
char						*gc_strdup(const char *s);
void						gc_clean(void);
t_memory_block				**get_memory_list_ptr(void);

#endif // GC_H
