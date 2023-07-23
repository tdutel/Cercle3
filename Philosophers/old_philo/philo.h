/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:36:19 by tdutel            #+#    #+#             */
/*   Updated: 2023/03/23 14:40:40 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define SUCCESS 0
# define ERROR 1
# define STDERR 2
# define STR_ERR_SYNTAX "Error : put the instructions in this order : ./philo \
\"nb_philo\" \"time_to_die\" \"time_to_eat\" \"time_to_sleep\" (\"max_nb_eat\")"
# define STR_ERR_THREAD "Thread creation failed"
# define STR_ERR_MALLOC "Memory allocation failed"
# define STR_ERR_MUTEX_INIT "Mutex initialisation failed"
# define STR_ERR_MUTEX_DESTROY "Mutex destroy failed"

typedef struct s_philo	t_philo;
typedef struct s_env	t_env;
typedef struct timeval	t_tval;

typedef enum e_action {
	EAT,
	FORK,
	SLEEP,
	THINK,
	DIED,
}	t_action;

struct s_philo {
	t_env			*env;
	int				index;
	int				right_fork_id;
	int				left_fork_id;
	time_t			last_meal;
	int				nb_meal;
	bool			sated;
	pthread_mutex_t	mutex_meal;
	pthread_t		thread_id;
};

struct s_env {
	int				nb_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	t_philo			*philo;
	int				max_meal;
	time_t			start_time_ms;
	int				stop_sim;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*mutex_tab_fork;
	pthread_mutex_t	mutex_stop_sim;
};

//	philosophers.c	//
void	start_synchro(long long start_time);
void	*philosopher(void *pphilo);

//	parse.c	//
int		parse_fct(char **argv, int argc, t_env *env);

//	init_actions.c	//
int		init_philo(t_env *env, t_philo **philo);
void	eating_fct(t_env *env, t_philo *philo);
void	print_action(t_env *env, t_philo *philo, t_action act, bool died);

//	philo_utils.c	//
int		ft_atoi(const char *str);
time_t	get_time_ms(void);
void	usleep_plus(time_t usec);
bool	clean(t_env *env);
int		write_error(char *str, t_env *env);

//	philo_tools.c	//
int		stop_simulation(t_env *env, bool flag);
void	philo_loop(t_env *env);
bool	is_philo_full(t_env *env, t_philo *philo);

#endif
