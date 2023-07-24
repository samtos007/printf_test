#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */

int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int pflags, pwidth, pprecision, psize, pbuff_indx = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[pbuff_indx++] = format[i];
			if (pbuff_indx == BUFF_SIZE)
				print_buffer(buffer, &pbuff_indx);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &pbuff_indx);
			pflags = get_flags(format, &i);
			pwidth = get_width(format, &i, list);
			pprecision = get_precision(format, &i, list);
			psize = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				pflags, pwidth, pprecision, psize);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &pbuff_indx);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - This prints the contents of the buffer if it exist
 * @buffer: Array of 'chars' to be printed
 * @pbuff_indx: printf buffer Index to add next char, represents the length.
 */
void print_buffer(char buffer[], int *pbuff_indx)
{
	if (*pbuff_indx > 0)
		write(1, &buffer[0], *pbuff_indx);

	*pbuff_indx = 0;
}
