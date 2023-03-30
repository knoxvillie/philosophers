/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:24:30 by kfaustin          #+#    #+#             */
/*   Updated: 2023/03/30 11:31:35 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_destroy_mutex_fork(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_destroy(&data->fork[i]);
}

void	ft_destroy_free(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->print);
	while (++i < data->n_philo)
		pthread_mutex_destroy(&data->fork[i]);
	free (data->fork);
	free (data->philosophers);
}
