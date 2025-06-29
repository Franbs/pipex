/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:57:01 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/06/29 12:48:00 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_execute(char *cmd, char **envp)
{
	char	*path;
	char	**splitcmd;

	if (!cmd || !*cmd)
	{
		perror("Error");
		exit(127);
	}
	splitcmd = ft_split(cmd, ' ');
	path = ft_findpath(splitcmd[0], envp);
	if (!path)
	{
		ft_freearray(splitcmd);
		ft_erroralternate();
	}
	if (execve(path, splitcmd, envp) == -1)
	{
		free(path);
		ft_freearray(splitcmd);
		ft_erroralternate();
	}
}

void	ft_child1_process(char **av, int *fd, char **envp)
{
	int	fd_in;

	fd_in = open(av[1], O_RDONLY);
	if (fd_in == -1)
		ft_error();
	close(fd[0]);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	ft_execute(av[2], envp);
}

void	ft_child2_process(char **av, int *fd, char **envp)
{
	int	fd_out;

	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		ft_error();
	close(fd[1]);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_execute(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		status;
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
	{
		ft_printf("Error: invalid arguments");
		return (0);
	}
	if (pipe(fd) == -1)
		ft_error();
	pid1 = fork();
	if (pid1 == 0)
		ft_child1_process(av, fd, envp);
	pid2 = fork();
	if (pid2 == 0)
		ft_child2_process(av, fd, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
}
