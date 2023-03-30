/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:28:20 by kfaustin          #+#    #+#             */
/*   Updated: 2023/03/30 13:08:21 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += (*str - '0');
		str++;
	}
	return (result * sign);
}

long long	ft_get_time(void)
{
	struct timeval	time;
	long long		time_ms;

	gettimeofday(&time, NULL);
	time_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_ms);
}

long long	ft_abs_time(t_philo *root)
{
	return (ft_get_time() - root->data->t_init);
}

void	ft_print(t_philo *root, char *str)
{
	long long	time_ms;

	time_ms = (ft_get_time() - root->data->t_init);
	pthread_mutex_lock(&root->data->print);
	if (root->data->god.all_ate || root->data->god.died)
	{
		pthread_mutex_unlock(&root->data->print);
		return ;
	}
	printf("%lld %d %s\n", time_ms, root->id, str);
	pthread_mutex_unlock(&root->data->print);
}
