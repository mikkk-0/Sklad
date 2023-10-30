#ifndef PRODUCT_H
#define PRODUCT_H
#include "Includes.h"

class Product
{
public:
    Product();
    double getPrice() const;
    void setPrice(double newPrice);
    double getPercent() const;
    void setPercent(double newPercent);
    int getTime_limit() const;
    void setTime_limit(int newTime_limit);
    std::string getName() const;
    void setName(const std::string &newName);
    void decTimeLimit();

    int getCount() const;
    void setCount(int newCount);
    double getWeight_per_pack() const;
    void setWeight_per_pack(double newWeight_per_pack);

    Product* copy();

private:
    double price;
    double percent;
    int time_limit;
    int count;
    std::string name;
    double weight_per_pack;
};

#endif // PRODUCT_H
