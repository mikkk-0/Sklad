#include "storage.h"

Storage::Storage()
{
    this->shpmnts = std::vector<Shipment*>();
    this->prods = std::vector<Product*>();
    this->s_pts = std::vector<Selling_Point*>();
    this->today_qrs = std::vector<Query*>();
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

std::vector<Selling_Point *> Storage::getS_pts() const
{
    return s_pts;
}

std::vector<Product *> Storage::getProds() const
{
    return prods;
}

std::vector<Query *> Storage::getToday_qrs() const
{
    return today_qrs;
}

std::vector<Shipment *> Storage::getShpmnts() const
{
    return shpmnts;
}
