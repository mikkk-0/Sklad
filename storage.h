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
    Storage(std::vector<Product*>*);
    void processShipments();
    void generateQueries();
    void addShipment(Shipment* shipment);
    void orderProducts();
    void orderShipments();

    std::vector<Selling_Point *> getS_pts() const;
    std::vector<Product *> getProds() const;
    std::vector<Query *> getToday_qrs() const;
    std::vector<Shipment *> getShpmnts() const;

private:
    std::vector<Selling_Point*> s_pts;
    std::vector<Product*> prods;
    std::vector<Query*> today_qrs;
    std::vector<Shipment*> shpmnts;

};

#endif // STORAGE_H
