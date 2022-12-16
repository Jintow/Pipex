/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:05:11 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/16 21:09:45 by Teiki            ###   ########.fr       */
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

typedef struct s_pipe
{
	int		fd_input;
	int		fd_output;
	int		pipe_current[2];
	int		pipe_previous[2];
	char	***tab_cmd;
	char	**env;
	int		*pid;
}t_pipe;

void	init_information(t_pipe *pipex, int argc, char **argv, char **env);
void	init_cmd(t_pipe *pipex, int argc, char **argv);

#endif