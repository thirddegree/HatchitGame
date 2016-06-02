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

#include <ht_audiolistener_component.h>

#include <ht_gameobject.h> //GameObject
#include <ht_transform.h> //Transform data
#include <AL/al.h>

namespace Hatchit
{
    namespace Game
    {
        AudioListener::AudioListener()
        {

        }

        Core::JSON AudioListener::VSerialize()
        {
            return Core::JSON();
        }

        bool AudioListener::VDeserialize(const Core::JSON& jsonObject)
        {
            //TODO: Grab listener information from JSON file
            return true;
        }

        void AudioListener::VOnInit()
        {
            HT_DEBUG_PRINTF("Initialized AudioListener Component.\n");
        }

        void AudioListener::VOnUpdate()
        {
            //Update listener's transform data
            Transform& transformData = m_owner->GetTransform();
            Math::Vector3 position = transformData.GetPosition();
            Math::Vector3 forward = transformData.GetForward();
            
            alListenerfv(AL_POSITION, &position.m_data[0]);
            alListenerfv(AL_DIRECTION, &forward.m_data[0]);
        }

        Component* AudioListener::VClone() const
        {
            HT_DEBUG_PRINTF("Cloned AudioListener.\n");
            return new AudioListener(*this);
        }

        Core::Guid AudioListener::VGetComponentId() const
        {
            return Component::GetComponentId<AudioListener>();
        }

        void AudioListener::VOnEnabled()
        {
            HT_DEBUG_PRINTF("Enabled AudioListener Component.\n");
        }

        void AudioListener::VOnDisabled()
        {
            HT_DEBUG_PRINTF("Disabled AudioListener Component.\n");
        }

        void AudioListener::VOnDestroy()
        {
            HT_DEBUG_PRINTF("Destroyed AudioListener Component\n");
        }
    }
}