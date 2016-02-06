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

#include "ht_gameobject.h"

namespace Hatchit {

	namespace Game {

		GameObject::GameObject()
		{

		}

		GameObject::~GameObject()
		{

		}

		void GameObject::OnInit()
		{
			for (size_t i = 0; i < m_components.size(); i++)
			{
				m_components[i]->VOnInit();
			}
		}

		void GameObject::OnEnabled()
		{
			for (size_t i = 0; i < m_components.size(); i++)
			{
				m_components[i]->VOnEnabled();
			}
		}

		void GameObject::Update()
		{
			for (size_t i = 0; i < m_components.size(); i++)
			{
				m_components[i]->VOnUpdate();
			}
		}

		void GameObject::OnDisabled()
		{
			for (size_t i = 0; i < m_components.size(); i++)
			{
				m_components[i]->OnDisabled();
			}
		}

		void GameObject::OnDestroy()
		{
			for (size_t i = 0; i < m_components.size(); i++)
			{
				m_components[i]->VOnDestroy();
			}
		}
	}
}
