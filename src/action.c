/* ************************************************************************** */
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

static void	ft_sleep(t_philo *root)
{
	ft_print(root, "is sleeping");
	usleep(root->data->t_sleep * 1000);
}

static void	ft_eat(t_philo *root)
{
	ft_print(root, "is eating");
	root->t_last_meal = ft_get_time();
	usleep(root->data->t_eat * 1000);
	pthread_mutex_unlock(root->l_fork);
	pthread_mutex_unlock(root->r_fork);
	root->n_meals++;
}

static int	ft_grab_forks(t_philo *root)
{
	pthread_mutex_lock(root->l_fork);
	ft_print(root, "has taken a fork");
	if (root->data->n_philo == 1)
	{
		usleep(root->data->t_eat * 1000);
		return (0);
	}
	pthread_mutex_lock(root->r_fork);
	ft_print(root, "has taken a fork");
	return (1);
}

void	*ft_action(void *philosopher)
{
	t_philo	*root;

	root = (t_philo *)philosopher;
	root->t_last_meal = ft_get_time();
	while (1)
	{
		if (root->data->god.died)
			break ;
		if (!ft_grab_forks(root))
			break ;
		if (root->data->god.died)
			break ;
		ft_eat(root);
		if ((root->n_meals == root->data->n_must_eat)
			|| (root->data->god.died || root->data->god.all_ate))
			break ;
		ft_sleep(root);
		if (root->data->god.died)
			break ;
		ft_print(root, "is thinking");
	}
	return ((void *)root);
}
