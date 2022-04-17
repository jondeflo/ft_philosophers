/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 18:19:19 by jondeflo          #+#    #+#             */
/*   Updated: 2021/02/10 16:36:31 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int		print_err(char *str)
{
	printf("%s\n", str);
	return (1);
}

int		print_state(t_phil *tmp, size_t time, char state)
{
	if (pthread_mutex_lock(tmp->cond->print_lock))
		return (1);
	if (state == 'f')
		printf("%11lu %d has taken a fork\n", time, tmp->num + 1);
	else if (state == 'e' && tmp->alive == 1)
		printf("%11lu %d is eating\n", time, tmp->num + 1);
	else if (state == 's')
		printf("%11lu %d is sleeping\n", time, tmp->num + 1);
	else if (state == 't')
		printf("%11lu %d is thinking\n", time, tmp->num + 1);
	if (pthread_mutex_unlock(tmp->cond->print_lock))
		return (1);
	return (0);
}

int		print_dead(t_phil *tmp, size_t time)
{
	if (pthread_mutex_lock(tmp->cond->print_lock))
		return (1);
	printf("%11lu %d died\n", time, tmp->num + 1);
	return (0);
}

size_t	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	prec_sleep(size_t time)
{
	struct timeval	current;
	struct timeval	target;

	gettimeofday(&current, NULL);
	while (1)
	{
		usleep(25);
		gettimeofday(&target, NULL);
		if (((target.tv_sec - current.tv_sec) * 1000000 +
		target.tv_usec - current.tv_usec) >= (long)time)
			break ;
	}
}
