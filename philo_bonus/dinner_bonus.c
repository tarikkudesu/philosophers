/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:19:00 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/18 11:24:03 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

void	print_status(t_philos *philo, t_status status)
{
	long	time_stamp;

	time_stamp = get_current_time() - philo->table->simu_start_time;
	sem_wait(philo->table->print_s);
	if (status == DIED)
		printf("%ld\t%d\t%s\n", time_stamp, philo->philo_id, "died");
	else if (status == FORK)
		printf("%ld\t%d\t%s\n", time_stamp, philo->philo_id, "has taken a fork");
	else if (status == FORK)
		printf("%ld\t%d\t%s\n", time_stamp, philo->philo_id, "has taken a fork");
	else if (status == EATING)
		printf("%ld\t%d\t%s\n", time_stamp, philo->philo_id, "is eating");
	else if (status == SLEEPING)
		printf("%ld\t%d\t%s\n", time_stamp, philo->philo_id, "is sleeping");
	else if (status == THINKING)
		printf("%ld\t%d\t%s\n", time_stamp, philo->philo_id, "is thinking");
	if (status != DIED)
		sem_post(philo->table->print_s);
}

void	eat(t_philos *philo)
{
	sem_wait(philo->philo_s);
	sem_wait(philo->table->fork_s);
	print_status(philo, FORK);
	sem_wait(philo->table->fork_s);
	print_status(philo, FORK);
	print_status(philo, EATING);
	philo->last_eaten = get_current_time();
	philo->meals_eaten++;
	if (philo->table->meals_nbr > 0 && philo->meals_eaten == philo->table->meals_nbr)
		sem_post(philo->table->full_s);
	ft_usleep(philo, philo->table->t_eat);
	sem_post(philo->table->fork_s);
	sem_post(philo->table->fork_s);
	sem_post(philo->philo_s);
}

void	*checker(void *param)
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
	pthread_create(&philo->thread_id, NULL, checker, philo);
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

void	*f(void *param)
{
	long	i;
	t_table	*table;

	i = -1;
	table = (t_table *)param;
	while (++i < table->philos_n)
		sem_wait(table->full_s);
	sem_post(table->end_simu_s);
	return (NULL);
}

void	kill_them(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->philos_n)
		kill((table->philos + i)->pid, SIGKILL);
}


int	dinner_served(t_table *table)
{
	long		i;
	pthread_t	tid;

	i = -1;
	table->simu_start_time = get_current_time();
	while (++i < table->philos_n)
	{
		(table->philos + i)->pid = fork();
		if (-1 == (table->philos + i)->pid)
			return (quit(ERROR_FORK));
		if (0 == (table->philos + i)->pid)
			routine(table->philos + i);
	}
	pthread_create(&tid, NULL, f, table);
	pthread_detach(tid);
	sem_wait(table->end_simu_s);
	kill_them(table);
	return (0);
}

