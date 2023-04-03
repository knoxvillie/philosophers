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

void	ft_print_exit(char *str, int flag)
{
	printf("%s", str);
	exit (flag);
}

static int	len_number(long num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	else if (num < 0)
	{
		len++;
		num *= -1;
	}
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int number)
{
	int		len;
	long	num;
	char	*str;

	num = number;
	len = len_number(num);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (num == 0)
		str[0] = '0';
	else if (num < 0)
	{
		num *= -1;
		str[0] = '-';
	}
	while (num > 0)
	{
		str[len--] = (48 + (num % 10));
		num /= 10;
	}
	return (str);
}