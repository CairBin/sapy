#pragma once
#include "sapy/pobject.h"
#include "sapy/base/pbytes.h"
#include "sapy/pstring.h"

namespace sapy {

class PBytes : public PObject, public base::PBytes{
public:
    using base::PBytes::PBytes;
    PString toString() const override;
private:
    virtual void _print(std::ostream &os) const override;
};

}  // namespace sapy
