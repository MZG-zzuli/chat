#ifndef SINGLETON_H
#define SINGLETON_H
#include<QObject>
#include<memory>
#include <mutex>
#include<iostream>
#include<QDebug>
template<typename T>
class Singleton
{
protected:
    Singleton()=default;
    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton<T>&)=delete;
    static std::shared_ptr<T> _instance;
public:
    static std::shared_ptr<T> getInstance()
    {
        static std::once_flag once;
        std::call_once(once,[&](){
            _instance=std::shared_ptr<T>(new T);
        });
        return _instance;
    }
    ~Singleton()
    {
        std::cout<<"delete instance";
    }
};
template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

#endif // SINGLETON_H
