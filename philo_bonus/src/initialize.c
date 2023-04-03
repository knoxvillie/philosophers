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

void	ft_initialize_data(t_data *data, int argc, char **argv)
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
	ft_check_data(data, argc);
	data->pid = (int *)malloc(sizeof(int) * data->n_philo);
	if (!data->pid)
		ft_print_exit("Error: Malloc data->pid fails\n", 1);
}

void	ft_initialize_philo(t_data *data)
{
	int	i;

	data->philosophers = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philosophers)
	{
		free (data->pid);
		ft_print_exit("Error: Malloc data->philosophers fails\n", 1);
	}
	i = -1;
	while (++i < data->n_philo)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].n_meals = 0;
		data->philosophers[i].died = sem_open(ft_itoa(i + 1), O_CREAT, 0644, 1);
		printf("Test ITOA %s num: %d\n", ft_itoa(i + 1), i + 1);
		data->philosophers[i].data = data;
	}
}

void	ft_init_semaphore(t_data *data)
{
	sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT, 0644, data->n_philo);
}

void	ft_initialize_simulation(t_data *data)
{
	data->index = -1;
	data->t_init = ft_get_time();
	while (++data->index < data->n_philo)
	{
		data->pid[data->index] = fork();
		if (data->pid[data->index] == 0)
			ft_action(data);
		usleep(SPAWN_RATE * 1000);
	}
}
