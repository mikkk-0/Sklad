#include "shipment.h"

Shipment::Shipment()
{

}

int Shipment::getDate() const
{
    return date;
}

void Shipment::setDate(int newDate)
{
    date = newDate;
}

Product *Shipment::getProduct() const
{
    return product;
}

void Shipment::setProduct(Product *newProduct)
{
    product = newProduct;
}

int Shipment::getCount_of_product() const
{
    return count_of_product;
}

void Shipment::setCount_of_product(int newCount_of_product)
{
    count_of_product = newCount_of_product;
}

Shipment* generateShipment(Product* product, int weight, int date) {
    Shipment* shpmnt = new Shipment;
    shpmnt->setProduct(product);
    shpmnt->setCount_of_product(weight / product->getWeight_per_pack());
    shpmnt->setDate(date);
    return shpmnt;
}
