/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:55:35 by seunghoy          #+#    #+#             */
/*   Updated: 2022/11/26 15:05:42 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_bnode
{
	int				fd;
	char			*backup;
	struct s_bnode	*next;
}	t_bnode;

char	*get_next_line(int fd);

void	delete_node(int fd, t_bnode **bnode);
size_t	s_len(char const *s);
size_t	len_until_char(const char *s, char c, size_t range);
char	*s_join_free_s1(char *s1, char *s2, size_t byte);
char	*sub_s(char const *s, unsigned int start, size_t len);

#endif
