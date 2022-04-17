/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 18:19:22 by jondeflo          #+#    #+#             */
/*   Updated: 2021/02/14 13:55:50 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	get_forks(t_phil *tmp)
{
	if (!(tmp->num % 2))
		prec_sleep(50);
	if (sem_wait(tmp->cond->forks) < 0)
		exit(1);
	print_state(tmp, get_time() - tmp->cond->start, 'f');
	if (sem_wait(tmp->cond->forks) < 0)
		exit(1);
	print_state(tmp, get_time() - tmp->cond->start, 'f');
	if (sem_wait(tmp->cond->state) < 0)
		exit(1);
	prec_sleep(25);
	print_state(tmp, get_time() - tmp->cond->start, 'e');
	if (sem_post(tmp->cond->state) < 0)
		exit(1);
	tmp->prev_eat = get_time();
}

void	*checker(void *args)
{
	t_phil	*tmp;

	tmp = (t_phil*)args;
	while (1)
	{
		prec_sleep(50);
		if (get_time() - tmp->prev_eat >= tmp->cond->die)
		{
			print_dead(tmp, (get_time() - tmp->cond->start));
			exit(1);
		}
	}
}

void	*eat(void *args)
{
	t_phil	*tmp;

	tmp = (t_phil*)args;
	if (pthread_create(tmp->thread, NULL, checker, tmp))
		exit(1);
	while (tmp->eats != tmp->cond->limit)
	{
		print_state(tmp, get_time() - tmp->cond->start, 't');
		get_forks(tmp);
		prec_sleep(tmp->cond->eat * 1000);
		if (sem_post(tmp->cond->forks) < 0)
			exit(1);
		if (sem_post(tmp->cond->forks) < 0)
			exit(1);
		tmp->eats++;
		print_state(tmp, get_time() - tmp->cond->start, 's');
		prec_sleep(tmp->cond->sleep * 1000);
	}
	if (pthread_detach(*tmp->thread))
		exit(1);
	exit(0);
}

int		ready_set_go(t_main *main)
{
	int		i;
	size_t	pid;

	i = -1;
	while (++i < main->cond->num)
	{
		pid = fork();
		if (pid == 0)
			eat(&(main->phil[i]));
		if (pid < 0)
			return (1);
		main->phil[i].pid = pid;
	}
	closing(main);
	return (0);
}

int		main(int ac, char **av)
{
	t_main	*main;
	t_cond	*cond;

	if (!(main = (t_main*)malloc(sizeof(t_main))))
		return (print_err("Memory allocation error"));
	if (!(cond = (t_cond*)malloc(sizeof(t_cond))))
		return (print_err("Memory allocation error"));
	main->cond = cond;
	if (ac < 5 || ac > 6)
	{
		printf("Wrong arguments number\n");
		return (parce_free(main));
	}
	if (fill_conditions(av, main) == 1)
		return (print_err("Error in arguments"));
	if (make_arrays(main) == 1)
		return (print_err("Error in semaphore init"));
	if (init_phils(main) == 1)
		return (print_err("Error in semaphore init"));
	if (ready_set_go(main) == 1)
		return (parce_free(main));
	clear_all(main);
	return (0);
}
