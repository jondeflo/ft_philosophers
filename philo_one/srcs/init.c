/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:40:53 by jondeflo          #+#    #+#             */
/*   Updated: 2021/02/08 15:33:54 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	add_phil(t_main *main, int i)
{
	main->phil[i].num = i;
	main->phil[i].eats = 0;
	if (i == 0)
	{
		main->phil[i].left = &(main->fork[main->cond->num - 1]);
		main->phil[i].right = &(main->fork[i]);
	}
	else if (i == main->cond->num - 1)
	{
		main->phil[i].left = &(main->fork[i - 1]);
		main->phil[i].right = &(main->fork[main->cond->num - 1]);
	}
	else
	{
		main->phil[i].left = &(main->fork[i - 1]);
		main->phil[i].right = &(main->fork[i]);
	}
	main->phil[i].prev_eat = get_time();
	main->phil[i].cond = main->cond;
	main->phil[i].alive = 1;
}

int		make_arrays(t_main *main)
{
	if (!(main->phil = (t_phil*)malloc(sizeof(t_phil) * main->cond->num)))
		return (parce_free(main));
	memset(main->phil, 0, sizeof(t_phil) * main->cond->num);
	if (!(main->fork = (t_fork*)malloc(sizeof(t_fork) * main->cond->num)))
		return (parce_free(main));
	if (!(main->thread =
	(pthread_t*)malloc(sizeof(pthread_t) * main->cond->num)))
		return (parce_free(main));
	if (!(main->cond->print_lock =
	(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
		return (parce_free(main));
	if (pthread_mutex_init((main->cond->print_lock), NULL))
		return (parce_free(main));
	if (!(main->cond->state_lock =
	(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
		return (parce_free(main));
	if (pthread_mutex_init((main->cond->state_lock), NULL))
		return (parce_free(main));
	return (0);
}

void	get_neighbours(t_main *main, int i)
{
	if (i == 0)
	{
		main->phil[i].left_phil = &main->phil[main->cond->num - 1];
		main->phil[i].right_phil = &main->phil[i + 1];
	}
	else if (i == main->cond->num - 1)
	{
		main->phil[i].left_phil = &main->phil[main->cond->num - 2];
		main->phil[i].right_phil = &main->phil[0];
	}
	else
	{
		main->phil[i].left_phil = &main->phil[i - 1];
		main->phil[i].right_phil = &main->phil[i + 1];
	}
}

int		init_phils(t_main *main)
{
	int i;

	i = 0;
	while (i < main->cond->num)
	{
		add_phil(main, i);
		i++;
	}
	i = 0;
	while (i < main->cond->num)
	{
		get_neighbours(main, i);
		i++;
	}
	return (0);
}

int		init_forks(t_main *main)
{
	int i;

	i = 0;
	while (i < main->cond->num)
	{
		if (!(main->fork[i].mutex =
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t))))
			return (parce_free(main));
		if (pthread_mutex_init(main->fork[i].mutex, NULL))
			return (parce_free(main));
		i++;
	}
	return (0);
}
