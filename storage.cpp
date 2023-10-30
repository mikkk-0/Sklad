#include "storage.h"

Storage::Storage()
{
    this->shpmnts = std::vector<Shipment*>();
    this->prods = std::vector<Product*>();
    this->s_pts = std::vector<Selling_Point*>();
    this->today_qrs = std::vector<Query*>();
    shipment_index = 1;
}

Storage::Storage(std::vector<Product *> * products,  std::vector<std::string> names)
{
    this->prods.clear();
    for (int i = 0; i < products->size(); ++i) {
        prods.emplace_back(products->at(i)->copy());
    }
    this->s_pts.clear();
    for (int i = 0; i < names.size(); ++i) {
        Selling_Point* pt = new Selling_Point;
        pt->setName(names[i]);
        s_pts.emplace_back(pt);
    }
}

int Storage::nextShipment() {
    return shipment_index++;
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
    int c = rnd() % this->s_pts.size();
    this->today_qrs.clear();
    this->today_qrs_reply.clear();
    this->info_products.clear();
    for (int i = 0; i < c; ++i) {
        Selling_Point* pt = this->s_pts[rnd() % c];
        Query* query = generate_query(this->getProds());
        query->setS_pt(pt);
        std::vector<std::pair<int, double>> reply_vec;
        auto que = query->getProds();
        info_products.emplace_back();
        for (auto& [ind, need] : que) {
            int give = std::min(this->prods[ind]->getCount(), (int)ceil((double)need / prods[ind]->getWeight_per_pack()));
            prods[ind]->setCount(prods[ind]->getCount() - give);
            reply_vec.emplace_back(ind, give);
            info_products.back().emplace_back(prods[ind]->getName(), prods[ind]->getWeight_per_pack());
        }
        Query* qr = new Query;
        qr->setS_pt(pt);
        qr->setProds(reply_vec);
        today_qrs.emplace_back(query);
        today_qrs_reply.emplace_back(qr);
        for (int i = 0; i < prods.size(); ++i) {
            if (prods[i]->getCount() == 0) {
                std::swap(prods[i], prods.back());
                delete prods.back();
                prods.pop_back();
            }
        }
        orderProducts();
    }
}

void Storage::addShipment(Shipment *shipment)
{
    shipment->setId(nextShipment());
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

void Storage::newDay()
{
    processShipments();
    generateQueries();
    processProducts();
}

void Storage::processProducts() {
    for (auto& p : prods) {
        if (p->getTime_limit() == 0) continue;
        p->decTimeLimit();
    }
    orderProducts();
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

std::vector<Query *> Storage::getToday_qrs_reply() const
{
    return today_qrs_reply;
}

std::vector<std::vector<std::pair<std::string, double> > > Storage::getInfo_products() const
{
    return info_products;
}
