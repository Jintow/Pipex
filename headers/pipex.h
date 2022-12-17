/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:05:11 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/17 15:24:30 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"

# define ERR_INPUT "Error opening input file"
# define ERR_OUTPUT "Error opening output file"
# define ERR_MALLOC "Error with malloc"
# define ERR_CMD "Error with command"
# define ERR_PIPE "Error with pipe"
# define ERR_FORK "Error while forking"
# define ERR_DUP "Error while executind dup"
# define ERR_READ "Error while reading pipe"
# define ERR_CLOSE "Error while closing file"
# define ERR_CLOS_PIP "Error while closing pipe"
# define ERR_EXEC "Error while executing command"
# define ERR_READ "Error while reading pipe"
# define ERR_WRITE "Error while writing in file"

typedef struct s_pipe
{
	int		fd_input;
	int		fd_output;
	int		pipe_current[2];
	char	***tab_cmd;
	char	**env;
}t_pipe;

void	init_information(t_pipe *pipex, int argc, char **argv, char **env);
void	init_cmd(t_pipe *pipex, int argc, char **argv);
void	pipe_and_exec(t_pipe *pipex);
void	read_and_write_result(t_pipe *pipex);
void	error_exit(t_pipe *pipex, char *err_msg);
void	gate_away(t_pipe *pipex);

#endif