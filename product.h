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
    void applyPercent();

    int getCount() const;
    void setCount(int newCount);
    double getWeight_per_pack() const;
    void setWeight_per_pack(double newWeight_per_pack);

    Product* copy();

    int getId() const;

    void setId(int newId);

    bool getSeen() const;
    void makeSeen();

    int getCount_ship() const;
    void setCount_ship(int newCount_ship);

private:
    double price;
    double percent;
    int time_limit;
    int count;
    std::string name;
    double weight_per_pack;
    int id;
    int count_ship;
    bool seen;
};

#endif // PRODUCT_H
