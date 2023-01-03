/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:39:05 by seunghoy          #+#    #+#             */
/*   Updated: 2022/11/26 14:04:18 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);

size_t	s_len(char const *s);
size_t	len_until_char(const char *s, char c, size_t range);
char	*s_join_free_s1(char *s1, char *s2, size_t byte);
char	*sub_s(char const *s, unsigned int start, size_t len);

#endif
