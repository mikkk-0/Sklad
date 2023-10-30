#include "shipment.h"

Shipment::Shipment()
{

}

int Shipment::getLeft_days() const
{
    return left_days;
}

void Shipment::setLeft_days(int newLeft_days)
{
    left_days = newLeft_days;
}

void Shipment::setProducts(const std::vector<Product *> &newProducts)
{
    products = newProducts;
}

void Shipment::decLeftDays()
{
    left_days--;
}

std::vector<Product *> Shipment::getProducts() const
{
    return products;
}

int Shipment::getId() const
{
    return id;
}

void Shipment::setId(int newId)
{
    id = newId;
}

Shipment* generateShipment(std::vector<Product*>& products, int days) {
    Shipment* shpmnt = new Shipment;
    shpmnt->setProducts(products);
    shpmnt->setLeft_days(days);
    return shpmnt;
}
