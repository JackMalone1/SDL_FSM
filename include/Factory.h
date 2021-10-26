#pragma once


#include <vector>

template <typename T>
class Factory
{
public:
    virtual T* getObject(){return new T()};
};