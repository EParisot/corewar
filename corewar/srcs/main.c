/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:06:55 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/11 15:15:40 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		del(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

void		del_champ(void *content, size_t content_size)
{
	(void)content_size;
	free(((t_champ*)content)->name);
	free(((t_champ*)content)->comment);
	free(((t_champ*)content)->prog);
	free(((t_champ*)content)->splited_prog);
	free(((t_champ*)content)->reg);
	ft_lstdel(&((t_champ*)content)->instru, del);
	free(content);
}

static void	free_cor(t_cor *cor)
{
	if (cor)
	{
		if (cor->aff)
			free(cor->aff);
		if (cor->opt && cor->opt->n)
			free(cor->opt->n);
		if (cor->opt)
			free(cor->opt);
		if (cor->champs)
			ft_lstdel(&(cor->champs), del_champ);
		if (cor->map)
			free(cor->map);
		if (cor->c_map)
			free(cor->c_map);
		free(cor);
	}
}

static void	deal_w_error(t_opt *opt, t_cor *cor)
{
	print_usage();
	free(cor);
	free(opt);
}

int			main(int argc, char **argv)
{
	t_opt	*opt;
	t_cor	*cor;

	opt = ft_malloc(sizeof(t_opt), EXIT_FAILURE);
	cor = ft_malloc(sizeof(t_cor), EXIT_FAILURE);
	if (argc == 1)
	{
		deal_w_error(opt, cor);
		exit(EXIT_FAILURE);
	}
	else if (parse_opt(argv, opt, cor) == ERROR)
	{
		deal_w_error(opt, cor);
		exit(EXIT_FAILURE);
	}
	else if (init(argv, cor) == ERROR)
	{
		free_cor(cor);
		exit(EXIT_FAILURE);
	}
	free_cor(cor);
	exit(EXIT_SUCCESS);
}
