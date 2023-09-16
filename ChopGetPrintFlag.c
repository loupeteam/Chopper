#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include <string.h>
#include "Chopper.h"

#ifdef __cplusplus
	};
#endif


/* Gets the defualt printf flag for type and copies it into pDest */
plcbit ChopGetDefaultFormatter(plcstring* dest, unsigned long type) {
	// Note we dont generate a flag for each type
	// Only types that NEED a flag to render. Types that do not need a flag or dont support a flag will instead have an empty string
	switch (type)
	{
		case VAR_TYPE_LREAL:
		case VAR_TYPE_REAL:
			strcpy(dest, "%f");
			break;
		case VAR_TYPE_SINT:
		case VAR_TYPE_INT:
		case VAR_TYPE_DINT:
			strcpy(dest, "%d");
			break;
		case VAR_TYPE_USINT:
		case VAR_TYPE_UINT:
		case VAR_TYPE_UDINT:
			strcpy(dest, "%u");
			break;
		default:
			strcpy(dest, "");
			break;
	}
}

// %[flags][width][.precision][length]specifier

// --- Flags ---
//	-	Left-justify within the given field width; Right justification is the default (see width sub-specifier).
//	+	Forces to preceed the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a - sign.
//	(space)	If no sign is going to be written, a blank space is inserted before the value.
//	#	Used with o, x or X specifiers the value is preceeded with 0, 0x or 0X respectively for values different than zero.
//		  Used with a, A, e, E, f, F, g or G it forces the written output to contain a decimal point even if no more digits follow. By default, if no digits follow, no decimal point is written.
//	0	Left-pads the number with zeroes (0) instead of spaces when padding is specified (see width sub-specifier).

// --- Width ---
//	(number)	Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger.
//	*	The width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.


// --- Length ---
//	length	d i			u o x X				f F e E g G a A			c		s			p				n
//	(none)	int			unsigned int		double					int		char*		void*			int*
//	hh		signed char	unsigned char																	signed char*
//	h		short int	unsigned short int																short int*
//	l		long int	unsigned long int							wint_t	wchar_t*					long int*
//	ll		long long 	int	unsigned long long int														long long int*
//	j		intmax_t	uintmax_t																		intmax_t*
//	z		size_t		size_t																			size_t*
//	t		ptrdiff_t	ptrdiff_t																		ptrdiff_t*
//	L										long double				

// --- Specifiers ----
//	d or i	Signed decimal integer	392
//	u		Unsigned decimal integer	7235
//	o		Unsigned octal	610
//	x		Unsigned hexadecimal integer	7fa
//	X		Unsigned hexadecimal integer (uppercase)	7FA
//	f		Decimal floating point, lowercase	392.65
//	F		Decimal floating point, uppercase	392.65
//	e		Scientific notation (mantissa/exponent), lowercase	3.9265e+2
//	E		Scientific notation (mantissa/exponent), uppercase	3.9265E+2
//	g		Use the shortest representation: %e or %f	392.65
//	G		Use the shortest representation: %E or %F	392.65
//	a		Hexadecimal floating point, lowercase	-0xc.90fep-2
//	A		Hexadecimal floating point, uppercase	-0XC.90FEP-2
//	c		Character	a
//	s		String of characters	sample
//	p		Pointer address	b8000000
//	n		Nothing printed.
//	The corresponding argument must be a pointer to a signed int.
//	The number of characters written so far is stored in the pointed location.	
//	%	A % followed by another % character will write a single % to the stream.	%

/* Gets the defualt printf flag for type and copies it into pDest */
plcbit ChopVerifyFormatter(char* src, UDINT type) {
	char* format = src;
	
	if(!format) return 0;
	
	// Consume %
	if(*format != '%') return 0;
	format++;
	
	

	// Check Flags
	if(*format == '+'
		|| *format == '-'
		|| *format == ' '
		|| *format == '#'
		// || *format == '\'' This is not currently supportted in C standard. Maybe one day. 
	|| *format == '0') {
		// TODO: Additional checks can be done here
		format++;	
	}
	
	// Check Width
	if(*format == '*' || isdigit(*format)) {
		while(isdigit(*format)) format++;
		if(*format == '*') return 0; // We cant support this
	}
	
	// Check precision
	if(*format == '.') {
		format++; // Move past '.'
		while(isdigit(*format)) format++;
		if(*format == '*') return 0; // We cant support this
	}
	//	hh		signed char	unsigned char																	signed char*
	//	h		short int	unsigned short int																short int*
	//	l		long int	unsigned long int							wint_t	wchar_t*					long int*
	//	ll		long long 	int	unsigned long long int														long long int*
	//	j		intmax_t	uintmax_t																		intmax_t*
	//	z		size_t		size_t																			size_t*
	//	t		ptrdiff_t	ptrdiff_t																		ptrdiff_t*
	//	L	
	// Check for length
	if(*format == 'h' 
		|| *format == 'l'
		|| *format == 'j'
		|| *format == 'z'
		|| *format == 't'
	|| *format == 'L') {
		format++;
		if(*format == 'h' || *format == 'l') format++;
	}
	
	switch (type)
	{
		case VAR_TYPE_LREAL:
		case VAR_TYPE_REAL:
			if(*format == 'f'
				|| *format == 'F'
				|| *format == 'e'
				|| *format == 'E'
				|| *format == 'g'
				|| *format == 'G'
				|| *format == 'a'
				|| *format == 'A') 
				format++;
			else
				return 0; 
			break;
		case VAR_TYPE_SINT:
		case VAR_TYPE_INT:
		case VAR_TYPE_DINT:
			if(*format == 'd'
				|| *format == 'i'
				|| *format == 'c') 
				format++;
			else
				return 0; 
			break;
		case VAR_TYPE_USINT:
		case VAR_TYPE_UINT:
		case VAR_TYPE_UDINT:
			if(*format == 'u'
				|| *format == 'o'
				|| *format == 'x'
				|| *format == 'X'
				) 
				format++;
			else
				return 0; 
			break;
		case VAR_TYPE_STRING:
			if(*format == 's') 
				format++;
			else
				return 0; 
			break;
		default:
			return 0;
			break;
	}
	
	return *format == '\0';
}

