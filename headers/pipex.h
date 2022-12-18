/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:05:11 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/18 12:56:38 by Teiki            ###   ########.fr       */
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

# define ERR_USER "Error : Pipex must me launch with at least 4 args \
following this pattern:\n\t [input file] [cmd1] [cmd2] ... [cmdn] [output file]\n"
# define ERR_USER_HERE_DOC "Error : Pipex must me launch with at least 5 args \
using the here_doc. It must follow this pattern:\n\t \
[here_doc] [limiter] [cmd1] [cmd2] ... [cmdn] [output file]\n"
# define ERR_STDIN "Error reading standard input\n"
# define ERR_LIMITER "Error : You must specify a non empty string limiter for an here_doc use of pipex\n"
# define ERR_HERE_DOC "\nError : You must specify your limiter at the end of the input\n"
# define ERR_HERE_DOC2 "Error while processing heredoc.txt temporary file"
# define ERR_UNLINK "Error while unlink /tmp/heredoc.txt file"
# define ERR_INPUT "Error opening input file"
# define ERR_OUTPUT "Error opening output file"
# define ERR_MALLOC "Error with malloc"
# define ERR_CMD "Error :command not found: "
# define ERR_PIPE "Error with pipe"
# define ERR_FORK "Error while forking"
# define ERR_DUP "Error while executing dup"
# define ERR_READ "Error while reading pipe"
# define ERR_CLOSE "Error while closing file"
# define ERR_CLOS_PIP "Error while closing pipe"
# define ERR_EXEC "Error while executing command"
# define ERR_WRITE "Error while writing in file"

typedef struct s_pipe
{
	int		fd_input;
	int		fd_output;
	int		pipe_current[2];
	char	***tab_cmd;
	char	**env;
	char	*limiter;
	char	*here_doc;
}t_pipe;

void	init_information(t_pipe *pipex, int argc, char **argv, char **env);
void	make_here_doc(t_pipe *pipex);
void	init_cmd(t_pipe *pipex, int argc, char **argv);
void	pipe_and_exec(t_pipe *pipex);
void	read_and_write_result(t_pipe *pipex);
void	error_exit(t_pipe *pipex, char *err_msg);
void	error_exit2(t_pipe *pipex, int i);
void	error_exit3(t_pipe *pipex, char *err_msg);
void	gate_away(t_pipe *pipex);

#endif