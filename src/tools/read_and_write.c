/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:07:09 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/10 10:39:09 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_all_pid(t_pipe *pipex);
void	close_all_pipe(t_pipe *pipex, int size);

/*
	Function that read the last file descriptor pipe[0] and output the result
	in the corresponding file descriptor if it's valid.
*/
void	read_and_write_result(t_pipe *pipex)
{
	char		buffer[1001];
	int			nb_read;

	buffer[1000] = 0;
	nb_read = read(pipex->tab_pipe[pipex->size - 1][0], buffer, 1000);
	if (nb_read < 0)
		error_exit(pipex, ERR_READ, 1);
	buffer[nb_read] = 0;
	while (nb_read)
	{
		if (pipex->fd_output != -1 && write(pipex->fd_output, buffer, \
			ft_strlen(buffer)) == -1)
			error_exit(pipex, ERR_WRITE, 1);
		nb_read = read(pipex->tab_pipe[pipex->size - 1][0], buffer, 1000);
		if (nb_read < 0)
			error_exit(pipex, ERR_READ, 1);
		buffer[nb_read] = 0;
	}
	if (pipex->fd_output != -1 && close(pipex->fd_output) == -1)
		error_exit(pipex, ERR_CLOSE, 1);
	close_all_pipe(pipex, pipex->size);
	wait_all_pid(pipex);
	gate_away(pipex);
}

/*
	Function that close all previous opened pipe[0] in the parent program.
*/
void	close_all_pipe(t_pipe *pipex, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (close(pipex->tab_pipe[i][0]) == -1)
			error_exit(pipex, ERR_CLOS_PIP, 1);
		i++;
	}
}

/*
	Function that wait all children pid in the parent program.
*/
void	wait_all_pid(t_pipe *pipex)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->size)
		waitpid(pipex->tab_pid[i++], &status, 0);
}
