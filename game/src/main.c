#include <rcgfw/rcgfw.h>

int main(void)
{
	RcgfwInit("Hello, World!", 800, 600);

	while(!RcgfwWindowShouldClose())
	{
		RcgfwWindowClearScreen(1.0f, 1.0f, 1.0f, 1.0f);

		RcgfwWindowSwap();
	}

	RcgfwClose();

	return 0;
}