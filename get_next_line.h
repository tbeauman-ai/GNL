/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:15:39 by tbeauman          #+#    #+#             */
/*   Updated: 2024/11/24 15:17:07 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char				*ft_strchr(const char *s, int c);
size_t				ft_strlen(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);
void				*ft_memmove(void *dst, const void *src, size_t len);
char				*ft_strnew(size_t size);
char				*get_next_line(int fd);

static inline int	free_line(char **line)
{
	free(*line);
	*line = 0;
	return (1);
}

#endif