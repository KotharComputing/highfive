/*
 *  Copyright (c), 2020, EPFL - Blue Brain Project
 *
 *  Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 */
#pragma once

#include <H5Ipublic.h>

#include "H5Utils.hpp"
#include "H5Path_traits.hpp"

namespace HighFive {

template <typename Derivate>
inline PathTraits<Derivate>::PathTraits() {
    static_assert(std::is_same<Derivate, Group>::value || std::is_same<Derivate, DataSet>::value ||
                      std::is_same<Derivate, Attribute>::value,
                  "PathTraits can only be applied to Group, DataSet and Attribute");
    const auto& obj = static_cast<const Derivate&>(*this);
    if (obj.isValid()) {
#if !defined(HIGHFIVE_USE_RESTVOL)
        const hid_t file_id = detail::h5i_get_file_id<PropertyException>(obj.getId());
        _file_obj.reset(new File(file_id));
#endif
    }
}

template <typename Derivate>
inline std::string PathTraits<Derivate>::getPath() const {
    return details::get_name([this](char* buffer, size_t length) {
        return detail::h5i_get_name(static_cast<const Derivate&>(*this).getId(), buffer, length);
    });
}

template <typename Derivate>
inline File& PathTraits<Derivate>::getFile() const {
    const auto& obj = static_cast<const Derivate&>(*this);
#if defined(HIGHFIVE_USE_RESTVOL)
    throw ObjectException("`PathTraits::getFile` is not supported with REST VOL.");
#endif
    if (!obj.isValid()) {
        throw ObjectException("Invalid call to `PathTraits::getFile` for invalid object");
    }
    return *_file_obj;
}

}  // namespace HighFive
