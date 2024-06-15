/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:41:34 by dherszen          #+#    #+#             */
/*   Updated: 2023/10/30 15:48:30 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_is_space(const char *nptr, int i)
{
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == ' '))
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	is_neg;

	n = 0;
	is_neg = 1;
	i = ft_is_space(nptr, 0);
	if (nptr[i] == '-')
	{
		is_neg = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
		n = n * 10 + (nptr[i++] - '0');
	return (is_neg * n);
}
