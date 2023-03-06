#pragma once

#include <random>
#include <string>

#include "object.h"

using namespace ObjectModel;
using namespace Core;
using namespace Util;

namespace HashTable
{
	template<typename T, typename U> class User;
	template<typename T, typename U> std::istream& operator>>(std::istream& stream, User<T, U>& user);

	template<typename T, typename U>
	class User
	{
	private:
		T Login;
		U Password;
		User* Next;
	public:
		bool isSerialized = false;
		bool isNext = false;
	public:
		User(const T& Login, const U& Password)
			:
			Login(Login),
			Password(Password),
			Next(nullptr) {}

		User() = default;
		~User() = default;
	public:
		//template<typename T, typename U>
		//friend std::istream& operator>>(std::istream& stream, User<T, U>& user);


		void setLogin(const T& Login)
		{
			this->Login = Login;
		}
		void setPassword(const U& Password)
		{
			this->Password = Password;
		}
		void setNext(User* Next)
		{
			this->Next = Next;
		}
		T getLogin() const
		{
			return Login;
		}
		U getPassword() const
		{
			return Password;
		}
		User* getNext() const
		{
			return Next;
		}

	};

	template<typename T, typename U, int tableSize> class Hashtable;
	template<typename T, typename U, int tableSize> std::ostream& operator<<(std::ostream& stream, const Hashtable<T, U, tableSize>& ht);

	template<typename T, typename U, int tableSize>
	class Hashtable
	{
	private:
		User<T, U>** ht;
	public:
		int count = 0;

	public:
		Hashtable();
		Hashtable(const Hashtable&) = delete;
		Hashtable& operator=(const Hashtable&) = delete;
		~Hashtable();
	public:
		//template<typename T, typename U, int tableSize>
		//friend std::ostream& operator<<(std::ostream& stream, const Hashtable<T, U, tableSize>& ht);

		int Hash(const T&);
		void Put(const T&, const U&);
		void Remove(const T&, const U&);
		bool Get(const T&, const U&);

		void Serialize();
		void Deserialize();
	};


	template<typename T, typename U>
	std::istream& operator>>(std::istream& stream, User<T, U>& user)
	{
		std::cout << "Login: ";
		stream >> user.Login;

		std::cout << "Password: ";
		stream >> user.Password;

		return stream;
	}

	template<typename T, typename U, int tableSize>
	std::ostream& operator<<(std::ostream& stream, const Hashtable<T, U, tableSize>& hashtable)
	{
		for (int slot = 0; slot != tableSize; ++slot)
		{
			User<T, U>* user = hashtable.ht[slot];

			if (user == nullptr)
			{
				continue;
			}

			std::cout << "[" << static_cast<int>(slot) << "]: ";

			for (;;)
			{
				stream << "Login: " << user->getLogin() << " Password: " << user->getPassword() << ' ';

				if (user->getNext() == nullptr)
				{
					break;
				}

				user = user->getNext();
			}
			std::cout << '\n';
		}

		return stream;
	}

	template<typename T, typename U, int tableSize>
	Hashtable<T, U, tableSize>::Hashtable()
	{
		ht = new User<T, U> * [tableSize];

		for (int i = 0; i != tableSize; ++i)
		{
			ht[i] = new User<T, U>();
			ht[i] = nullptr;
		}
	}


	template<typename T, typename U, int tableSize>
	Hashtable<T, U, tableSize>::~Hashtable()
	{
		for (int slot = 0; slot != tableSize; ++slot)
		{
			if (ht[slot] == nullptr)
			{
				continue;
			}

			User<T, U>* tmp = ht[slot];
			User<T, U>* prev = nullptr;

			while (tmp != nullptr)
			{
				prev = tmp;
				tmp = prev->getNext();
				delete prev;
			}

			ht[slot] = nullptr;
		}
	}


	template<typename T, typename U, int tableSize>
	int Hashtable<T, U, tableSize>::Hash(const T& Login)
	{
		int hashVal = 0;

		const char* c_string = Login.c_str();

		for (int i = 0; i != Login.size(); ++i)
		{
			hashVal += (int)c_string[i];
		}

		return hashVal % tableSize;
	}

