/* Minimal main program -- everything is loaded from the library */

#include "Python.h"

#ifdef __FreeBSD__
#include <floatingpoint.h>
#endif

int
main(int argc, char **argv)
{
	/* 754 requires that FP exceptions run in "no stop" mode by default,
	 * and until C vendors implement C99's ways to control FP exceptions,
	 * Python requires non-stop mode.  Alas, some platforms enable FP
	 * exceptions by default.  Here we disable them.
	 */
#ifdef __FreeBSD__
	fp_except_t m;

	m = fpgetmask();
	fpsetmask(m & ~FP_X_OFL);
#endif
	setenv("VERSIONER_PYTHON_VERSION", "@VERSION@", 1);
#ifdef __LP64__
	setenv("VERSIONER_PYTHON_PREFER_32_BIT", "no", 1);
#else /* !__LP64__ */
	setenv("VERSIONER_PYTHON_PREFER_32_BIT", "yes", 1);
#endif /* __LP64__ */

	return Py_Main(argc, argv);
}
