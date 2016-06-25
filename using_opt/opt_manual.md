选项数组的定义
结构体类型option：系统已定义，直接使用即可

```C++
//  头文件：“getopt.h”
struct option
{
  //  选项长名称
  const char * name;
  //  该选项是否具有附加参数；0：无；1：有；2：可选
  int has_arg;
  //  指向整数，用于保存val值，设为0
  int * flag;
  //  选项短名称
  int val;
};
```

```C++
int getopt_long( int argc, char * const * argv, const char * short_options, const struct option * long_options, int * long_index );
```
函数返回值为参数短名称，不存在时返回-1
如果为长选项，第五个参数输出该选项在长选项数组中的索引
