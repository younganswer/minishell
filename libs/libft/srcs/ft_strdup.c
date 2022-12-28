#include "../incs/libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	char	*res;
	size_t	len;

	len = ft_strlen(str);
	res = (char *) ft_calloc(len + 1, sizeof(char), "");
	if (!res)
		return (0);
	ft_strlcpy(res, str, len + 1);
	return (res);
}
