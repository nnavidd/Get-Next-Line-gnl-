/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:30:53 by nnabaeei          #+#    #+#             */
/*   Updated: 2023/01/17 17:25:44 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char		*spare[OPEN_MAX];
	char			*line;
	t_file_att		*new_fd;

	if (fd > 1024 || fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	new_fd = store_fd_attr(fd);
	if (read(new_fd->fd, NULL, 0) == -1)
		return (free(spare[new_fd->fd]), spare[new_fd->fd] = NULL,
			free(new_fd), new_fd = NULL, NULL);
	spare[new_fd->fd] = fill_spare_up(new_fd, spare[new_fd->fd]);
	line = return_line(new_fd, spare[new_fd->fd]);
	spare[new_fd->fd] = keep_remain(new_fd, spare[new_fd->fd]);
	free(new_fd);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		f1;
// 	int		i;

// 	f1 = open("text1.txt", O_RDONLY);
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
