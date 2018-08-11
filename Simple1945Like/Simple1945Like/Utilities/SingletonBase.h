#pragma once

template <typename T>
class SingletonBase
{
public:
    static T* GetInstance();
    void ReleaseInstance();

protected:
    SingletonBase() {}
    virtual ~SingletonBase() {}

    static T* instance;
};

template <typename T>
T* SingletonBase<T>::instance = nullptr;

template <typename T>
T* SingletonBase<T>::GetInstance()
{
    if (!instance)
    {
        instance = new T;
    }

    return instance;
}

template <typename T>
void SingletonBase<T>::ReleaseInstance()
{
    if (instance)
    {
        delete instance;

        instance = nullptr;
    }
}
