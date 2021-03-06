#pragma once

#include "absl/types/span.h"
#include "fast_ber/ber_types/Identifier.hpp"
#include "fast_ber/util/BerView.hpp"

namespace fast_ber
{

struct DecodeResult
{
    bool success;
};

template <typename T, Class T2, Tag T3>
DecodeResult decode_impl(BerViewIterator& input, T& output, Id<T2, T3> id) noexcept
{
    if (!input->is_valid() || val(id.tag()) != input->tag())
    {
        return DecodeResult{false};
    }

    bool success = output.assign_ber(*input) > 0;
    ++input;
    return DecodeResult{success};
}

template <typename T, typename OuterId, typename InnerId>
DecodeResult decode_impl(BerViewIterator& input, T& output, DoubleId<OuterId, InnerId> id) noexcept
{
    if (!input->is_valid() || val(id.tag()) != input->tag())
    {
        return DecodeResult{false};
    }

    BerView         inner = input->content();
    BerViewIterator iter  = input->content();
    if (!decode_impl(iter, output, id.inner_id()).success)
    {
        return DecodeResult{false};
    }

    bool success = output.assign_ber(inner) > 0;
    ++input;
    return DecodeResult{success};
}

template <typename T>
DecodeResult decode(absl::Span<const uint8_t> input, T& output) noexcept
{
    BerViewIterator iter(input);
    if (!iter->is_valid())
    {
        return DecodeResult{false};
    }

    return decode(iter, output);
}

} // namespace fast_ber
