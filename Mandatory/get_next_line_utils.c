/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:27:03 by nnabaeei          #+#    #+#             */
/*   Updated: 2023/01/13 16:46:39 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_file_att	*store_fd_attr(int fd)
{
	t_file_att	*new_fd;

	new_fd = malloc (sizeof(t_file_att));
	if (!new_fd)
		return (NULL);
	new_fd->fd = fd;
	return (new_fd);
}

int	find_line_inx(char *str)
{
	int	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	length(char *str)
{
	size_t	i;

	i = 0;
	while (*str != '\0')
	{
		str++;
		i++;
	}
	return (i);
}

char	*string_joint(char *str1, char *str2)
{
	size_t	len;
	size_t	i1;
	size_t	i2;
	char	*string;

	if (str1 == NULL)
	{
		str1 = malloc(1);
		str1[0] = '\0';
	}
	len = length(str1) + length(str2) + 1;
	string = malloc(sizeof(char) * len);
	if (!string)
		return (NULL);
	i1 = -1;
	i2 = -1;
	while (str1[++i1] != '\0')
		string[i1] = str1[i1];
	while (str2[++i2] != '\0')
		string[i1 + i2] = str2[i2];
	string[i1 + i2] = '\0';
	free(str1);
	return (string);
}

char	*psudo_strdup(char	*str, int start, int end)
{
	char	*string;
	int		i;

	string = malloc(sizeof(char) * end - start + 1);
	if (!string)
		return (NULL);
	i = 0;
	while ((start + i) < end)
	{
		string[i] = str[start + i];
		i++;
	}
	string[i] = '\0';
	return (string);
}
