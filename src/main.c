/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:56:57 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/16 21:10:27 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	***ft_free_tab3(char ***tab);
char	***make_tab_cmd(char **str, int size);

int	main(int argc, char **argv, char **env)
{
	char	*path_f2;
	char	***tab_cmd;
	int		size_tab;
	int		i;
	t_pipe	pipex;

	pipex.pid = 0;
	if (argc < 4)
		return (0);
	init_information(&pipex, argc, argv, env);
	i = 0;
	while (pipex.env[i])
		ft_printf("%s\n", pipex.env[i++]);
	init_cmd(&pipex, argc - 1, &argv[1]);
	return (0);
}	
	// fd = open(path_f2, O_WRONLY);
	// pipe(fd3);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	close(fd3[0]);
	// 	int fd2 = dup2(fd3[1], 1);
	// 	execve(tab_cmd[0][0], tab_cmd[0], NULL);
	// }
	// wait(NULL);
	// // close(fd3[1]);
	// // close(fd2);
	// int fd5 = dup2(fd3[0], 0);
	// if (pid != 0)
	// {
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{
	// 	execve(tab_cmd[1][0], tab_cmd[1], NULL);
	// 	}
	// }
	// // dprintf(1, "tab : %s\n", buff);
	// char buff[10000];
	// read(fd3[0], buff, 10000);
	// write(fd, buff, ft_strlen(buff));
	// // close(fd2);
	// ft_free_tab3(tab_cmd);
	// ft_printf("Succes free!\n");
	// pipe_and_exec(path_f1, path_f2, tab_cmd);
	// fd3[1] = dup2(fd3[1], 1);
	// pid = fork()
	// i = 0;
	// while (tab_cmd[i])
	// {
	// 	if (pid ==0)
	// 	{

	// 	}
	// }




char	***ft_free_tab3(char ***tab)
{
	int	i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
		ft_free_tab(tab[i++]);
	free(tab);
	return (NULL);
}

//   char *new_argv[] = { "ls", "-l", NULL };
//   char *new_envp[] = { "PATH=/usr/local/bin:/usr/bin:/bin", NULL };

//   execve("/bin/ls", new_argv, NULL);

//   return 0;