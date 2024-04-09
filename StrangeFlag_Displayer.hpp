#ifndef STRANGEFLAG_DISPLAYER_HPP
#define STRANGEFLAG_DISPLAYER_HPP
#include "StrangeFlag.hpp"

class StrangeFlag_Displayer {
public:
    virtual void display_state(StrangeFlag * const f) = 0;
    virtual void display_fail(const size_t steps, const size_t tries) = 0;
    virtual void display_result(const bool is_success, const size_t steps) = 0;
};
#endif
