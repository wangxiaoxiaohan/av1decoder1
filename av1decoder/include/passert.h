#ifndef _ASSERT_
#define _ASSERT_
#define ASSERT(x) \
		if(!(x)){\
			printf("ASSERT! \n");\
            printf("line %d!\n",__LINE__);\
            printf("file :%s\n",__FILE__);}
#endif