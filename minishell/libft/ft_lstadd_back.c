#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newlst)
{
	if (!(*lst))
	{
		*lst = newlst;
		return ;
	}
	ft_lstlast(*lst)->next = newlst;
}
