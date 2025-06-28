/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:58:48 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/06/28 20:26:15 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>

// utils.c
void	ft_error(void);
void	ft_erroralternate(void);
char	**ft_splitpath(char **envp);
char	*ft_findpath(char *cmd, char **envp);
void	ft_freearray(char **array);

#endif
