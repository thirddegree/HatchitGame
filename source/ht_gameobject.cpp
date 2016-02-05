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
			for (int i = 0; i < components.size(); i++)
			{
				components[i].OnInit();
			}
		}

		void GameObject::OnEnabled()
		{
			for (int i = 0; i < components.size(); i++)
			{
				components[i].OnEnabled();
			}
		}

		void GameObject::Update()
		{
			for (int i = 0; i < components.size(); i++)
			{
				components[i].Update();
			}
		}

		void GameObject::OnDisabled()
		{
			for (int i = 0; i < components.size(); i++)
			{
				components[i].OnDisabled();
			}
		}

		void GameObject::OnDestroy()
		{
			for (int i = 0; i < components.size(); i++)
			{
				components[i].OnDestroy();
			}
		}
	}
}
