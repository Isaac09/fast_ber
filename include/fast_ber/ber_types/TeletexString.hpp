#pragma once

#include "fast_ber/ber_types/StringImpl.hpp"
#include "fast_ber/ber_types/Tag.hpp"

namespace fast_ber
{
template <typename Identifier = ExplicitId<UniversalTag::teletex_string>>
using TeletexString = fast_ber::StringImpl<UniversalTag::teletex_string, Identifier>;
}
