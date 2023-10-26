#ifndef PRODUCT_H
#define PRODUCT_H
#include "Includes.h"

class Product
{
public:
    Product();
    int getPrice() const;
    void setPrice(int newPrice);
    int getPercent() const;
    void setPercent(int newPercent);
    int getTime_limit() const;
    void setTime_limit(int newTime_limit);
    std::string getName() const;
    void setName(const std::string &newName);

    int getCount() const;
    void setCount(int newCount);
    double getWeight_per_pack() const;
    void setWeight_per_pack(double newWeight_per_pack);

    int getId() const;
    void setId(int newId);

private:
    double price;
    int percent;
    int time_limit;
    int count;
    std::string name;
    double weight_per_pack;
    int id;
};

#endif // PRODUCT_H
