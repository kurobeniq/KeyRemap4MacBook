#include <IOKit/IOLib.h>

#include "FlagStatus.hpp"
#include "IOLogWrapper.hpp"
#include "ModifierFilter.hpp"
#include "bridge.h"

namespace org_pqrs_KeyRemap4MacBook {
  namespace RemapFilter {
    ModifierFilter::ModifierFilter(unsigned int t) : type_(t)
    {}

    ModifierFilter::~ModifierFilter(void)
    {}

    void
    ModifierFilter::add(AddValue newval)
    {
      targets_.push_back(newval);
    }

    bool
    ModifierFilter::isblocked(void)
    {
      switch (type_) {
        case BRIDGE_FILTERTYPE_MODIFIER_NOT:
        case BRIDGE_FILTERTYPE_MODIFIER_ONLY:
        {
          bool isnot = (type_ == BRIDGE_FILTERTYPE_MODIFIER_NOT);

          Flags current = FlagStatus::globalFlagStatus().makeFlags();
          for (size_t i = 0; i < targets_.size(); ++i) {
            Flags f(targets_[i]);
            if (current.isOn(f)) {
              return isnot ? true : false;
            }
          }
          return isnot ? false : true;
        }

        default:
          IOLOG_ERROR("ModifierFilter::isblocked unknown type_(%d)\n", type_);
          break;
      }

      return false;
    }
  }
}
