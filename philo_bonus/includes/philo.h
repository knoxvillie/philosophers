/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:55:21 by kfaustin          #+#    #+#             */
/*   Updated: 2023/03/30 11:31:50 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>


// Reflects the time in (milliseconds) between initialization of philosophers.
# ifndef SPAWN_RATE
#  define SPAWN_RATE 1
# endif

typedef struct s_god
{
	short	all_ate;
	short	died;
	int		n_meals;
}	t_god;

typedef struct s_philo
{
	int				id;
	int				n_meals;
	long long		t_last_meal;
	sem_t			died;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				n_philo;
	int				n_must_eat;
	int				*pid;
	int				index;
	long long		t_init;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	t_philo			*philosophers;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*end;
	t_god			god;
}	t_data;

//####### ACTION.C #########
void			*ft_action(void *philosopher);
//####### CHECKER.C ########
int				ft_check_data(t_data *data, int argc);
void			ft_god(t_data *data);
int				ft_check_argc(int argc);
int				ft_check_is_num(char **argv);
//####### GENERAL.C ########
int				ft_atoi(const char *str);
int				ft_strlen(const char *str);
long long		ft_get_time(void);
long long		ft_abs_time(t_philo *root);
void			ft_print(t_data *data, char *str);
//####### GENERAL2.C #######
void			ft_destroy_mutex_fork(t_data *data);
void			ft_destroy_free(t_data *data);
void			ft_print_exit(char *str, int flag);
char			*ft_itoa(int number);
//####### INITIALIZE.C ######
void			ft_check_init(t_data *data, int argc, char **argv);
int				ft_initialize_data(t_data *data, int argc, char **argv);
int				ft_initialize_philo(t_data *data);
void			ft_init_semaphore(t_data *data);
int				ft_initialize_simulation(t_data *data);

#endif
