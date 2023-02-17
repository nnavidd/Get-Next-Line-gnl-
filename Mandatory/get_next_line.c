/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:30:53 by nnabaeei          #+#    #+#             */
/*   Updated: 2023/01/17 17:21:50 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_spare_up(t_file_att *new_fd, char *spare)
{
	char	*reader;
	int		readout;

	reader = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!reader)
		return (NULL);
	reader[0] = '\0';
	readout = 1;
	while (find_line_inx(spare) == -1 && readout > 0)
	{
		readout = read(new_fd->fd, reader, BUFFER_SIZE);
		if (readout == -1)
			return (free(spare), free(reader), NULL);
		reader[readout] = '\0';
		spare = string_joint(spare, reader);
		if (spare == NULL || length(spare) == 0)
			return (free(spare), free(reader), NULL);
	}
	free(reader);
	return (spare);
}

char	*return_line(t_file_att *new_fd, char	*spare)
{
	char	*line;

	if (spare == NULL || length(spare) == 0)
		return (NULL);
	new_fd->line_inx = find_line_inx(spare);
	if (new_fd->line_inx >= 0)
		return (psudo_strdup(spare, 0, new_fd->line_inx + 1));
	line = psudo_strdup(spare, 0, length(spare));
	return (line);
}

char	*keep_remain(t_file_att *new_fd, char *spare)
{
	char	*new_spare;

	new_spare = NULL;
	if (spare == NULL || length(spare) == 0)
		return (free(spare), NULL);
	if (new_fd->line_inx != -1)
		new_spare = psudo_strdup(spare, new_fd->line_inx + 1, length(spare));
	free (spare);
	return (new_spare);
}

char	*get_next_line(int fd)
{
	static char		*spare;
	char			*line;
	t_file_att		*new_fd;

	if (fd > 1024 || fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (read(fd, NULL, 0) == -1)
		return (free(spare), spare = NULL, NULL);
	new_fd = store_fd_attr(fd);
	spare = fill_spare_up(new_fd, spare);
	line = return_line(new_fd, spare);
	spare = keep_remain(new_fd, spare);
	free(new_fd);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		f1;
// 	int		i;

// 	f1 = open("text1", O_RDONLY);
// 	i = 0;
// 	while (1)
// 	{
// 		line = get_next_line(f1);
// 		printf("%s", line);
// 		if (line == NULL)
// 			break ;
// 	}
// 	return (0);
// }
