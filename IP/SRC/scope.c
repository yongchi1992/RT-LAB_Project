#include "svpwm.h"
	extern SVPWM svpwm;
long ua = 0;
long ub = 0;
long uab = 0;
void scope(void)
{
	long tl,tm,t0;

	tl = svpwm.tl;
	tm = svpwm.tm;
	t0 = ((long)1<<19) - tl - tm;

	switch(svpwm.vect)
		{
			case 2:ua = t0+tm;  ub = t0;			break;
			case 3:ua = 0;      ub = tl;			break;
			case 1:ua = t0;     ub = ((long)1<<19);		break;
			case 5:ua = tl;     ub = tl+tm;	   	    break;
			case 4:ua = ((long)1<<19); ub = tm+t0;	    	break;
			case 6:ua = tl+tm;	    ub = 0;	    	break;
			default: 		              	break;
		}
	uab=ua-ub;
}
