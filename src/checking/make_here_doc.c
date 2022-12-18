/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:38:32 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/18 12:51:39 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

char	*get_next_line(int fd, t_pipe *pipex);
void	make_here_doc_tmp_file(t_pipe *pipex);

void	make_here_doc(t_pipe *pipex)
{
	char	*line;

	if (read(STDIN_FILENO, NULL, 0) != 0)
		error_exit3(pipex, ERR_STDIN);
	pipex->here_doc = ft_calloc(1, sizeof(char));
	if (!(pipex->here_doc))
		error_exit(pipex, ERR_MALLOC);
	while (1)
	{
		ft_printf("pipe heredoc> ");
		line = get_next_line(STDIN_FILENO, pipex);
		pipex->here_doc = ft_strjoin_free_s1(pipex->here_doc, line);
		if (!(pipex->here_doc))
			error_exit(pipex, ERR_MALLOC);
		if (ft_strncmp(line, pipex->limiter, ft_strlen(line) - 1) == 0 \
			|| !(ft_strlen(line)))
			break;
		free(line);
	}
	free(line);
	if (ft_strncmp(line, pipex->limiter, ft_strlen(pipex->limiter)))
		error_exit3(pipex, ERR_HERE_DOC);
	make_here_doc_tmp_file(pipex);
}

char	*get_next_line(int fd, t_pipe *pipex)
{
	char	buffer[1001];
	char 	*line;

	ft_bzero(buffer, 1001);
	line = ft_calloc(1, sizeof(char));
	if (!line)
		error_exit(pipex, ERR_MALLOC);
	read(fd, buffer, 1000);
	while (!ft_strrchr(buffer, '\n') && ft_strlen(buffer))
	{
		line = ft_strjoin_free_s1(line, buffer);
		if (!line)
			error_exit(pipex, ERR_MALLOC);
		ft_bzero(buffer, 1001);
		read(STDIN_FILENO, buffer, 1000);
	}
	line = ft_strjoin_free_s1(line, buffer);
	if (!line)
		error_exit(pipex, ERR_MALLOC);
	return (line);
}

void	make_here_doc_tmp_file(t_pipe *pipex)
{
	pipex->fd_input = open("/tmp/pipex_heredoc.txt", O_WRONLY \
	| O_CREAT | O_TRUNC, 0644);
	if (write(pipex->fd_input, pipex->here_doc, ft_strlen(pipex->here_doc)) < 0)
		error_exit(pipex, ERR_HERE_DOC2);
	if (close(pipex->fd_input) == -1)
		error_exit(pipex, ERR_HERE_DOC2);
	pipex->fd_input = open("/tmp/pipex_heredoc.txt", O_RDONLY);
	if (pipex->fd_input == -1)
		error_exit(pipex, ERR_HERE_DOC2);
	if (unlink("/tmp/pipex_heredoc.txt") == -1)
		error_exit(pipex, ERR_UNLINK);
}