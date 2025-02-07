/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:05:41 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/06 21:05:57 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include "garbage_collection/gc.h"

int main(void) {
    char *string_ptr;
    string_ptr = (char *)gc_malloc(sizeof(char) * 20);
    sprintf(string_ptr, "Hello GC Simple!");
    printf("Allocated string: %s\n", string_ptr);
    gc_free(string_ptr);

    string_ptr = (char *)gc_malloc(sizeof(char) * 20);
    sprintf(string_ptr, "no free");
    printf("Allocated string: %s\n", string_ptr);
    gc_free(string_ptr);
    printf("Program compiles and runs successfully!\n");
    gc_clean();
    return 0;
}
