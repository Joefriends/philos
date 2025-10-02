/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:24:00 by jlopes-c          #+#    #+#             */
/*   Updated: 2025/09/29 12:36:04 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_sleep(int ms, t_info *data)
{
	long long	start;
	long long	now;

	start = get_time_in_ms();
	while (1)
	{
		now = get_time_in_ms();
		if (now - start >= ms || data->simulation_end == 1)
			break ;
		usleep(500);
	}
}
