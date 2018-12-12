#pragma once

namespace app::inp
{
	template<typename KeyType>
	class KeyHandler
	{
	public:
	public:
		KeyHandler() = default;

		void updateKey(KeyType const & key, bool const & pressed);
		void update();

		bool isKeyDown(KeyType const & key) const;
		bool isKeyDown(std::initializer_list<KeyType> const & keys) const;
		bool isKeyUp(KeyType const & key) const;
		bool isKeyUp(std::initializer_list<KeyType> const & key) const;
		bool isKeyPressed(KeyType const & key) const;

		static KeyHandler & getRef();
	private:
		static std::unique_ptr<KeyHandler> s_ptr;
		std::map<const KeyType, bool> m_keyNowMap;
		std::map<const KeyType, bool> m_keyPrevMap;
	};

	#pragma region Implementation

	template<typename KeyType>
	std::unique_ptr<app::inp::KeyHandler<KeyType>> app::inp::KeyHandler<KeyType>::s_ptr = nullptr;

	template<typename KeyType>
	void app::inp::KeyHandler<KeyType>::updateKey(KeyType const & key, bool const & pressed)
	{
		if (auto itt = m_keyNowMap.find(key); itt != m_keyNowMap.end())
		{
			auto &[key, value] = *itt;
			value = pressed;
		}
		else
		{
			m_keyNowMap.insert({ key, pressed });
			m_keyPrevMap.insert({ key, !pressed });
		}
	}

	template<typename KeyType>
	void app::inp::KeyHandler<KeyType>::update()
	{
		m_keyPrevMap = m_keyNowMap;
	}

	template<typename KeyType>
	bool app::inp::KeyHandler<KeyType>::isKeyDown(KeyType const & key) const
	{
		if (auto const & itt = m_keyNowMap.find(key); itt != m_keyNowMap.end())
		{
			auto const &[key, value] = *itt;
			return value;
		}
		return false;
	}

	template<typename KeyType>
	bool app::inp::KeyHandler<KeyType>::isKeyDown(std::initializer_list<KeyType> const & keys) const
	{
		for (auto const &[mapKey, mapValue] : m_keyNowMap)
		{
			if (mapValue && std::find(keys.begin(), keys.end(), mapKey) != keys.end()) { return true; }
		}
		return false;
	}

	template<typename KeyType>
	bool app::inp::KeyHandler<KeyType>::isKeyUp(KeyType const & key) const
	{
		if (auto const & itt = m_keyNowMap.find(key); itt != m_keyNowMap.end())
		{
			auto const &[key, value] = *itt;
			return !value;
		}
		return false;
	}

	template<typename KeyType>
	bool app::inp::KeyHandler<KeyType>::isKeyUp(std::initializer_list<KeyType> const & keys) const
	{
		for (auto const &[mapKey, mapValue] : m_keyNowMap)
		{
			if (!mapValue && std::find(keys.begin(), keys.end(), mapKey) != keys.end()) { return true; }
		}
		return false;
	}

	template<typename KeyType>
	bool app::inp::KeyHandler<KeyType>::isKeyPressed(KeyType const & keyPressed) const
	{
		if (auto const & itt = m_keyNowMap.find(keyPressed); itt != m_keyNowMap.end())
		{
			auto const &[key, value] = *itt;

			if (auto const & prevItt = m_keyPrevMap.find(key); prevItt != m_keyPrevMap.end())
			{
				auto const &[prevKey, prevValue] = *prevItt;
				return value && !prevValue;
			}
			return value;
		}
		return false;
	}

	template<typename KeyType>
	app::inp::KeyHandler<KeyType> & KeyHandler<KeyType>::getRef()
	{
		if (!s_ptr) { s_ptr = std::make_unique<KeyHandler<KeyType>>(); }
		return *s_ptr;
	}


	#pragma endregion

}