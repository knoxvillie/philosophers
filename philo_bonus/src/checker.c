/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:39:58 by kfaustin          #+#    #+#             */
/*   Updated: 2023/03/30 14:17:00 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_check_data(t_data *data, int argc)
{
	if (data->n_philo < 1 || data->t_die < 0 || data->t_eat < 0
		|| data->t_sleep < 0 || (data->n_must_eat < 0 && argc == 6))
	{
		if (data->n_philo < 1)
			printf("Error: Number of Philosopher must be at least 1\n");
		else if (data->t_die < 0)
			printf("Error: Time to die can't be negative\n");
		else if (data->t_eat < 0)
			printf("Error: Time to eat can't be negative\n");
		else if (data->t_sleep < 0)
			printf("Error: Time to sleep can't be negative\n");
		else
			printf("Error: (N.T.E.P.M.E) can't be negative\n");
		exit(1);
	}
}

/**
 * @brief Generic function to check if the number of arguments is correct
 *
 * @param argc	Number of arguments
 * @return int (boolean)
 */
void	ft_check_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments\n");
		exit (1);
	}
}

void	ft_check_is_num(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (j == 0 && argv[i][j] == '-')
				j++;
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("The inputs must be numbers\n");
				exit (1);
			}
			j++;
		}
		i++;
	}
}

void	ft_god(void	*root)
{
	t_data		*data;
	long long	time;

	data = (t_data *)root;
	time = ft_get_time() - data->philosophers[data->index].t_last_meal;
	if (time > data->t_die)
	{
		sem_wait(&data->philosophers[data->index].died);
		ft_print(data, "died");
		sem_post(data->end);
		sem_post(&data->philosophers[data->index].died);
	}
}
