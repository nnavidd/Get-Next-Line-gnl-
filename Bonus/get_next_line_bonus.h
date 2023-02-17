/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:30:39 by nnabaeei          #+#    #+#             */
/*   Updated: 2023/02/17 18:02:04 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct t_file_att
{
	int	fd;
	int	line_inx;
}t_file_att;

int			length(char *str);
char		*string_joint(char *str1, char *str2);
int			find_line_inx(char *str);
char		*psudo_strdup(char	*str, int start, int end);
t_file_att	*store_fd_attr(int fd);
char		*fill_spare_up(t_file_att *new_fd, char *spare);
char		*return_line(t_file_att *new_fd, char *spare);
char		*keep_remain(t_file_att *new_fd, char *spare);
char		*get_next_line(int fd);

#endif