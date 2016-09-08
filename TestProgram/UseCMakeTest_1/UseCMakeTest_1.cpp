// UseCMakeTest_1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#include"TutorialConfig.h"
#include <math.h>

#ifdef USE_MYMATH
#include "mysqrt.h"
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	
	if (argc < 2)
	{
		fprintf(stdout,"%s Version %d.%d\n",
			argv[0],
			Tutorial_VERSION_MAJOR,
			Tutorial_VERSION_MINOR);
		fprintf(stdout,"Usage: %s number\n",argv[0]);
		system("PAUSE");
		return 1;
	}
	double inputValue = atof(argv[1]);
	double outputValue = sqrt(inputValue);
	fprintf(stdout,"The square root of %g is %g\n",
		inputValue, outputValue);
	system("PAUSE");
	return 0;
	
}

