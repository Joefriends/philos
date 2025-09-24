/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:52 by jlopes-c          #+#    #+#             */
/*   Updated: 2025/09/24 14:53:47 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_info	t_info;
typedef struct s_philo	t_philo; //maybe making more structs is smarter...

typedef struct s_info //General info, not specific to each philo
{
	int				philo_num; //Number of philos and forks
	int				philo_ttd; //Time it takes for a philo to die (they die if they wont eat within time to die milliseconds)
	int				philo_tte; //The time it takes for a philo to eat
	int				philo_tts; //The amount of time a philo will spend sleeping
	int				philo_num_eat; //The optional arg, if every philo has eaten num_eat times, program ends successfully, if not present, program ends when a philo dies
	pthread_mutex_t	*forks; //Fork Mutex Indicator, lock when a philo grabs a fork, unlock when he's done eating
	t_philo			**philo; // Pointer to the philo struct
	long int		start_philo; //Time at which the simulation begins
	int				simulation_end; // Flag to indicate if the simulation should end for leaks
	int				food_flag; //maybeeeeeeeeee
	pthread_mutex_t	print_lock; //Print Mutex, lock to write current philo action
}	t_info;

typedef struct s_philo //Philo specific information
{
	pthread_t		thread; //Each philo is a thread
	int				times_ate; //Amount of times a specific philo has eaten, relates to philo_num_eat and might be useful to sort a priority system?
	int				id; //Each philo has a specific number, can't be negative and shouldnt pass INTMAX
	int				fork[2]; // Array of forks, each philo has to grab 2 forks to eat properly
	int				is_eating; //Check if philo is eating
	int				is_thinking; //Check if philo is thinking
	int				is_sleeping; //Check if philo is sleeping
	long long		last_meal; // Timestamp of the last time a philo has eaten
	pthread_mutex_t	meal_lock; //Meal Mutex, lock while a philo is eating, inside the mutex adjust the amount of times a philo has eaten and the timestamp of their last meal
	int				is_dead; //Indicates if a philo is dead
	t_info			*info; // Pointer to the info struct..
}	t_philo;
//Parsing
int				ft_atoi(const char *nptr);
int				ft_isdigit(char *str);
int				is_valid(int argc, char **argv);

//Get Time
long long		get_time_in_ms(void);
void			philo_sleep(int ms, t_info *data);
//Initialize
pthread_mutex_t	*initialize_forks(t_info *data);
void			give_forks(t_philo *data);
t_philo			**initialize_philosophers(t_info *data);
void			init_values(char **argv, t_info *data);

//Philo Routine
void			eat_routine(t_philo *data);

//Aux Functions
void			exit_message(char *str, int status);
void			print_current_action(t_philo *data, char *str);

//Free
void			*free_data(t_info *data);
void			mutex_destroy(t_info *data);

#endif