#ifndef _FLOATPOINT_H_
#define _FLOATPOINT_H_

const float threshold = 0.00001;

#define f_equal(a1, a2) \
	(fabs(((a1) - (a2))) < threshold)


#define f_unequal(a1, a2) \
	(fabs(((a1) - (a2))) > threshold)

#endif
