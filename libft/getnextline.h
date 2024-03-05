/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:34:22 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/06 14:44:34 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETNEXTLINE_H
# define GETNEXTLINE_H

# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

// Functions for getnextline
char	*get_next_line(int fd);
size_t	gnl_strlen(const char *s);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
void	*gnl_calloc(size_t nmemb, size_t size);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*gnl_strdup(const char *s);

#endif
