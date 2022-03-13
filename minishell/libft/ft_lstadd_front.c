#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *newlst)
{
	if (*lst)
		newlst->next = *lst;
	*lst = newlst;
}
