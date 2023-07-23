/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/16 20:59:14 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**init_shell_env(char **envp);
void		init_secret_array(t_minishell *data);
static void	in_main(t_var *var, t_minishell *data);

int		g_return_value = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	t_var		var;

	(void)argc;
	(void)argv;
	data.sig = malloc(sizeof(t_sig));
	if (!data.sig)
		exit_sig();
	init_sigaction(data.sig);
	var.sig = data.sig;
	if (EASTER_EGG == 1)
		init_secret_array(&data);
	data.envp = init_shell_env(envp);
	var.env_cpy = data.envp;
	printf(ROCKET_LOGO);
	var.str_in = get_user_input(&data);
	var.str = ft_space_str(&var);
	while (42)
		in_main(&var, &data);
	return (0);
}

static void	in_main(t_var *var, t_minishell *data)
{
	if (!var->str_in)
	{
		clear_history();
		ft_free_secure(&var->str_in);
		ft_free_secure(&var->str);
		ft_free_array((void **)data->envp);
		ft_free_array((void **)data->secret_array);
		ft_printf("exit\n");
		ft_free_sig(&var->sig);
		exit(EXIT_SUCCESS);
	}
	if (var->str)
	{
		if (var->str_in && *(var->str_in))
			add_history(var->str_in);
		data->token_list = get_token_list(var);
		free_var(var);
		if (data->token_list)
			master_exec(data);
		else
			token_clear(&data->token_list);
	}
	var->str_in = get_user_input(data);
	var->str = ft_space_str(var);
	var->env_cpy = data->envp;
}

char	**init_shell_env(char **envp)
{
	char	**new_envp;
	char	*pwd;
	char	*old_pwd;
	char	*shlvl;

	if (envp[0])
	{
		new_envp = (char **)ft_array_dup((void **)envp, false, true);
	}
	else
	{
		new_envp = ft_calloc(5, sizeof (char *));
		pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
		new_envp[0] = pwd;
		old_pwd = ft_strdup("OLDPWD");
		new_envp[1] = old_pwd;
		shlvl = ft_strdup("SHLVL=1");
		new_envp[2] = shlvl;
		new_envp[3] = ft_strdup("PATH=");
	}
	return (new_envp);
}

void	init_secret_array(t_minishell *data)
{
	char	*pwd;

	if (EASTER_EGG == false)
		data->secret_array = NULL;
	else
	{
		data->secret_array = ft_calloc(3, sizeof(char *));
		data->secret_array[0] = ft_strdup("/usr/bin/eog");
		pwd = getcwd(NULL, 0);
		data->secret_array[1] = ft_strjoin(
				pwd, "/assets/secret.gif");
		free(pwd);
	}
}
