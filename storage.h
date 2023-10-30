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
    void processProducts();
    void generateQueries();
    void addShipment(Shipment* shipment);
    void orderProducts();
    void orderShipments();
    void newDay();
    int nextShipment();

    std::vector<Selling_Point *> getS_pts() const;
    std::vector<Product *> getProds() const;
    std::vector<Query *> getToday_qrs() const;
    std::vector<Shipment *> getShpmnts() const;

    std::vector<Query *> getToday_qrs_reply() const;
    std::vector<std::vector<std::pair<std::string, double> > > getInfo_products() const;

private:
    std::vector<Selling_Point*> s_pts;
    std::vector<Product*> prods;
    std::vector<Query*> today_qrs, today_qrs_reply;
    std::vector<Shipment*> shpmnts;
    std::vector<std::vector<std::pair<std::string, double>>> info_products;

    int shipment_index;
};

#endif // STORAGE_H
