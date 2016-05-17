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

#include <ht_audiosource_component.h>
#include <stb_vorbis.c>

namespace Hatchit
{
    namespace Game
    {
        AudioSource::AudioSource()
            : m_currentAudioHandle(),
            m_playing(false),
            m_audioStream(nullptr),
            m_source(),
            m_bufferList(),
            m_nextBufferIndex(0)
        {
        }

        AudioSource::AudioSource(const AudioSource& source)
            : m_currentAudioHandle(source.m_currentAudioHandle),
            m_playing(source.m_playing),
            m_audioStream(),
            m_source(source.m_source),
            m_bufferList(),
            m_nextBufferIndex(0)
        {
            m_audioStream = reinterpret_cast<stb_vorbis*>(malloc(sizeof(stb_vorbis)));
            std::memcpy(m_audioStream, source.m_audioStream, sizeof(stb_vorbis));
        }

        AudioSource::AudioSource(AudioSource&& source)
            : m_currentAudioHandle(std::move(source.m_currentAudioHandle)),
            m_playing(std::move(source.m_playing)),
            m_audioStream(std::move(source.m_audioStream)),
            m_source(std::move(source.m_source)),
            m_bufferList(std::move(source.m_bufferList)),
            m_nextBufferIndex(std::move(source.m_nextBufferIndex))
        {
            source.m_audioStream = nullptr;
        }

        AudioSource& AudioSource::operator=(const AudioSource& source)
        {
            m_currentAudioHandle = source.m_currentAudioHandle;
            m_playing = source.m_playing;
            m_audioStream = reinterpret_cast<stb_vorbis*>(malloc(sizeof(stb_vorbis)));
            std::memcpy(m_audioStream, source.m_audioStream, sizeof(stb_vorbis));
            m_source = source.m_source;
            return *this;
        }

        AudioSource& AudioSource::operator=(AudioSource&& source)
        {
            m_currentAudioHandle = std::move(source.m_currentAudioHandle);
            m_playing = std::move(source.m_playing);
            m_audioStream = std::move(source.m_audioStream);
            source.m_audioStream = nullptr;
            m_source = std::move(source.m_source);
            m_bufferList = std::move(source.m_bufferList);
            m_nextBufferIndex = std::move(source.m_nextBufferIndex);
            return *this;
        }

        Core::JSON AudioSource::VSerialize()
        {
            return Core::JSON();
        }

        bool AudioSource::VDeserialize(const Core::JSON& jsonObject)
        {
            return true;
        }

        void AudioSource::VOnInit()
        {
            HT_DEBUG_PRINTF("Initialized AudioSource Component.\n");

            //For testing
            PlayAudio(Resource::Audio::GetHandleFromFileName("Example2.ogg"));
        }

        void AudioSource::VOnUpdate()
        {
            if (!m_playing)
                return;

            auto numBuffersToProcess = m_source.GetNumBuffersQueued();
            if (numBuffersToProcess == 0)
            {
                m_playing = false;
                return;
            }

            auto numBuffersProcessed = m_source.GetNumBuffersProcessed();
            while (numBuffersProcessed > 0)
            {
                m_source.UnqueueBuffer(m_bufferList[m_nextBufferIndex]);
                SetupBuffer(m_bufferList[m_nextBufferIndex]);

                //If there's nothing left to buffer, then don't queue it to
                //play
                if(m_bufferList[m_nextBufferIndex].GetBufferSize() > 0)
                    m_source.QueueBuffer(m_bufferList[m_nextBufferIndex]);

                m_nextBufferIndex = (m_nextBufferIndex + 1) % numBuffers;
                --numBuffersProcessed;
            }
            //Update source buffers
        }

        Component* AudioSource::VClone() const
        {
            HT_DEBUG_PRINTF("Cloned AudioSource Component.\n");
            return new AudioSource(*this);
        }

        Core::Guid AudioSource::VGetComponentId() const
        {
            return Component::GetComponentId<AudioSource>();
        }

        void AudioSource::PlayAudio(Resource::AudioResourceHandle handle)
        {
            m_currentAudioHandle = handle;
            //Initialize for playing
            stb_vorbis_close(m_audioStream);

            //Setup Stream
            if (!SetupAudioStream())
            {
                HT_ERROR_PRINTF("Error playing audio resource.");
                return;
            }

            //Start setting up buffers
            for (auto& buffer : m_bufferList)
            {
                SetupBuffer(buffer);
            }

            //Queue buffers to play
            if (!(m_bufferList[0].GetBufferSize() > 0))
            {
                m_playing = false;
                return;
            }

            m_source.QueueBuffer(m_bufferList[0]);

            for (size_t i = 1; i < numBuffers; ++i)
            {
                if (!(m_bufferList[i].GetBufferSize() > 0))
                    break;

                m_source.QueueBuffer(m_bufferList[i]);
            }

            assert(m_source.GetNumBuffersQueued() == 16);

            //Finally, start playing buffers
            if (!m_source.Play())
            {
                HT_ERROR_PRINTF("Error playing Audio source");
                return;
            }

            m_playing = true;
        }

        void AudioSource::VOnEnabled()
        {
            HT_DEBUG_PRINTF("Enabled AudioSource Component.\n");
        }

        void AudioSource::VOnDisabled()
        {
            HT_DEBUG_PRINTF("Disabled AudioSource Component.\n");
        }

        void AudioSource::VOnDestroy()
        {
            HT_DEBUG_PRINTF("Destroyed AudioSource Component.\n");

            stb_vorbis_close(m_audioStream);    //This function already internally checks
                                                //for nullptrs.
        }

        void AudioSource::SetupBuffer(Audio::Buffer& audioBuffer)
        {
            //First, read data in
            short dataBuffer[Audio::Buffer::BufferSize / sizeof(short)];
            std::memset(&dataBuffer[0], 0, sizeof(dataBuffer));
            auto numChannels = m_currentAudioHandle->GetNumChannels();
            int numSamplesPerChannelReceived = stb_vorbis_get_samples_short_interleaved(m_audioStream, numChannels, &dataBuffer[0], Audio::Buffer::BufferSize / sizeof(short));

            //Then output to buffer
            audioBuffer.SetData(Audio::Buffer::Format::Stereo16, &dataBuffer[0], numSamplesPerChannelReceived * numChannels * sizeof(short), m_currentAudioHandle->GetSampleRate());
        }

        bool AudioSource::SetupAudioStream()
        {
            int errorCode = STBVorbisError::VORBIS__no_error;
            m_audioStream = stb_vorbis_open_filename(m_currentAudioHandle->GetFileName().c_str(), &errorCode, nullptr);
            if (errorCode != STBVorbisError::VORBIS__no_error)
            {
                HT_ERROR_PRINTF("Error opening Vorbis File: Error code %i", errorCode);
                return false;
            }
            stb_vorbis_seek_start(m_audioStream);
            return true;
        }
    }
}