#ifndef BIT_MATH_H_INCLUDED
#define BIT_MATH_H_INCLUDED


#define SET_BIT(REG_NAME, BIT_NUM)      REG_NAME = REG_NAME | (1 << BIT_NUM)
#define CLR_BIT(REG_NAME, BIT_NUM)      REG_NAME = REG_NAME & (~(1 << BIT_NUM))
#define TOG_BIT(REG_NAME, BIT_NUM)      REG_NAME = REG_NAME ^ (1 << BIT_NUM)
#define GET_BIT(REG_NAME, BIT_NUM)      ((REG_NAME >> BIT_NUM) & 1)




#endif