/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:32:33 by mpouce            #+#    #+#             */
/*   Updated: 2022/10/13 19:22:29 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
/*
void	free_data(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = malloc(len + 1);
	if (!str)
		return (0);
	i = 0;
	while ((s + start)[i] != '\0' && i < len)
	{
		str[i] = (s + start)[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = (s1)[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free_data(&s1);
	return (str);
}

*/
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
	{
		free_data(&buf);
		free_data(&file_str);
		return (0);
	}
	while (sz > 0)
	{
		
		buf[sz] = '\0';
		file_str = ft_strjoin(file_str, buf);
		if (ft_strchr(buf, '\n'))
			break ;
		if (strfind(buf, '\0', sz - 1) != -1)
		{
			free_data(&buf);
			free_data(&file_str);
			return (0);
		}
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
	*str = ft_substr(ft_strchr(*str, '\n'), 1, j + 1);
	if (temp)
		free(temp);
	if (extract_next(str) == (void *)0)
		free_data(str);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*str;

	if (!str || str[0] == '\0')
	{
		str = read_file(fd);
		if (!str)
			return (0);
	}
	if (ft_strchr(str, '\0') && ft_strlen(str) == 1)
	{
		if (str)
			free_data(&str);
		return (0);
	}
	if (strfind(str, '\n', ft_strlen(str)) == -1 && ft_strchr(str, '\0' == 0))
		str = ft_strjoin(str, read_file(fd));
	return (extract_next(&str));
}

/*

void	ft_putstr(const char *s)
{
	//write(1, s, ft_strlen(s));
	//write(1, "\n", 1);
	printf("%s\n", s);
}

int main(void)
{
	int fd;

	fd = open("./tests/multiple_nl.txt", O_RDONLY);
	//ft_putstr(get_next_line(fd));
	ft_putstr(get_next_line(fd));
	ft_putstr(get_next_line(fd));
	ft_putstr(get_next_line(fd));

	return 0;
}*/