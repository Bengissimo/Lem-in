/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:14:57 by ykot              #+#    #+#             */
/*   Updated: 2022/10/03 15:11:51 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static void	ft_newline(char **line, char **str, int *result)
{
	char	*newl;
	char	*temp;

	*result = 0;
	newl = ft_strchr(*str, '\n');
	if (newl)
	{
		temp = ft_strsub(*str, 0, (size_t)(newl - *str));
		if (!temp)
		{
			*result = -1;
			return ;
		}
		*line = temp;
		temp = ft_strsub(*str, newl - *str + 1, \
			ft_strlen(*str) - ((size_t)(newl - *str) + 1));
		if (!temp)
		{
			*result = -1;
			return ;
		}
		ft_strdel(&(*str));
		*str = temp;
		*result = 1;
	}
}

static int	ft_alloc_buf(char **str, char **buf)
{
	char	*temp;

	if (*str)
	{
		temp = ft_strjoin(*str, *buf);
		if (!temp)
			return (-1);
		ft_strdel(&(*str));
		*str = temp;
		return (0);
	}
	else
	{
		*str = ft_strdup(*buf);
		if (!*str)
			return (-1);
		return (0);
	}
}

static void	ft_clr_and_read_buf(int fd, int *ret, char **buf)
{
	ft_strclr(*buf);
	*ret = read(fd, *buf, BUFF_SIZE);
}

static int	ft_ret(int fd, char **str, char **line, int *result)
{
	char	*buf;
	int		ret;

	buf = ft_strnew(BUFF_SIZE);
	if (!buf)
		return (-1);
	ret = read(fd, buf, BUFF_SIZE);
	if (ret == -1)
		return (-1);
	while (ret)
	{
		if (ft_alloc_buf(str, &buf) == -1)
			return (-1);
		ft_newline(line, str, result);
		if (*result)
		{
			ft_strdel(&buf);
			return (*result);
		}
		ft_clr_and_read_buf(fd, &ret, &buf);
		if (ret == -1)
			return (-1);
	}
	ft_strdel(&buf);
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	static char	*str[MAX_FD];
	int			result;

	if (fd < 0 || fd > MAX_FD || BUFF_SIZE <= 0 || !line)
		return (-1);
	if (str[fd])
	{	
		ft_newline(line, &(str[fd]), &result);
		if (result)
			return (result);
	}
	result = ft_ret(fd, &(str[fd]), line, &result);
	if (result)
		return (result);
	if (str[fd] && ft_strlen(str[fd]))
	{
		*line = str[fd];
		str[fd] = NULL;
		return (1);
	}
	return (0);
}*/

// Bengisu's gnl fn below

static int	seek_more_newline(char **remaining, char **line)
{
	char	*p_newline;
	char	*prev;

	p_newline = ft_strchr(*remaining, '\n');
	if (p_newline)
	{
		*p_newline = '\0';
		prev = *remaining;
		*line = ft_strdup(*remaining);
		*remaining = ft_strdup(p_newline + 1);
		ft_strdel(&prev);
		return (1);
	}
	else
	{
		*line = ft_strdup(*remaining);
		ft_strdel(remaining);
	}
	return (0);
}

static void	update_line(char **line, char *buff)
{
	char	*oldline;

	oldline = *line;
	*line = ft_strjoin(*line, buff);
	ft_strdel(&oldline);
}

static int	get_newline(char **line, char *buff, char **left, const int fd)
{
	char	*newline;

	newline = ft_strchr(buff, '\n');
	if (newline)
	{
		*newline = '\0';
		left[fd] = ft_strdup(newline + 1);
		if (!left[fd])
			return (-1);
		update_line(line, buff);
		if (!line)
			return (-1);
		return (1);
	}
	update_line(line, buff);
	if (!line)
		return (-1);
	return (0);
}

static int	read_line(const int fd, char **left, char **line)
{
	char		buff[BUFF_SIZE + 1];
	int			read_bytes;
	int			got;

	while (1)
	{
		read_bytes = read(fd, buff, BUFF_SIZE);
		if (read_bytes == 0 || read_bytes == -1)
		{
			if (ft_strlen(*line) > 0)
				return (1);
			ft_strdel(&left[fd]);
			ft_strdel(line);
			return (read_bytes);
		}
		buff[read_bytes] = '\0';
		got = get_newline(line, buff, left, fd);
		if (got != 0)
			return (got);
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*left[FD_MAX];

	if (fd < 0 || line == NULL || fd >= FD_MAX)
		return (-1);
	if (left[fd] != NULL)
	{
		if (seek_more_newline(&left[fd], line) == 1)
			return (1);
	}
	else
		*line = ft_strnew(1);
	return (read_line(fd, left, line));
}
