/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:03:02 by tbeauman          #+#    #+#             */
/*   Updated: 2024/11/24 15:21:13 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *src)
{
	char	*ret;
	char	*tmp;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!ret)
		return (0);
	tmp = ret;
	while (*src)
	{
		*tmp = *src;
		tmp++;
		src++;
	}
	*tmp = 0;
	return (ret);
}

char	*join_buffers(char *buf, char **line)
{
	char	*tmp;

	tmp = ft_strjoin(*line, buf);
	free(*line);
	*line = 0;
	if (!tmp)
		return (0);
	*line = tmp;
	return (*line);
}

char	*fill_currl(char **line)
{
	char	*str;
	char	tmp;
	char	*currl;

	str = ft_strchr(*line, '\n');
	if (str)
	{
		tmp = str[1];
		str[1] = 0;
		currl = ft_strdup(*line);
		if (!currl)
			return (free_line(line), NULL);
		str[1] = tmp;
		return (ft_memmove(*line, &str[1], ft_strlen(str)), currl);
	}
	else if (ft_strlen(*line) > 0)
	{
		currl = ft_strdup(*line);
		if (!currl)
			return (free_line(line), NULL);
		return (free_line(line), currl);
	}
	else
		return (free_line(line), NULL);
}

int	read_process(char **line, int fd)
{
	char	*buf;
	int		rr;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	rr = read(fd, buf, BUFFER_SIZE);
	if (rr < 0 && free_line(&buf))
		return (free_line(line), -1);
	if (rr == 0 && free_line(&buf))
		return (0);
	buf[rr] = 0;
	if (!join_buffers(buf, line))
		return (-1);
	free_line(&buf);
	return (rr);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	int			rr;

	if (fd < 0 || fd > 255)
		return (NULL);
	if (!line)
	{
		line = ft_strnew(1);
		if (!line)
			return (NULL);
	}
	while (!ft_strchr(line, '\n'))
	{
		rr = read_process(&line, fd);
		if (rr == 0)
			break ;
		if (rr == -1)
			return (NULL);
	}
	return (fill_currl(&line));
}
