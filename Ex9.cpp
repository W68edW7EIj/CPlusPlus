/*
这道题主要考察了重载、内联函数

- 重载：同名但是不同参数列表（返回类型不参与、形参顶层的const不参与）
    - 编译器内部对重载的解析：
        - 1. 候选集：找到所有同名函数;
        - 2. 可行集：能通过隐式转换把实参转换为形参的函数
        - 3. 最佳可行函数：比较每个参数的转换“优劣”，选整体更优的那个；若无唯一更优 => 二义性报错
    - 优劣排序：
        - 1. 精准匹配：类型完全相同、或仅限底层cv的调整
        - 2. 提升：
            - a. 整型提升：bool/char/signed char/unsigned char/short => int（或 unsigned int）
            - b. 浮点提升：float => double
        - 3. 转换：int <=> float、double => float、double => int、unsigned <=> signed、派生 => 基类等
    - 消歧修正：
        - 1. 显式类型转换：调用 (float)i 等
        - 2. 添加后缀字面量：如 3.0f （有点像TS里的 i as float )

        */