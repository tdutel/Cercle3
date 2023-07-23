/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:10:06 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/11 14:55:54 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define EXIT_EOF 101

//-----------------INCLUDES-----------------//

//########### PERSONAL LIB HEADERS ##########//

# include "../lib/libft/includes/libft.h"

//########### PROJECT SPECIFICS HEADERS ##########//

# include "builtins.h"
# include "error_message.h"
# include "exec.h"
# include "parsing.h"
# include "sig.h"

//########### SYSTEM LIB HEADERS ##########//

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

//-----------------GLOBAL_VAR-----------------//
extern int	g_return_value;

//-----------------FUNCTION-----------------//
//################# PROMPT.C #################//
char	*get_user_input(t_minishell *data);

# define ROCKET_LOGO "\033[0;31m\n\033[2JBienvenue dans le Minishell de la Team Rocket!\n\n##################################\n\
####################################,\n\
######################################\n\
######################################,\n\
###########               #############\n\
###########               #############\n\
######################################\n\
#####################################*\n\
####################################\n\
#################################/\n\
#################################/\n\
###########           #############\n\
###########            *############\n\
###########              ############.\n\
###########               #############\n\n\033[0m"

# ifndef EASTER_EGG
#  define EASTER_EGG 1
# endif

#endif
