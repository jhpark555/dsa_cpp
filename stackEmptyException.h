#ifndef STACKEMPTYEXCEPTION
#define STACKEMPTYEXCEPTION


#include "RuntimeException.h"


class StackEmpty : public RuntimeException {  // StackEmpty exception handling class implementation
    public:
        StackEmpty(const string& err) : RuntimeException(err) {}
};

class StackFull : public RuntimeException {  // StackEmpty exception handling class implementation
    public:
        StackFull(const string& err) : RuntimeException(err) {}
};


#endif
