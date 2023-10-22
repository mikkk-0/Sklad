#include "product.h"

Product::Product() {

}

double Product::getPrice() const
{
    return price;
}

void Product::setPrice(double newPrice)
{
    price = newPrice;
}

int Product::getPercent() const
{
    return percent;
}

void Product::setPercent(int newPercent)
{
    percent = newPercent;
}

int Product::getTime_limit() const
{
    return time_limit;
}

void Product::setTime_limit(int newTime_limit)
{
    time_limit = newTime_limit;
}

std::string Product::getName() const
{
    return name;
}

void Product::setName(const std::string &newName)
{
    name = newName;
}

int Product::getCount() const
{
    return count;
}

void Product::setCount(int newCount)
{
    count = newCount;
}

double Product::getWeight_per_pack() const
{
    return weight_per_pack;
}

void Product::setWeight_per_pack(double newWeight_per_pack)
{
    weight_per_pack = newWeight_per_pack;
}

int Product::getId() const
{
    return id;
}

void Product::setId(int newId)
{
    id = newId;
}
