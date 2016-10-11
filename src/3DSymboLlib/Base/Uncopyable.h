#ifndef BASE_UNCOPYABLE_H
#define BASE_UNCOPYABLE_H

namespace Base {

class Uncopyable
{
protected:
    Uncopyable() {}
    ~Uncopyable() {}

private:
    // declare but not define, prevent compiler-synthesized functions
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

}

#endif  // BASE_UNCOPYABLE_H