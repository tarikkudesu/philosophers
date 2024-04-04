
#include "../srcs/philos.h"

size_t    get_current_time()
{
	struct timeval  tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void    ft_usleep(size_t micro)
{
	size_t    start_time;

	start_time = get_current_time();
	while (1)
	{
		if (get_current_time() - start_time >= micro)
			break ;
		usleep(50);
	}
}
