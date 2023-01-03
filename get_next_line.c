/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:35:42 by seunghoy          #+#    #+#             */
/*   Updated: 2022/11/26 13:46:08 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*getline(char **backup, int *mal_b);

static void	read_until_nl(int fd, char **backup, int *mal_b)
{
	char	buf[BUFFER_SIZE];
	ssize_t	read_byte;

	read_byte = read(fd, buf, BUFFER_SIZE);
	while (read_byte == BUFFER_SIZE)
	{
		*backup = s_join_free_s1(*backup, buf, BUFFER_SIZE);
		if (*backup == 0)
		{
			*mal_b = 1;
			break ;
		}
		if (len_until_char(buf, '\n', BUFFER_SIZE))
			return ;
		read_byte = read(fd, buf, BUFFER_SIZE);
	}
	*backup = s_join_free_s1(*backup, buf, read_byte);
	if (*backup == 0)
		*mal_b = 1;
}

static char	*getline(char **backup, int *mal_b)
{
	size_t	nl_len;
	char	*line;
	char	*temp_backup;

	nl_len = len_until_char(*backup, '\n', s_len(*backup));
	if (nl_len == 0 || nl_len == s_len(*backup))
	{
		line = *backup;
		*backup = 0;
		return (line);
	}
	line = sub_s(*backup, 0, nl_len);
	if (line == 0)
		*mal_b = 1;
	temp_backup = *backup;
	*backup = sub_s(*backup, nl_len, s_len(*backup) - nl_len);
	if (*backup == 0)
		*mal_b = 1;
	free(temp_backup);
	return (line);
}

static char	*re_check(int *is_malbreak, char **backup, char *re_str)
{
	if (*is_malbreak)
	{
		free(re_str);
		free(*backup);
		*backup = 0;
		return (0);
	}
	if (*backup && **backup == 0)
	{
		free(*backup);
		*backup = 0;
	}
	if (re_str && *re_str == 0)
	{
		free(re_str);
		re_str = 0;
	}
	return (re_str);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	int			mal_b;

	mal_b = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		free(backup);
		backup = 0;
		return (0);
	}
	if (backup)
	{
		if (len_until_char(backup, '\n', s_len(backup)))
			return (re_check(&mal_b, &backup, getline(&backup, &mal_b)));
	}
	read_until_nl(fd, &backup, &mal_b);
	return (re_check(&mal_b, &backup, getline(&backup, &mal_b)));
}
