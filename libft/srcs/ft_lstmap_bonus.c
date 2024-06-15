/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:15:47 by dherszen          #+#    #+#             */
/*   Updated: 2023/10/30 13:45:26 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_tmp;
	t_list	*lst_new;
	t_list	*node;

	if (!lst || !f || !del)
		return (0);
	lst_new = 0;
	lst_tmp = lst;
	while (lst_tmp)
	{
		node = ft_lstnew(f(lst_tmp->content));
		if (!node)
		{
			ft_lstclear(&lst_new, del);
			return (0);
		}
		ft_lstadd_back(&lst_new, node);
		lst_tmp = lst_tmp->next;
	}
	return (lst_new);
}
