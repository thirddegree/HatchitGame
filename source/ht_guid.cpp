#include <ht_guid.h>
#include <chrono>
#include <random>
#include <sstream>
#include <string.h>
#include <time.h>

namespace Hatchit {

    namespace Game {

        /**
         * \brief Defines a simple Guid helper.
         */
        struct GuidHelper
        {
            static GuidHelper s_Instance;

            std::mt19937_64 m_mersenneTwister;
            std::uniform_int_distribution<uint32_t> m_distribution;

            /**
             * \brief Creates a new Guid helper.
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
            static inline uint8_t GenerateByte()
            {
                return static_cast<uint8_t>(s_Instance.m_distribution(s_Instance.m_mersenneTwister));
            }
        };

        GuidHelper GuidHelper::s_Instance;

        /**
         * \brief Creates a new Guid.
         */
        Guid::Guid()
        {
            for (int index = 0; index < 16; ++index)
            {
                m_uuid[index] = GuidHelper::GenerateByte();
            }
        }

        /**
         * \brief Copies one Guid's information into this Guid.
         *
         * \param other The other Guid.
         */
        Guid::Guid(const Guid& other)
        {
            *this = other;
        }

        /**
         * \brief Moves one Guid's information into this Guid.
         *
         * \param other The other Guid.
         */
		Guid::Guid(Guid&& other)
		{
			*this = other;
		}

        /**
         * \brief Destroys this Guid.
         */
        Guid::~Guid()
        {
            for (int index = 0; index < 16; ++index)
            {
                m_uuid[index] = 0;
            }
        }

		/**
		* \brief Copies raw guid information into this guid.
		*
		* \param uuid Guid array.
		*/
		void Guid::Set(uint8_t uuid[])
		{
			for (int index = 0; index < 16; ++index)
			{
				m_uuid[index] = uuid[index];
			}
		}

        /**
         * \brief Hashes this Guid.
         *
         * Provides a 64-bit unsigned integer hash representation of this Guid.
         */
        uint64_t Guid::Hash() const
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
         * \brief Gets the textual representation of this Guid.
         *
         * Returns the textual representation of this Guid, in the form
         * of {xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}.
         */
        std::string Guid::ToString() const
        {
            std::ostringstream stream;
            stream << '{' << std::hex;

            for (int index = 0; index < 16; ++index)
            {
                // TODO - Get std::setfill and std::setw to work ... eventually
                if (m_uuid[index] < 16)
                {
                    stream << '0';
                }

                stream << static_cast<int>(m_uuid[index]);

                switch (index)
                {
                    case 3:
                    case 5:
                    case 7:
                    case 9:
                        stream << '-';
                        break;
                }
            }

            stream << '}';
            return stream.str();
        }

        /**
         * \brief Checks to see if this Guid is the same as another.
         *
         * \param other The other Guid.
         */
        bool Guid::operator==(const Guid& other) const
        {
            for (int index = 0; index < 16; ++index)
            {
                if (m_uuid[index] != other.m_uuid[index])
                {
                    return false;
                }
            }
            return true;
        }

        /**
         * \brief Checks to see if this Guid is not the same as another.
         *
         * \param other The other Guid.
         */
        bool Guid::operator!=(const Guid& other) const
        {
            return !(*this == other);
        }

        /**
         * \brief Copies one Guid's information into this Guid.
         *
         * \param other The other Guid.
         */
        Guid& Guid::operator=(const Guid& other)
        {
            for (int index = 0; index < 16; ++index)
            {
                m_uuid[index] = other.m_uuid[index];
            }
            return *this;
        }

        /**
         * \brief Moves one Guid's information into this Guid.
         *
         * \param other The other Guid.
         */
        Guid& Guid::operator=(Guid&& other)
        {
            for (int index = 0; index < 16; ++index)
            {
                m_uuid[index] = other.m_uuid[index];
                other.m_uuid[index] = 0;
            }
            return *this;
        }

    }
}
