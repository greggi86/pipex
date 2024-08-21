/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:02:18 by grbuchne          #+#    #+#             */
/*   Updated: 2024/05/10 19:18:18 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>

// error
# define ERR_ARGC "pipex: wrong number of arguments\n"
# define ERR_INFILE "pipex: "
# define ERR_OUTFILE "pipex: output"
# define ERR_PIPE "pipex: "
# define ERR_FORK "pipex: fork failed\n"
# define ERR_EXECVE "pipex: execve failed\n"
# define ERR_DUP2 "pipex: dup2 failed\n"

typedef struct s_data
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		in;
	int		out;
}				t_data;

int			access_check(char *av);
void		file_error(void);
void		message_error(void);
void		message_fork_error(t_data *data);
void		ft_putendl_fd(char *s, int fd);
int			ft_strlen(char *str);
void		manual_info(char *str);
#endif