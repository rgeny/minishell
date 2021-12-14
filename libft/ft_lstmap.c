/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:47:02 by tokino            #+#    #+#             */
/*   Updated: 2020/12/10 15:47:04 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*clear_all(t_list *lst, void *content, void (*del)(void *))
{
	if (content)
		del(content);
	ft_lstclear(&lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elt;
	void	*new_content;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_content = f(lst->content);
	if (new_content == NULL)
		return (NULL);
	new_lst = ft_lstnew(new_content);
	if (new_lst == NULL)
		return (clear_all(new_lst, new_content, del));
	while (lst->next)
	{
		lst = lst->next;
		new_content = f(lst->content);
		if (new_content == NULL)
			return (clear_all(new_lst, new_content, del));
		new_elt = ft_lstnew(new_content);
		if (new_elt == NULL)
			return (clear_all(new_lst, new_content, del));
		ft_lstadd_back(&new_lst, new_elt);
	}
	return (new_lst);
}
