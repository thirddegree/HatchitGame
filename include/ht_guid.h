/**
 **    Hatchit Engine
 **    Copyright(c) 2016 Third-Degree
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

#include <ht_platform.h>
#include <stdint.h>
#include <string>

namespace Hatchit {

    namespace Game {

        /**
         * \class GUID
         * \ingroup HatchitGame
         *
         * \brief Defines a simple globally-unique identifier.
         */
        class HT_API GUID
        {
            uint8_t m_uuid[16];

        public:
            /**
             * \brief Creates a new GUID.
             */
            GUID();

            /**
             * \brief Copies one GUID's information into this GUID.
             *
             * \param other The other GUID.
             */
            GUID(const GUID& other);

            /**
             * \brief Moves one GUID's information into this GUID.
             *
             * \param other The other GUID.
             */
            GUID(GUID&& other);

            /**
             * \brief Destroys this GUID.
             */
            ~GUID();

            /**
             * \brief Hashes this GUID.
             *
             * Provides a 64-bit unsigned integer hash representation of this GUID.
             */
            uint64_t Hash() const;

            /**
             * \brief Gets the textual representation of this GUID.
             *
             * Returns the textual representation of this GUID, in the form
             * of {xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}.
             */
            std::string ToString() const;

            /**
             * \brief Checks to see if this GUID is the same as another.
             *
             * \param other The other GUID.
             */
            bool operator==(const GUID& other) const;

            /**
             * \brief Checks to see if this GUID is not the same as another.
             *
             * \param other The other GUID.
             */
            bool operator!=(const GUID& other) const;

            /**
             * \brief Copies one GUID's information into this GUID.
             *
             * \param other The other GUID.
             */
            GUID& operator=(const GUID& other);

            /**
             * \brief Moves one GUID's information into this GUID.
             *
             * \param other The other GUID.
             */
            GUID& operator=(GUID&& other);
        };

    }
}

namespace std {

    /**
     * \class hash<Hatchit::Game::GUID>
     * \ingroup std
     *
     * \brief Defines a hash struct to allow Hatchit::Game::GUIDs to be used as keys in STL structures.
     */
    template<> struct hash<Hatchit::Game::GUID>
    {
        inline size_t operator()(const Hatchit::Game::GUID& guid)
        {
            return guid.Hash();
        }
    };

}
