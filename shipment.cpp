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

Shipment* generateShipment(int id, int weight) {
    Shipment* shpmnt = new Shipment;
    id %= products.size();
    shpmnt->setProduct(products[id]);
    shpmnt->setCount_of_product(weight / shpmnt->getProduct()->getWeight_per_pack());
    shpmnt->setDate(CURRENT_DAY + delay);
    return shpmnt;
}
