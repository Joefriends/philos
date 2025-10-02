/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:03:38 by jlopes-c          #+#    #+#             */
/*   Updated: 2025/10/02 11:09:44 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_current_action(t_philo *data, char *str)
{
	long	time;

	pthread_mutex_lock(&data->info->print_lock);
	if (data->info->simulation_end == 1)
	{
		pthread_mutex_unlock(&data->info->print_lock);
		return ;
	}
	time = get_time_in_ms() - data->info->start_philo;
	printf("[%ld ms] %d%s\n", time, data->id, str);
	pthread_mutex_unlock(&data->info->print_lock);
}

void	create_thrd(t_info *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	if (pthread_create(&monitor, NULL, death_monitor, data) != 0)
		mutex_destroy(data);
	while (i < data->philo_num)
	{
		pthread_create(&data->philo[i]->thread,
			NULL, philo_routine, data->philo[i]);
		i++;
	}
	pthread_join(monitor, NULL);
}

void	end_thrd(t_info *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philo[i]->thread, NULL);
		i++;
	}
}
