#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*chain;

	if (!lst)
		return (NULL);
	chain = 0;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&chain, del);
			return (NULL);
		}
		ft_lstadd_back(&chain, tmp);
		lst = lst->next;
	}
	return (chain);
}
