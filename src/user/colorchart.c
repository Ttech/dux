/*
void print_number_width(int n, char width)
{
	static char* spaces = "        "; // 8
	if (n >= 10)       { width--; }
	if (n >= 100)      { width--; }
	if (n >= 1000)     { width--; }
	if (n >= 10000)    { width--; }
	if (n >= 100000)   { width--; }
	if (n >= 1000000)  { width--; }
	if (n >= 10000000) { width--; }
	printf("%i%s", n, spaces + (9 - width));
}
*/

void color_chart()
{
	char bgcolor, fgcolor;
	
	for (fgcolor = 0; fgcolor < 16; fgcolor++)
	{
		if (fgcolor < 2)
		{
			screen_setattr(0x70 + fgcolor, 0x70 + fgcolor);
			printf(" %i   ", fgcolor);
		}
		else if (fgcolor < 10)
		{
			screen_setattr(fgcolor, fgcolor);
			printf(" %i   ", fgcolor);
		}
		else
		{
			screen_setattr(fgcolor, fgcolor);
			printf("%i/%x ", fgcolor, fgcolor);
		}
	}
	
	for (bgcolor = 0; bgcolor < 16; bgcolor++)
	{
		printf("\n");
		
		for (fgcolor = 0; fgcolor < 16; fgcolor++)
		{
			screen_setattr(bgcolor * 16 + fgcolor, bgcolor * 16 + fgcolor);
			printf("0x%x%x ", bgcolor, fgcolor);
		}
	}
	
	screen_setattr(0x0f, 0x0f);
	printf("\n\n");
}
