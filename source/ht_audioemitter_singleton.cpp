/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#include <ht_audioemitter_singleton.h>

namespace Hatchit
{
    namespace Game
    {
        bool AudioEmitter::Initialize()
        {
            AudioEmitter& _instance = AudioEmitter::instance();
            if (!_instance.m_device.Initialize())
            {
                return false;
            }
            _instance.m_device.MakeContextCurrent();
            return true;
        }

        void AudioEmitter::DeInitialize()
        {
            AudioEmitter& _instance = AudioEmitter::instance();

            _instance.m_device.~Device();
        }

        void AudioEmitter::Update()
        {
            //Do stuff
        }
    }
}