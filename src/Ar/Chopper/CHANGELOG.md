1.05.0 - Add tslf support 
	   - Fix some render calls not being thread-safe 

1.04.0 - Add support for error checking on manual formatting
	   - Add ChopGetDefaultFormatter
	   - Add ChopVerifyFormatter

1.03.2 - Handle snprintf returning a negative value

1.03.1 - Fixed bug when rendering STRINGs 

1.03.0 - Add support for manual formatting

1.02.2 - Update dependencies

1.02.1 - Update dependencies

1.02.0 - Add support basic for WString variables

1.01.0 - Increase variable limit from 50 to 100
	   - Fix Chopper falsely reporting successful compile if 1 variable over limit

1.00.0 - Increment version release

0.00.5 - Change member names to match updated style *Breaking change*
	   - Add compiled status to template. Used in chop fub to condition a compile, and in ChopRender as render precheck.
	   - Add source length check. Will not compile if source is longer than CHOP_TEMPLATE_MAXVARSTR.
	   - Add ChopGetErrorMsg fn
	   - ReOganized errors. Error numbers have changed!

0.00.4 - Add initial documentation

0.00.3 - Add Replace variable functions

0.00.2 - Remove unused dependencies 

0.00.1 - Initial version
