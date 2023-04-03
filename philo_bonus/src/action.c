+/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:32:25 by kfaustin          #+#    #+#             */
/*   Updated: 2023/03/30 11:17:38 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_sleep(t_data *data)
{
	ft_print(data, "is sleeping");
	usleep(data->t_sleep * 1000);
}

static void	ft_eat(t_data *data)
{
	ft_print(data, "is eating");
	data->philosophers[data->index].t_last_meal = ft_get_time();
	sem_post(data->philosophers[data->index].died);
	usleep(data->t_eat * 1000);
	data->philosophers[data->index].n_meals++;
	sem_post(data->forks);
	sem_post(data->forks);
}

static void	ft_grab_forks(t_data *data)
{
	sem_wait(data->forks);
	ft_print(data, "has taken a fork");
	if (data->n_philo == 1)
	{
		usleep(data->t_eat * 1000);
		return ;
	}
	sem_wait(data->forks);
	ft_print(root, "has taken a fork");
}

void	ft_action(t_data *data)
{
	pthread_t	god;

	pthread_create(&god, NULL, ft_god, data);
	data->philosophers[data->index].t_last_meal = ft_get_time();
	while (1)
	{
		ft_grab_forks(data);
		sem_wait(data->philosophers[data->index].died);
		ft_eat(data);
		ft_sleep(data);
		ft_print(data, "is thinking");
	}
}
