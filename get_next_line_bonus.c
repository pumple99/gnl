/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:55:16 by seunghoy          #+#    #+#             */
/*   Updated: 2022/11/26 14:51:27 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_bnode	*find_or_new(int fd, t_bnode **bnode)
{
	t_bnode	*temp;
	t_bnode	*cur;

	cur = *bnode;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		cur = cur->next;
	}
	temp = (t_bnode *)malloc(sizeof(t_bnode));
	if (temp == 0)
		return (0);
	temp->fd = fd;
	temp->backup = 0;
	temp->next = *bnode;
	*bnode = temp;
	return (temp);
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

static char	*re_check(int fd, int *is_malbreak, t_bnode **bnode, char *re_str)
{
	char	**backup;

	backup = &(find_or_new(fd, bnode)->backup);
	if (*is_malbreak)
	{
		free(re_str);
		free(*backup);
		*backup = 0;
		delete_node(fd, bnode);
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
		delete_node(fd, bnode);
	}
	return (re_str);
}

char	*get_next_line(int fd)
{
	static t_bnode	*bnode;
	int				mal_b;
	t_bnode			*n;
	char			**backup;

	mal_b = 0;
	n = find_or_new(fd, &bnode);
	if (n == 0)
		return (0);
	backup = &(n->backup);
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
	{
		free(*backup);
		*backup = 0;
		delete_node(fd, &bnode);
		return (0);
	}
	if (*backup)
	{
		if (len_until_char(*backup, '\n', s_len(*backup)))
			return (re_check(fd, &mal_b, &bnode, getline(backup, &mal_b)));
	}
	read_until_nl(fd, backup, &mal_b);
	return (re_check(fd, &mal_b, &bnode, getline(backup, &mal_b)));
}
