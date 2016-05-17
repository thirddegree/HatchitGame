/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
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

#pragma once

#include <ht_component.h> //Component
#include <ht_jsonhelper.h> //Core::JSON
#include <ht_audio_resource.h> //AudioHandle
#include <ht_audiosource.h> //Audio::Source
#include <ht_audiobuffer.h> //Audio::Buffer
#include <array> //std::array

struct stb_vorbis;

namespace Hatchit
{
    namespace Core
    {
        class Guid;
    }
}

namespace Hatchit
{
    namespace Game
    {
        class AudioSource : public Component
        {
        public:
            AudioSource();
            AudioSource(const AudioSource& source);
            AudioSource(AudioSource&& source);

            AudioSource& operator=(const AudioSource& source);
            AudioSource& operator=(AudioSource&& source);

            virtual Core::JSON VSerialize() override;
            virtual bool VDeserialize(const Core::JSON& jsonObject) override;
            
            virtual void VOnInit() override;
            virtual void VOnUpdate() override;

            virtual Component* VClone() const override;

            virtual Core::Guid VGetComponentId(void) const override;

            void PlayAudio(Resource::AudioResourceHandle handle);
        protected:

            virtual void VOnEnabled() override;
            virtual void VOnDisabled() override;
            virtual void VOnDestroy() override;

        private:
            static constexpr size_t numBuffers = 16;

            Resource::AudioResourceHandle m_currentAudioHandle;
            bool m_playing;
            stb_vorbis* m_audioStream;
            Audio::Source m_source;
            std::array<Audio::Buffer, numBuffers> m_bufferList;
            size_t m_nextBufferIndex;

            void SetupBuffer(Audio::Buffer& audioBuffer);
            bool SetupAudioStream();

        };
    }
}
