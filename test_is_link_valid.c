#include <stdio.h>
#include "libft/libft.h"

int is_link_valid(t_list *rooms, char *line);

int main(void)
{
	t_list *lst1 = ft_lstnew("room1", 6);
	t_list *lst2 = ft_lstnew("room2", 6);
	t_list *lst3 = ft_lstnew("room3", 6);

	ft_lstappend(&lst1, lst2);
	ft_lstappend(&lst2, lst3);

	/*print the list to check order */
	t_list *curr = lst1;
	while (curr)
	{
		printf("%s\n", (char *)curr->content);
		curr = curr->next;
	}

	printf("is_valid: %d\n", is_link_valid(lst1, "room1-a"));
	printf("is_valid: %d\n", is_link_valid(lst1, "room1-room2"));
	printf("is_valid: %d\n", is_link_valid(lst1, "room1-room1"));
	printf("is_valid: %d\n", is_link_valid(lst1, "room1-"));

	return (0);
}
