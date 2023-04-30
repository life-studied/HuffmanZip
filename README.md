# HuffmanZip
使用C++实现的哈夫曼编码，并封装用于Ascii文件的压缩与解压

## 使用

```C++
#include <iostream>
#include "file_manager.h"
#include "FCompress.h"
int main()
{
    file_manager fm;
    fm.writeData("test.txt", "hello123451234\n111\n222");
    FCompress FC1("test.txt");		//compress
    FC1.process();

    FCompress FC2("test.hfm");		//decompress
    FC2.process();
}
```

## 类图

## 流程图

