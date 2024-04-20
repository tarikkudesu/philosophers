/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:19:00 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/20 11:17:52 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

void	print_status(t_philos *philo, t_status status)
{
	long	time;

	time = get_current_time() - philo->table->simu_start_time;
	sem_wait(philo->table->print_s);
	if (status == DIED)
		printf("%ld\t%d\t%s\n", time, philo->philo_id, "died");
	else if (status == FORK)
		printf("%ld\t%d\t%s\n", time, philo->philo_id, "has taken a fork");
	else if (status == FORK)
		printf("%ld\t%d\t%s\n", time, philo->philo_id, "has taken a fork");
	else if (status == EATING)
		printf("%ld\t%d\t%s\n", time, philo->philo_id, "is eating");
	else if (status == SLEEPING)
		printf("%ld\t%d\t%s\n", time, philo->philo_id, "is sleeping");
	else if (status == THINKING)
		printf("%ld\t%d\t%s\n", time, philo->philo_id, "is thinking");
	if (status != DIED)
		sem_post(philo->table->print_s);
}

static void	eat(t_philos *philo)
{
	sem_wait(philo->philo_s);
	sem_wait(philo->table->fork_s);
	print_status(philo, FORK);
	sem_wait(philo->table->fork_s);
	print_status(philo, FORK);
	print_status(philo, EATING);
	philo->last_eaten = get_current_time();
	philo->meals_eaten++;
	if (philo->table->meals_nbr > 0 \
		&& philo->meals_eaten == philo->table->meals_nbr)
		sem_post(philo->table->full_s);
	ft_usleep(philo, philo->table->t_eat);
	sem_post(philo->table->fork_s);
	sem_post(philo->table->fork_s);
	sem_post(philo->philo_s);
}

static void	*checker(void *param)
{
	t_philos	*philo;

	philo = (t_philos *)param;
	while (1)
	{
		sem_wait(philo->philo_s);
		if (get_current_time() - philo->last_eaten > philo->table->t_die)
		{
			print_status(philo, DIED);
			sem_post(philo->table->end_simu_s);
			break ;
		}
		sem_post(philo->philo_s);
	}
	return (NULL);
}

void	routine(t_philos *philo)
{
	philo->last_eaten = get_current_time();
	pthread_create(&philo->thread_id, NULL, &checker, philo);
	pthread_detach(philo->thread_id);
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo, philo->table->t_eat);
	while (true)
	{
		eat(philo);
		print_status(philo, SLEEPING);
		ft_usleep(philo, philo->table->t_sleep);
		print_status(philo, SLEEPING);
	}
}
