#ifndef SHIPMENT_H
#define SHIPMENT_H
#include "Includes.h"
#include "product.h"

class Shipment
{
public:
    Shipment();
    int getLeft_days() const;
    void setLeft_days(int newLeft_days);
    void setProducts(const std::vector<Product *> &newProducts);
    void decLeftDays();
    std::vector<Product *> getProducts() const;

    int getId() const;
    void setId(int newId);

private:
    int left_days;
    std::vector<Product*> products;
    int id;
};

Shipment* generateShipment(std::vector<Product*> &products, int days);

#endif // SHIPMENT_H
