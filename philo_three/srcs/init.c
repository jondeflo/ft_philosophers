/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:40:53 by jondeflo          #+#    #+#             */
/*   Updated: 2021/02/14 13:24:51 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	add_phil(t_main *main, int i)
{
	main->phil[i].num = i;
	main->phil[i].eats = 0;
	main->phil[i].prev_eat = get_time();
	main->phil[i].cond = main->cond;
	main->phil[i].alive = 1;
}

int		make_arrays(t_main *main)
{
	if (!(main->phil =
	(t_phil*)malloc(sizeof(t_phil) * main->cond->num)))
		return (parce_free(main));
	memset(main->phil, 0, sizeof(t_phil) * main->cond->num);
	sem_unlink("print");
	if ((main->cond->print = sem_open("print",
	O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (parce_free(main));
	sem_unlink("state");
	if ((main->cond->state = sem_open("state",
	O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (parce_free(main));
	sem_unlink("forks");
	if ((main->cond->forks = sem_open("forks",
	O_CREAT, S_IRWXU, main->cond->num)) == SEM_FAILED)
		return (parce_free(main));
	return (0);
}

int		init_phils(t_main *main)
{
	int i;

	i = 0;
	while (i < main->cond->num)
	{
		add_phil(main, i);
		if (!(main->phil[i].thread =
		(pthread_t*)malloc(sizeof(pthread_t))))
			return (parce_free(main));
		i++;
	}
	return (0);
}

void	closing(t_main *main)
{
	int		i;
	int		stat;

	stat = 0;
	i = 0;
	while (stat == 0 && i < main->cond->num)
	{
		waitpid(-1, &stat, 0);
		i++;
	}
	if (stat)
	{
		i = 0;
		while (i < main->cond->num)
		{
			kill(main->phil[i].pid, SIGINT);
			i++;
		}
	}
}
