#include "ht_gameobject.h"


namespace Hatchit {

	namespace Game {

		Hatchit::Game::GameObject::GameObject()
		{

		}

		Hatchit::Game::GameObject::~GameObject()
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