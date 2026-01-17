class A {
    const int example(const int a) const {
        // ...
    }
};

[1] const int example( ... )
    修饰返回值，调用方不能修改返回值

[2] example(const int a)
    函数体内不能修改a
    虽然像不传指针或引用可以避免影响外部，但是更重要的是这个const还能避免内部修改a，强制防止误用

[3] example(...) const
    修饰成员函数本身，函数体内不能修改该类对象的非mutable成员变量
    class A {
        int x;
        mutable int cache;
    public:
        int f() const {
            // x = 1;        // 不允许
            cache = 42;     // 允许（mutable）
            return x;
        }
    };