	template<typename T, typename U, int tableSize>
	void Hashtable<T, U, tableSize>::Put(const T& Login, const U& Password)
	{
		int HashVal = Hash(Login);

		User<T, U>* tmp = ht[HashVal];
		User<T, U>* prev = nullptr;

		while (tmp != nullptr)
		{
			prev = tmp;
			tmp = prev->getNext();
		}

		if (prev == nullptr)
		{
			tmp = new User<T, U>(Login, Password);
			ht[HashVal] = tmp;
			count++;
		}
		else
		{
			tmp = new User<T, U>(Login, Password);
			prev->setNext(tmp);
			count++;
		}
	}

	template<typename T, typename U, int tableSize>
	void Hashtable<T, U, tableSize>::Remove(const T& Login, const U& Password)
	{
		int HashVal = Hash(Login);

		User<T, U>* tmp = ht[HashVal];
		User<T, U>* prev = nullptr;

		while (tmp->getNext() != nullptr && tmp->getLogin() != Login && tmp->getPassword() != Password)
		{
			prev = tmp;
			tmp = prev->getNext();
		}

		if (prev == nullptr)
		{
			ht[HashVal] = tmp->getNext();
			delete tmp;
			count--;
		}
		else
		{
			prev->setNext(tmp->getNext());
			delete tmp;
			count--;
		}
	}

	template<typename T, typename U, int tableSize>
	bool Hashtable<T, U, tableSize>::Get(const T& Login, const U& Password)
	{
		bool isFind = false;
		int HashVal = Hash(Login);

		User<T, U>* tmp = ht[HashVal];

		for (; tmp != nullptr; tmp = tmp->getNext())
		{
			if (tmp->getLogin() == Login && tmp->getPassword() == Password)
			{
				isFind = true;
			}
		}

		return isFind;
	}

	template<typename T, typename U, int tableSize>
	void Hashtable<T, U, tableSize>::Serialize()
	{
		if (count == 0)
		{
			return;
		}

		Object hashtable("hashtable");

		std::unique_ptr<Primitive> numUsers = Primitive::createPrimitive("^", Type::U32, std::to_string(count));
		hashtable.addEntitie(numUsers.get());


		for (int slot = 0; slot != tableSize; ++slot)
		{
			User<T, U>* tmp = ht[slot];

			if (tmp == nullptr || tmp->isSerialized == true)
			{
				continue;
			}

			std::unique_ptr<Primitive> isNext = Primitive::createPrimitive("!", Type::BOOL, std::to_string(tmp->isNext));
			std::unique_ptr<Primitive> Login = Primitive::createPrimitive("#", Type::U8, tmp->getLogin());
			std::unique_ptr<Primitive> Password = Primitive::createPrimitive("@", Type::U8, tmp->getPassword());

			hashtable.addEntitie(isNext.get());
			hashtable.addEntitie(Login.get());
			hashtable.addEntitie(Password.get());

			tmp->isSerialized = true;

			while (tmp->getNext() != nullptr)
			{
				tmp = tmp->getNext();
				tmp->isNext = true;

				std::unique_ptr<Primitive> isNext = Primitive::createPrimitive("!", Type::BOOL, std::to_string(tmp->isNext));
				std::unique_ptr<Primitive> Login = Primitive::createPrimitive("#", Type::U8, tmp->getLogin());
				std::unique_ptr<Primitive> Password = Primitive::createPrimitive("@", Type::U8, tmp->getPassword());

				hashtable.addEntitie(isNext.get());
				hashtable.addEntitie(Login.get());
				hashtable.addEntitie(Password.get());

				tmp->isSerialized = true;
			}
		}

		saveAll(&hashtable);
	}

	template<typename T, typename U, int tableSize>
	void Hashtable<T, U, tableSize>::Deserialize()
	{
		std::vector<uint8_t> objectFromFile = load("Data/hashtable.hsbrdg");
		uint16_t it = 0;
		Object object = Object::unpack(objectFromFile, it);

		std::string data;
		for (int i = 0; i != objectFromFile.size(); ++i)
		{
			data += objectFromFile[i];
		}

		this->count = data[15];

		std::string log;
		std::string pas;

		for (int i = 0; i != data.size(); ++i)
		{
			if (data[i] == '#')
			{
				i += 3;
				int j = i;
				while (data[j] != '\0')
				{
					log += data[j++];
					i++;
				}
			}
			else if (data[i] == '@')
			{
				i += 3;
				int j = i;
				while (data[j] != '\0')
				{
					pas += data[j++];
					i++;
				}
			}

			if (log != "" && pas != "")
			{
				this->Put(log, pas);
				log.clear();
				pas.clear();
			}
		}
	}
}
