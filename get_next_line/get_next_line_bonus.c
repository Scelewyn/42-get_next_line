/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:32:33 by mpouce            #+#    #+#             */
/*   Updated: 2022/10/14 14:55:44 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	strfind(char *str, char c, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*abort_mission(char **kill1, char **kill2)
{
	free_data(kill1);
	free_data(kill2);
	return (0);
}

char	*read_file(int fd)
{
	int		sz;
	char	*buf;
	char	*file_str;

	file_str = malloc(BUFFER_SIZE + 1);
	buf = malloc(BUFFER_SIZE + 1);
	file_str[0] = '\0';
	sz = read(fd, buf, BUFFER_SIZE);
	if (sz < 1)
		return (abort_mission(&file_str, &buf));
	while (sz > 0)
	{
		buf[sz] = '\0';
		file_str = ft_strjoin(file_str, buf);
		if (ft_strchr(buf, '\n'))
			break ;
		if (strfind(buf, '\0', sz - 1) != -1)
			return (abort_mission(&file_str, &buf));
		sz = read(fd, buf, BUFFER_SIZE);
	}
	if (buf)
		free(buf);
	return (file_str);
}

char	*extract_next(char **str)
{
	char	*temp;
	char	*ret;
	size_t	i;
	size_t	j;

	if (!*str)
		return (0);
	if (strfind(*str, '\n', ft_strlen(*str)) == -1)
	{
		ret = ft_substr(*str, 0, ft_strlen(*str));
		free_data(str);
		return (ret);
	}
	i = ft_strlen(*str);
	j = ft_strlen(ft_strchr(*str, '\n'));
	ret = ft_substr(*str, 0, i - j + 1);
	temp = *str;
	*str = ft_substr(ft_strchr(*str, '\n'), 1, j);
	if (temp)
		free_data(&temp);
	if (strfind(*str, '\0', 1) != -1)
		free_data(str);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*str[4096];
	char		*temp;

	if (fd == -1)
		return (0);
	if (!str[fd] || str[fd][0] == '\0')
	{
		str[fd] = read_file(fd);
		if (!str[fd])
			return (0);
	}
	if (str[fd] && str[fd][0] != '\0' && ft_strchr(str[fd], '\n') == 0)
	{
		temp = read_file(fd);
		str[fd] = ft_strjoin(str[fd], temp);
		free_data(&temp);
	}
	if (ft_strchr(str[fd], '\0') && ft_strlen(str[fd]) == 1)
	{
		if (str[fd])
			free_data(&str[fd]);
		return (0);
	}
	return (extract_next(&str[fd]));
}
