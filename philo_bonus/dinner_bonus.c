/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:19:00 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/15 10:03:10 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

void	print_status(t_philos *philo, t_status status)
{
	long	time_stamp;

	time_stamp = get_current_time() - philo->table->simu_start_time;
	if (-1 == sem_wait(philo->table->print_s))
		quit(SEM_WAIT);
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
	if (-1 == sem_post(philo->table->print_s))
		quit(SEM_POST);
}

void	eating(t_philos *philo)
{

	sem_wait(philo->right_fork->fork_s);
	print_status(philo, FORK);
	sem_wait(philo->left_fork->fork_s);
	print_status(philo, FORK);
	print_status(philo, EATING);
	philo->last_eaten = get_current_time();
	philo->meals_eaten++;
	ft_usleep(philo, philo->table->t_eat);
	sem_post(philo->right_fork->fork_s);
	sem_post(philo->left_fork->fork_s);
}

void	*checker(void *param)
{
	t_philos	*philo;

	philo = (t_philos *)param;
	while (1)
	{
		if (get_current_time() - philo->last_eaten > philo->table->t_die)
		{
			print_status(philo, DIED);
			sem_wait(philo->table->print_s);
			philo->full = true;
			break ;
		}
	}
	return (NULL);
}

void	routine(t_philos *philo)
{
	philo->last_eaten = get_current_time();
	if (0 != pthread_create(&philo->thread_id, NULL, checker, philo))
	{
		quit(PTHREAD_CREATE);
		return ;
	}

	if (philo->philo_id % 2)
		ft_usleep(philo, philo->table->t_eat);
	while (philo->full == false)
	{
		eating(philo);
		if (philo->table->meals_nbr > 0 && philo->meals_eaten \
				== philo->table->meals_nbr)
			break ;
		print_status(philo, SLEEPING);
		ft_usleep(philo, philo->table->t_sleep);
		print_status(philo, THINKING);	
	}
	if (0 != pthread_join(philo->thread_id, NULL))
	{
		quit(PTHREAD_CREATE);
		return ;
	}
	exit(0);

}

int	dinner_served(t_table *table)
{
	t_philos	*philos;
	long		i;

	i = -1;
	philos = table->philos;
	table->simu_start_time = get_current_time();
	while (++i < table->philos_n)
	{
		philos[i].pid = fork();
		if (-1 == philos[i].pid)
			return (quit(ERROR_FORK));
		if (0 == philos[i].pid)
			routine(philos + i);
	}
	/* for (int i = 0; i < table->philos_n; i++) { */
	wait(NULL);
	
	/* } */
	return (0);
}

