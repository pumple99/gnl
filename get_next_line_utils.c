/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:38:10 by seunghoy          #+#    #+#             */
/*   Updated: 2022/11/26 13:46:05 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	s_len(char const *s)
{
	size_t	len;

	if (s == 0)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	len_until_char(const char *s, char c, size_t range)
{
	size_t	idx;

	idx = 0;
	while (idx < range && s[idx])
	{
		if (s[idx] == c)
			return (1 + idx);
		idx++;
	}
	return (0);
}

char	*s_join_free_s1(char *s1, char *s2, size_t byte)
{
	size_t	len1;
	size_t	idx;
	char	*sj;

	len1 = s_len(s1);
	if (s2 == 0)
		byte = 0;
	sj = (char *)malloc(len1 + byte + 1);
	if (sj == 0)
	{
		free(s1);
		return (0);
	}
	idx = 0 - 1;
	while (++idx < len1)
		sj[idx] = s1[idx];
	idx = 0 - 1;
	while (++idx < byte)
		sj[len1 + idx] = s2[idx];
	sj[len1 + byte] = 0;
	free(s1);
	return (sj);
}

char	*sub_s(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	idx;

	if (s == 0)
		return (0);
	ss = (char *)malloc(len + 1);
	if (ss == 0)
		return (0);
	idx = 0 - 1;
	while (++idx < len)
		ss[idx] = s[start + idx];
	ss[len] = 0;
	return (ss);
}
