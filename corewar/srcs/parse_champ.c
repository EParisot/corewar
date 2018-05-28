/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 23:28:10 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/28 20:01:11 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static t_list	*check_len(t_list *instru, int size, char **text)
{
	int		i;
	char	*add;

	i = 0;
	if (!(*text = ft_strnew(size + 1)))
		exit(EXIT_FAILURE);
	while (instru && (i += 4))
	{
		if (i == size)
		{
			if (ft_atoi(instru->content) != 0)
				return (NULL);
			else
				break ;
		}
		if (ft_atoi(instru->content) != 0)
		{
			add = translate(ft_atoi(instru->content));
			ft_strcat(*text, add);
			free(add);
		}
		instru = instru->next;
	}
	if (!instru)
		return (NULL);
	return (instru->next);
}

static int		check_prog_len(t_list *instru, int size, char **text)
{
	int		i;
	char	*add;

	i = 0;
	if (!(*text = ft_strnew(size * 2 + 1)))
		exit(EXIT_FAILURE);
	while (instru && (i += 4))
	{
		if (i > size && (size % 4) != 0)
		{
			if (size % 4 == 3)
				add = ft_itoa_base(ft_atoi(instru->content) >> 8, 16);
			else if (size % 4 == 2)
				add = ft_itoa_base(ft_atoi(instru->content) >> 16, 16);
			else if (size % 4 == 1)
				add = ft_itoa_base(ft_atoi(instru->content) >> 24, 16);
			ft_strcat(*text, add);
			free(add);
			(*text)[size * 2] = '\0';
		}
		else
		{
			add = ft_itoa_base(ft_atoi(instru->content), 16);
			if (ft_strlen(add) < 8)
				pad(&add);
			ft_strcat(*text, add);
			free(add);
		}
		instru = instru->next;
	}
	return (SUCCESS);
}

static int		check_champ_bis(t_list *instru, t_champ **champ, char *path)
{
	if (((*champ)->op_nb = ft_atoi(instru->content)) > CHAMP_MAX_SIZE)
	{
		ft_printf("{red}error : champion '%s' has wrong length{eoc}\n",\
			path);
		return (ERROR);
	}
	if (!(instru = check_len(instru->next, COMMENT_LENGTH, &(*champ)->comment)))
	{
		ft_printf("{red}error : champion '%s' has wrong comment length{eoc}\n",\
			path);
		return (ERROR);
	}
	if (check_prog_len(instru->next, (*champ)->op_nb, &(*champ)->prog) == ERROR) //PROTECT from less than size
	{
		ft_printf("{red}error : champion '%s' has wrong length{eoc}\n",\
			path);
		return (ERROR);
	}
	//TODO Check prog (operations conformity)
	//DEBUG
	ft_printf("champ name = %s, op_nb = %d, comment = %s, prog = %s\n", (*champ)->name, (*champ)->op_nb, (*champ)->comment, (*champ)->prog);
	return (SUCCESS);
}

int				check_champ(t_champ **champ, char *path)
{
	t_list	*instru;

	if (!(instru = (*champ)->instru))
	{
		ft_printf("{red}error : champion '%s' is empty{eoc}\n", path);
		return (ERROR);
	}
	if (ft_atoi(instru->content) != COREWAR_EXEC_MAGIC)
	{
		ft_printf("{red}error : champion '%s' has wrong CEM{eoc}\n", path);
		return (ERROR);
	}
	if (!(instru = check_len(instru->next, PROG_NAME_LENGTH, &(*champ)->name)))
	{
		ft_printf("{red}error : champion '%s' has wrong name length{eoc}\n", \
			path);
		return (ERROR);
	}
	if (check_champ_bis(instru->next, champ, path) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
