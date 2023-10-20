#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>

class Singleton
{
public:
	static T& GetInstance() 
	{
		static T instance;
		return instance;
	}

	//deleting any other instance created of this singleton class
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;

protected:
	//constructor
	Singleton() {}
	//Destructor
	virtual ~Singleton() {}
};

#endif //SINGLETON_H