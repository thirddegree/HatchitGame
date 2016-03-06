#include <ht_guid.hpp>
#include <chrono>
#include <random>
#include <sstream>
#include <string.h>
#include <time.h>

namespace Hatchit {

    namespace Game {

        /**
         * \brief Defines a simple GUID helper.
         */
        struct GuidHelper
        {
            static GuidHelper s_Instance;

            std::mt19937_64 m_mersenneTwister;
            std::uniform_int_distribution<uint32_t> m_distribution;

            /**
             * \brief Creates a new GUID helper.
             */
            GuidHelper()
                : m_distribution(0, 255)
            {
                using Clock = std::chrono::high_resolution_clock;
                using TimePoint = Clock::time_point;

                // We need to seed the PRNG, so let's use a high-resolution time since the epoch
                TimePoint epoch;
                TimePoint now = Clock::now();
                auto duration = now - epoch;
                m_mersenneTwister.seed(static_cast<uint64_t>(duration.count()));
            }

            /**
             * \brief Generates a high-quality random byte.
             */
            static uint8_t GenerateByte()
            {
                return s_Instance.m_distribution(s_Instance.m_mersenneTwister);
            }
        };

        /**
         * \brief Creates a new GUID.
         */
        GUID::GUID()
        {
        }

        /**
         * \brief Copies one GUID's information into this GUID.
         *
         * \param other The other GUID.
         */
        GUID::GUID(const GUID& other)
        {
        }

        /**
         * \brief Moves one GUID's information into this GUID.
         *
         * \param other The other GUID.
         */
        GUID::GUID(GUID&& other)
        {
        }

        /**
         * \brief Destroys this GUID.
         */
        GUID::~GUID()
        {
        }

        /**
         * \brief Hashes this GUID.
         *
         * Provides a 64-bit unsigned integer hash representation of this GUID.
         */
        uint64_t GUID::Hash() const
        {
            // This is adapted from the 64-bit version of the FNV-1a hashing algorithm
            // Source:  http://www.isthe.com/chongo/tech/comp/fnv/
            // License: Public Domain

            uint64_t hash = 0;

            for (int index = 0; index < 16; ++index)
            {
                hash ^= static_cast<uint64_t>(m_uuid[index]);

                // The algorithm differs on the next part, so if we're compiling using
                // GCC, then let's just use their optimization
#if defined(__GNUC__)
                hash += (hash << 1) + (hash << 4) + (hash << 5) +
                        (hash << 7) + (hash << 8) + (hash << 40);
#else
                hash *= 0x100000001b3ULL;
#endif
            }

            return hash;
        }

        /**
         * \brief Gets the textual representation of this GUID.
         *
         * Returns the textual representation of this GUID, in the form
         * of {xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}.
         */
        std::string GUID::ToString() const
        {
        }

        /**
         * \brief Checks to see if this GUID is the same as another.
         *
         * \param other The other GUID.
         */
        bool GUID::operator==(const GUID& other) const
        {
        }

        /**
         * \brief Checks to see if this GUID is not the same as another.
         *
         * \param other The other GUID.
         */
        bool GUID::operator!=(const GUID& other) const
        {
        }

        /**
         * \brief Copies one GUID's information into this GUID.
         *
         * \param other The other GUID.
         */
        GUID& GUID::operator=(const GUID& other)
        {
        }

        /**
         * \brief Moves one GUID's information into this GUID.
         *
         * \param other The other GUID.
         */
        GUID& GUID::operator=(GUID&& other)
        {
        }

    }
}
