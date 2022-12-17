/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:07:09 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/17 15:20:40 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_and_write_result(t_pipe *pipex)
{
	char		buffer[1001];
	int			nb_read;

	buffer[1000] = 0;
	nb_read = read(pipex->pipe_current[0], buffer, 1000);
	if (nb_read < 0)
		error_exit(pipex, ERR_READ);
	buffer[nb_read] = 0;
	while (nb_read)
	{
		if (write(pipex->fd_output, buffer, ft_strlen(buffer)) == -1)
			error_exit(pipex, ERR_WRITE);
		nb_read = read(pipex->pipe_current[0], buffer, 1000);
		if (nb_read < 0)
			error_exit(pipex, ERR_READ);
		buffer[nb_read] = 0;
	}
	if (close(pipex->pipe_current[0]) == -1)
		error_exit(pipex, ERR_CLOS_PIP);
	if (close(pipex->fd_output) == -1)
		error_exit(pipex, ERR_CLOSE);
	gate_away(pipex);
}
