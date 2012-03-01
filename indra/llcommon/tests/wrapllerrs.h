/**
 * @file   wrapllerrs.h
 * @author Nat Goodspeed
 * @date   2009-03-11
 * @brief  Define a class useful for unit tests that engage llerrs (LL_ERRS) functionality
 * 
 * $LicenseInfo:firstyear=2009&license=viewerlgpl$
 * Second Life Viewer Source Code
 * Copyright (C) 2010, Linden Research, Inc.
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

#if ! defined(LL_WRAPLLERRS_H)
#define LL_WRAPLLERRS_H

#include "llerrorcontrol.h"
#include <boost/bind.hpp>
#include <list>
#include <string>
#include <stdexcept>

// statically reference the function in test.cpp... it's short, we could
// replicate, but better to reuse
extern void wouldHaveCrashed(const std::string& message);

struct WrapLL_ERRS
{
    WrapLL_ERRS():
        // Resetting Settings discards the default Recorder that writes to
        // stderr. Otherwise, expected llerrs (LL_ERRS) messages clutter the
        // console output of successful tests, potentially confusing things.
        mPriorErrorSettings(LLError::saveAndResetSettings()),
        // Save shutdown function called by LL_ERRS
        mPriorFatal(LLError::getFatalFunction())
    {
        // Make LL_ERRS call our own operator() method
        LLError::setFatalFunction(boost::bind(&WrapLL_ERRS::operator(), this, _1));
    }

    ~WrapLL_ERRS()
    {
        LLError::setFatalFunction(mPriorFatal);
        LLError::restoreSettings(mPriorErrorSettings);
    }

    struct FatalException: public std::runtime_error
    {
        FatalException(const std::string& what): std::runtime_error(what) {}
    };

    void operator()(const std::string& message)
    {
        // Save message for later in case consumer wants to sense the result directly
        error = message;
        // Also throw an appropriate exception since calling code is likely to
        // assume that control won't continue beyond LL_ERRS.
        throw FatalException(message);
    }

    std::string error;
    LLError::Settings* mPriorErrorSettings;
    LLError::FatalFunction mPriorFatal;
};

/**
 * Capture log messages. This is adapted (simplified) from the one in
 * llerror_test.cpp.
 */
class CaptureLog : public LLError::Recorder
{
public:
    CaptureLog():
        // Mostly what we're trying to accomplish by saving and resetting
        // LLError::Settings is to bypass the default RecordToStderr and
        // RecordToWinDebug Recorders. As these are visible only inside
        // llerror.cpp, we can't just call LLError::removeRecorder() with
        // each. For certain tests we need to produce, capture and examine
        // DEBUG log messages -- but we don't want to spam the user's console
        // with that output. If it turns out that saveAndResetSettings() has
        // some bad effect, give up and just let the DEBUG level log messages
        // display.
        mOldSettings(LLError::saveAndResetSettings())
    {
        LLError::setFatalFunction(wouldHaveCrashed);
        LLError::setDefaultLevel(LLError::LEVEL_DEBUG);
        LLError::addRecorder(this);
    }

    ~CaptureLog()
    {
        LLError::removeRecorder(this);
        LLError::restoreSettings(mOldSettings);
    }

    void recordMessage(LLError::ELevel level,
                       const std::string& message)
    {
        mMessages.push_back(message);
    }

    /// Don't assume the message we want is necessarily the LAST log message
    /// emitted by the underlying code; search backwards through all messages
    /// for the sought string.
    std::string messageWith(const std::string& search)
    {
        for (std::list<std::string>::const_reverse_iterator rmi(mMessages.rbegin()),
                 rmend(mMessages.rend());
             rmi != rmend; ++rmi)
        {
            if (rmi->find(search) != std::string::npos)
                return *rmi;
        }
        // failed to find any such message
        return std::string();
    }

    typedef std::list<std::string> MessageList;
    MessageList mMessages;
    LLError::Settings* mOldSettings;
};

#endif /* ! defined(LL_WRAPLLERRS_H) */
