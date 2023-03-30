/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:39:58 by kfaustin          #+#    #+#             */
/*   Updated: 2023/03/30 11:15:36 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_check_data(t_data *data, int argc)
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
		return (0);
	}
	return (1);
}

/**
 * @brief Generic function to check if the number of arguments is correct
 *
 * @param argc	Number of arguments
 * @return int (boolean)
 */
int	ft_check_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (0);
	}
	return (1);
}

int	ft_check_is_num(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("The inputs must be numbers\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_god_complement(t_philo *root)
{
	if ((ft_get_time() - root->t_last_meal) > root->data->t_die)
	{
		ft_print(root, "died");
		root->data->god.died = 1;
		return (1);
	}
	if ((root->n_meals >= root->data->n_must_eat)
		&& root->data->n_must_eat != -1)
		root->data->god.n_meals++;
	if (root->data->god.n_meals == root->data->n_philo)
	{
		ft_print(root, "All philosophers ate\n");
		root->data->god.all_ate = 1;
		return (1);
	}
	return (0);
}

void	ft_god(t_data *data)
{
	int		i;
	t_philo	*root;

	while (1)
	{
		i = -1;
		data->god.n_meals = 0;
		while (++i < data->n_philo)
		{
			root = &data->philosophers[i];
			if (ft_god_complement(root))
				return ;
		}
	}
}
