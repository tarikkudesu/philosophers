/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:19:00 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/24 14:52:41 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

void	print_status(t_philos *philo, t_status status)
{
	size_t	time;

	time = get_current_time() - philo->table->simu_start_time;
	sem_wait(philo->table->print_s);
	if (status == DIED)
		printf("%zu\t%d\tdied\n", time, philo->philo_id);
	else if (status == FORK)
		printf("%zu\t%d\thas taken a fork\n", time, philo->philo_id);
	else if (status == EATING)
		printf("%zu\t%d\tis eating\n", time, philo->philo_id);
	else if (status == SLEEPING)
		printf("%zu\t%d\tis sleeping\n", time, philo->philo_id);
	else if (status == THINKING)
		printf("%zu\t%d\tis thinking\n", time, philo->philo_id);
	if (status != DIED)
		sem_post(philo->table->print_s);
}

static void	eat(t_philos *philo)
{
	sem_wait(philo->table->fork_s);
	print_status(philo, FORK);
	sem_wait(philo->table->fork_s);
	print_status(philo, FORK);
	print_status(philo, EATING);
	sem_wait(philo->philo_s);
	philo->last_eaten = get_current_time();
	philo->meals_eaten++;
	if (philo->table->meals_nbr != 0 \
		&& philo->meals_eaten == philo->table->meals_nbr)
		sem_post(philo->table->full_s);
	sem_post(philo->philo_s);
	ft_usleep(philo, philo->table->t_eat);
	sem_post(philo->table->fork_s);
	sem_post(philo->table->fork_s);
}

static void	*checker(void *param)
{
	t_philos	*philo;
	size_t		time;

	philo = (t_philos *)param;
	while (true)
	{
		sem_wait(philo->philo_s);
		time = get_current_time() - philo->last_eaten;
		sem_post(philo->philo_s);
		if (time > philo->table->t_die)
		{
			print_status(philo, DIED);
			sem_post(philo->table->end_simu_s);
			break ;
		}
	}
	return (NULL);
}

int	routine(t_philos *philo)
{
	philo->last_eaten = get_current_time();
	if (0 != pthread_create(&philo->thread_id, NULL, &checker, philo))
		return (quit(PTHREAD_CREATE));
	pthread_detach(philo->thread_id);
	if (philo->philo_id % 2)
		ft_usleep(philo, philo->table->t_eat);
	while (1)
	{
		eat(philo);
		print_status(philo, SLEEPING);
		ft_usleep(philo, philo->table->t_sleep);
		print_status(philo, THINKING);
	}
	return (0);
}
