/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:46:29 by kfaustin          #+#    #+#             */
/*   Updated: 2023/03/30 11:12:06 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_initialize_data(t_data *data, int argc, char **argv)
{
	short	i;

	i = 1;
	data->n_must_eat = -1;
	data->n_philo = ft_atoi(argv[i++]);
	data->t_die = ft_atoi(argv[i++]);
	data->t_eat = ft_atoi(argv[i++]);
	data->t_sleep = ft_atoi(argv[i++]);
	if (argv[i])
		data->n_must_eat = ft_atoi(argv[i]);
	return (ft_check_data(data, argc));
}

int	ft_initialize_print(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL))
	{
		printf("Error: Mutex (print) initialization fails\n");
		return (0);
	}
	return (1);
}

int	ft_initialize_fork(t_data *data)
{
	int	i;
	int	j;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->fork)
	{
		printf("Error: Malloc data->fork fails\n");
		return (0);
	}
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
		{
			pthread_mutex_destroy(&data->print);
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&data->fork[j]);
			free (data->fork);
			printf("Error: Mutex (fork) initialization fails\n");
			return (0);
		}
	}
	return (1);
}

int	ft_initialize_philo(t_data *data)
{
	int	i;

	data->philosophers = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philosophers)
	{
		pthread_mutex_destroy(&data->print);
		ft_destroy_mutex_fork(data);
		free (data->fork);
		printf("Malloc data->philosophers fails\n");
		return (0);
	}
	i = -1;
	while (++i < data->n_philo)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].n_meals = 0;
		data->philosophers[i].l_fork = &data->fork[i];
		data->philosophers[i].r_fork = &data->fork[(i + 1) % data->n_philo];
		data->philosophers[i].data = data;
	}
	return (1);
}

int	ft_initialize_simulation(t_data *data)
{
	int	i;

	data->god.all_ate = 0;
	data->god.died = 0;
	i = -1;
	data->t_init = ft_get_time();
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->philosophers[i].thread,
				NULL, ft_action, &data->philosophers[i]))
		{
			ft_destroy_free(data);
			printf("Error: The simulation fails\n");
			return (0);
		}
		usleep(SPAWN_RATE * 1000);
	}
	ft_god(data);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->philosophers[i].thread, NULL);
	return (1);
}
