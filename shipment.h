#ifndef SHIPMENT_H
#define SHIPMENT_H
#include "Globals.h"

class Shipment
{
public:
    Shipment();
    int getDate() const;
    void setDate(int newDate);
    Product *getProduct() const;
    void setProduct(Product *newProduct);
    friend Shipment* generateShipment(int id, int weight);
    int getCount_of_product() const;
    void setCount_of_product(int newCount_of_product);

private:
    int date;
    int count_of_product;
    Product* product;
};

#endif // SHIPMENT_H
