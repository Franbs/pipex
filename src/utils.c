/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:06:41 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/06/18 23:59:52 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
}

void	ft_freearray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_splitpath(char **envp)
{
	int		i;
	char	*path;
	char	**dirs;

	path = NULL;
	i = 0;
	while (envp[i] && !path)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i] + 5;
		i++;
	}
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	return (dirs);
}

char	*ft_findpath(char *cmd, char **envp)
{
	int		i;
	char	**dirs;
	char	*tmp;
	char	*fullpath;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	dirs = ft_splitpath(envp);
	if (!dirs)
		return (NULL);
	i = 0;
	fullpath = NULL;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		fullpath = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(fullpath, X_OK) == 0)
			break ;
		free(fullpath);
		fullpath = NULL;
		i++;
	}
	ft_freearray(dirs);
	return (fullpath);
}
