/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:01:37 by dherszen          #+#    #+#             */
/*   Updated: 2023/10/30 13:44:40 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp1;
	t_list	*tmp2;

	if (!lst || !del)
		return ;
	tmp1 = *lst;
	tmp2 = tmp1;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		del(tmp1->content);
		free(tmp1);
		tmp1 = tmp2;
	}
	*lst = 0;
}
