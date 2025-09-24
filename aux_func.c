/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:03:38 by jlopes-c          #+#    #+#             */
/*   Updated: 2025/09/24 11:00:53 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_message(char *str, int status)
{
	printf("%s", str);
	exit(status);
}

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
