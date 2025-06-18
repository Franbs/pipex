/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:58:48 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/06/18 23:51:05 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>

// utils.c
void	ft_error(char *str);
char	**ft_splitpath(char **envp);
char	*ft_findpath(char *cmd, char **envp);
void	ft_freearray(char **array);

#endif
