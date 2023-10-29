#include "storage.h"

Storage::Storage()
{

}

void Storage::processShipments()
{
    for (int i = 0; i < this->shpmnts.size(); ++i) {
        auto shp = this->shpmnts[i];
        if (shp->getLeft_days() == 0) {
            for (auto& p : shp->getProducts()) {
                this->prods.emplace_back(p->copy());
                delete p;
            }
            std::swap(this->shpmnts[i], this->shpmnts.back());
            this->shpmnts.pop_back();
            delete shp;
            i--;
        } else {
            shp->decLeftDays();
        }
    }
    orderShipments();
    orderProducts();
}

void Storage::generateQueries()
{

}

void Storage::addShipment(Shipment *shipment)
{
    this->shpmnts.push_back(shipment);
    orderShipments();
}

void Storage::orderProducts()
{
    std::sort(this->prods.begin(), this->prods.end(), [&](Product* &a, Product* &b) {
        if (b->getTime_limit() == 0) return true;
        if (a->getTime_limit() == 0) return false;
        return a->getTime_limit() < b->getTime_limit();
    });
}

void Storage::orderShipments()
{
    std::sort(this->shpmnts.begin(), this->shpmnts.end(), [&](Shipment* &a, Shipment* &b) {
        return a->getLeft_days() < b->getLeft_days();
    });
}
