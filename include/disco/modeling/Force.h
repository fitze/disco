#ifndef DISCO_FORCE_H
#define DISCO_FORCE_H

#include "fwk/NamedInterface.h"

namespace disco
{

/**
 * @brief A force.
 * */
class Force : public NamedInterface
{
public:

    /**
     * @brief Hello.
     * */
    Unit::Force value() const;


private:
};

} // namespace disco
#endif