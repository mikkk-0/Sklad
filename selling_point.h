#ifndef SELLING_POINT_H
#define SELLING_POINT_H
#include "Includes.h"
#include "query.h"

class Selling_Point
{
public:
    Selling_Point();
    std::string getName() const;
    void setName(const std::string &newName);

private:
    std::string name;
    std::vector<Query*> queries;
};

#endif // SELLING_POINT_H
