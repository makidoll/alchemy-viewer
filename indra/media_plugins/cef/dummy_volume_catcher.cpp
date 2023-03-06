/** 
<<<<<<<< HEAD:indra/media_plugins/cef/dummy_volume_catcher.cpp
 * @file dummy_volume_catcher.cpp
 * @brief A null implementation of the "VolumeCatcher" class for platforms where it's not implemented yet.
 *
 * @cond
 * $LicenseInfo:firstyear=2010&license=viewerlgpl$
 * Second Life Viewer Source Code
 * Copyright (C) 2010, Linden Research, Inc.
========
 * @file gaussianF.glsl
 *
 * $LicenseInfo:firstyear=2023&license=viewerlgpl$
 * Second Life Viewer Source Code
 * Copyright (C) 2023, Linden Research, Inc.
>>>>>>>> 2020201ba6890feb9a31168c40e1ed14727fa719:indra/newview/app_settings/shaders/class1/interface/gaussianF.glsl
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
 * @endcond
 */

<<<<<<<< HEAD:indra/media_plugins/cef/dummy_volume_catcher.cpp
#include "volume_catcher.h"


class VolumeCatcherImpl
{
};

/////////////////////////////////////////////////////

VolumeCatcher::VolumeCatcher()
{
	pimpl = NULL;
}

VolumeCatcher::~VolumeCatcher()
{
}

void VolumeCatcher::setVolume(F32 volume)
{
}

void VolumeCatcher::setPan(F32 pan)
{
}

void VolumeCatcher::pump()
{
========
out vec4 frag_color;

uniform sampler2D diffuseRect;

uniform float resScale;

// texture direction, will be <1, 0> or <0, 1>
uniform vec2 direction;

in vec2 vary_texcoord0;

// get linear depth value given a depth buffer sample d and znear and zfar values
float linearDepth(float d, float znear, float zfar);

void main() 
{
    vec3 col = vec3(0,0,0);

    float w[9] = float[9]( 0.0002, 0.0060, 0.0606, 0.2417, 0.3829, 0.2417, 0.0606, 0.0060, 0.0002 );
    
    for (int i = 0; i < 9; ++i)
    {
        vec2 tc = vary_texcoord0 + (i-4)*direction*resScale;
        col += texture(diffuseRect, tc).rgb * w[i];
    }

    frag_color = vec4(col, 0.0);
>>>>>>>> 2020201ba6890feb9a31168c40e1ed14727fa719:indra/newview/app_settings/shaders/class1/interface/gaussianF.glsl
}
