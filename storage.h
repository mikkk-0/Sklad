#ifndef STORAGE_H
#define STORAGE_H
#include "Includes.h"
#include "selling_point.h"
#include "product.h"
#include "shipment.h"

class Storage
{
public:
    Storage();
    void processShipments();
    void generateQueries();

private:
    std::vector<Selling_Point*> s_pts;
    std::vector<Product*> prods;
    std::vector<Query*> today_qrs;
    std::vector<Shipment*> shpmnts;
    void orderProducts();


};

#endif // STORAGE_H
