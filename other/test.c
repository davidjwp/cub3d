#include <unistd.h>

#define LEN 25

int	main(void)
{
	for (int i =0; i < LEN; i++)
	{
		write  (1, "[", 1);
		for (int x = 0; x < i; x++)
			write (1, "=", 1);
		for (int y = i; y < LEN - 1; y++)
			write(1 , " ", 1);
		write  (1, "]", 1);
		usleep(100000);
		write (1, "\r", 1);
	}
	write (1, "\n", 1);
	return 0;
}