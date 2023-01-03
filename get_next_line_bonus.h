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
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_bnode
{
	int				fd;
	char			*backup;
	struct s_bnode	*next;
}	t_bnode;

//gnl_b.c
char	*get_next_line(int fd);
t_bnode	*find_or_new(int fd, t_bnode **bnode, int *err);

//gnl_utils_b.c
void	delete_node(int fd, t_bnode **bnode);
size_t	s_len(char const *s);
size_t	len_until_nl(const char *s, size_t range);
char	*s_join_free_s1(char *s1, char *s2, size_t byte, int *err);
char	*sub_s(char const *s, unsigned int start, size_t len, int *err);

#endif
