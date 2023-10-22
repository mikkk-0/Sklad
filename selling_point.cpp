#include "selling_point.h"

Selling_Point::Selling_Point()
{

}

std::string Selling_Point::getName() const
{
    return name;
}

void Selling_Point::setName(const std::string &newName)
{
    name = newName;
}
