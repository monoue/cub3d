/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwaura <miwaura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 19:45:55 by miwaura           #+#    #+#             */
/*   Updated: 2020/06/29 18:45:09 by miwaura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	ft_get_strat0_end1(char const *s, char c, size_t len, int n)
{
	unsigned int	i;

	if (n == 0)
	{
		i = 0;
		while (i < len && s[i] == c)
			i++;
		return (i);
	}
	i = len;
	while (i > 0 && s[i - 1] == c)
		i--;
	return (i);
}

static int		ft_split_cnt(char const *s, char c, int len)
{
	int	start;
	int	end;
	int	cnt;

	start = ft_get_strat0_end1(s, c, len, 0);
	end = ft_get_strat0_end1(s, c, len, 1);
	cnt = 0;
	while (start < end)
	{
		if (c == s[start] && c != s[start - 1])
			cnt++;
		start++;
	}
	return (cnt);
}

static char		*ft_strndup(char const *s, size_t len)
{
	char	*p;
	size_t	i;

	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static void		ft_do_split(char **p, char const *s, char c, size_t end)
{
	size_t	start;
	size_t	i;
	int		num;

	num = 0;
	start = ft_get_strat0_end1(s, c, end, 0);
	i = start;
	while (start <= end)
	{
		if (s[start] == c || s[start] == '\0')
		{
			if ((p[num] = ft_strndup(&(s[i]), start - i)) == NULL)
			{
				while (num >= 0)
					free(p[num--]);
				free(p);
				p = NULL;
			}
			num++;
			while (s[start + 1] == c)
				start++;
			i = start + 1;
		}
		start++;
	}
}

char			**ft_split(char const *s, char c)
{
	char	**p;
	int		len;
	int		sp_cnt;
	int		end;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	sp_cnt = ft_split_cnt(s, c, len);
	end = ft_get_strat0_end1(s, c, len, 1);
	if (end == 0 && sp_cnt == 0)
	{
		p = (char **)malloc(sizeof(char *) * (1));
		if (p == NULL)
			return (NULL);
		p[0] = NULL;
		return (p);
	}
	p = (char **)malloc(sizeof(char *) * (sp_cnt + 2));
	if (p == NULL)
		return (NULL);
	p[sp_cnt + 1] = NULL;
	ft_do_split(p, s, c, end);
	return (p);
}
