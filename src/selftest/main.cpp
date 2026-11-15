// Selftest for the clang-cl + lld-link + Wine toolchain and crt0.
// Tests: virtual class, static object with a constructor (C++ static init),
// new/delete, printf, static destructor through atexit/exit.
// Expected output:
//   lift ok 2 32
//   lift exit
#include <stdio.h>

namespace {

class Base
{
public:
    virtual ~Base() {}
    virtual int Value() const = 0;
};

class Derived : public Base
{
public:
    explicit Derived(int* deleted) : deleted_(deleted) {}
    ~Derived() override { *deleted_ += 1; }
    int Value() const override { return 2; }

private:
    int* deleted_;
};

class StaticObject
{
public:
    explicit StaticObject(int value) : value_(value) {}
    ~StaticObject() { printf("lift exit\n"); }
    int value_;
};

StaticObject g_static(30);

} // namespace

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    // If static init did not run, value_ is 0.
    if (g_static.value_ != 30) {
        printf("lift fail static init\n");
        return 1;
    }

    int deleted = 0;
    Base* object = new Derived(&deleted);
    int value = object->Value();
    delete object;
    if (deleted != 1) {
        printf("lift fail delete\n");
        return 1;
    }

    printf("lift ok %d %d\n", value, g_static.value_ + value);
    return 0;
}
