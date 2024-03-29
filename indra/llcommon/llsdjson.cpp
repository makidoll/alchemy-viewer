/** 
 * @file llsdjson.cpp
 * @brief LLSD flexible data system
 *
 * $LicenseInfo:firstyear=2015&license=viewerlgpl$
 * Second Life Viewer Source Code
 * Copyright (C) 2015, Linden Research, Inc.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation;
 * version 2.1 of the License only.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * Linden Research, Inc., 945 Battery Street, San Francisco, CA  94111  USA
 * $/LicenseInfo$
 */

// Must turn on conditional declarations in header file so definitions end up
// with proper linkage.

#include "linden_common.h"

#include "llsdjson.h"

#include "llerror.h"


//=========================================================================
LLSD LlsdFromJson(const nlohmann::json &val)
{
    LLSD result;

    switch (val.type())
    {
    default:
    case nlohmann::json::value_t::null:
        break;
    case nlohmann::json::value_t::number_integer:
        result = LLSD(val.get<LLSD::Integer>());
        break;
    case nlohmann::json::value_t::number_unsigned:
        result = LLSD(val.get<LLSD::Integer>());
        break;
    case nlohmann::json::value_t::number_float:
        result = LLSD(val.get<LLSD::Real>());
        break;
    case nlohmann::json::value_t::string:
        result = LLSD(val.get<LLSD::String>());
        break;
    case nlohmann::json::value_t::boolean:
        result = LLSD(val.get<LLSD::Boolean>());
        break;
    case nlohmann::json::value_t::array:
        result = LLSD::emptyArray();
        for (const auto &element : val)
        {
            result.append(LlsdFromJson(element));
        }
        break;
    case nlohmann::json::value_t::object:
        result = LLSD::emptyMap();
        for (auto it = val.cbegin(), end = val.cend(); it != end; ++it)
        {
            result[it.key()] = LlsdFromJson(it.value());
        }
        break;
    }
    return result;
}

//=========================================================================
nlohmann::json LlsdToJson(const LLSD &val)
{
    nlohmann::json result;

    switch (val.type())
    {
    case LLSD::TypeUndefined:
        result = nullptr;
        break;
    case LLSD::TypeBoolean:
        result = val.asBoolean();
        break;
    case LLSD::TypeInteger:
        result = val.asInteger();
        break;
    case LLSD::TypeReal:
        result = val.asReal();
        break;
    case LLSD::TypeURI:
    case LLSD::TypeDate:
    case LLSD::TypeUUID:
    case LLSD::TypeString:
        result = val.asString();
        break;
    case LLSD::TypeMap:
        for (auto it = val.beginMap(), it_end = val.endMap(); it != it_end; ++it)
        {
            result[it->first] = LlsdToJson(it->second);
        }
        break;
    case LLSD::TypeArray:
        for (auto it = val.beginArray(), end = val.endArray(); it != end; ++it)
        {
            result.push_back(LlsdToJson(*it));
        }
        break;
    case LLSD::TypeBinary:
    default:
        LL_ERRS("LlsdToJson") << "Unsupported conversion to JSON from LLSD type (" << val.type() << ")." << LL_ENDL;
        break;
    }

    return result;
}
