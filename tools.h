#ifndef __TOOLS__
#define __TOOLS__
#define nullptr (void *)0

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;

#define bool int
#define false 0
#define true 1

#define OFFSET_OF(type, member) ((uint32_t) & ((type *)0)->member)                        /* 获取结构体成员在结构体中的偏移量 */
#define PARENT_STRUCT_ADDR(node, type, member) ((uint32_t)node - OFFSET_OF(type, member)) /* 找到结构体首地址 */
#define KLIST_STRUCT_ADDR(node, struct_type, member) ((struct_type *)(node ? PARENT_STRUCT_ADDR(node, struct_type, member) : 0))

#endif // !__TOOLS__
