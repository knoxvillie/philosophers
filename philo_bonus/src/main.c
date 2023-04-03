/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:55:16 by kfaustin          #+#    #+#             */
/*   Updated: 2023/03/30 10:55:34 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @param argc	Number of parameters (argc - 1)
 * @param argv	([1] Number of Philosophers - Number of forks;
 * 				[2] Time to die in (ms);
 * 				[3] Time to eat in (ms);
 * 				[3] Time to sleep in (ms);
 * 				[4] OPTIONAL - Number of times each philosopher must eat);
 * @return int
 */

int	main(int argc, char **argv)
{
	t_data	data;

	ft_check_argc(argc);
	ft_check_is_num(argv);
	ft_initialize_data(&data, argc, argv);
	ft_initialize_philo(&data);
	ft_init_semaphore(&data);

	ft_initialize_simulation(&data);
	ft_destroy_free(&data);
	return (0);
}
