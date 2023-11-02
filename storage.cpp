#include "storage.h"

Storage::Storage()
{
    this->shpmnts = std::vector<Shipment*>();
    this->prods = std::vector<Product*>();
    this->s_pts = std::vector<Selling_Point*>();
    this->today_qrs = std::vector<Query*>();
    this->shipment_index = 1;
    total = 0;
}

Storage::Storage(std::vector<Product *> * products,  std::vector<std::string> names)
{
    this->shpmnts = std::vector<Shipment*>();
    this->prods = std::vector<Product*>();
    this->s_pts = std::vector<Selling_Point*>();
    this->today_qrs = std::vector<Query*>();
    this->shipment_index = 1;
    total = 0;
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

void add(Product* product, std::vector<Product*>& prods) {
    for (auto& p : prods) {
        if (p->getId() == product->getId() && p->getTime_limit() == product->getTime_limit() && p->getPercent() == product->getPercent()) {
            p->setCount(p->getCount() + product->getCount());
            return;
        }
    }
    prods.emplace_back(product->copy());
}

void Storage::processShipments()
{
    for (int i = 0; i < this->shpmnts.size(); ++i) {
        auto shp = this->shpmnts[i];
        shp->decLeftDays();
        if (shp->getLeft_days() == 0) {
            for (auto& p : shp->getProducts()) {
                p->setTime_limit(p->getTime_limit() + 1);
                add(p, this->prods);
                delete p;
            }
            std::swap(this->shpmnts[i], this->shpmnts.back());
            this->shpmnts.pop_back();
            delete shp;
            i--;
        }
    }
    orderShipments();
    orderProducts();
}

void Storage::generateQueries()
{
    int c = rnd() % this->s_pts.size();
//    int c = 0;
    this->today_qrs.clear();
    this->today_qrs_reply.clear();
    this->info_products.clear();
    for (int i = 0; i < c; ++i) {
        Query* query = generate_query(this->getProds());
        if (query->getProds().empty()) break;
        Selling_Point* pt = this->s_pts[rnd() % c];
        query->setS_pt(pt);
        std::vector<std::pair<int, double>> reply_vec;
        auto que = query->getProds();
        info_products.emplace_back();
        for (auto& [ind, need] : que) {
            Product* prod = prods[ind];
            int give = std::min(prod->getCount(), (int)ceil((double)need / prod->getWeight_per_pack()));
            prod->setCount(prod->getCount() - give);
            reply_vec.emplace_back(ind, give);
            info_products.back().emplace_back(prod->getName(), prod->getWeight_per_pack());
            total += give * prod->getPrice();
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
                i--;
            }
        }
        orderProducts();
    }
}

int Storage::addShipment(Shipment *shipment)
{
    shipment->setId(nextShipment());
    int id = shipment->getId();
    this->shpmnts.push_back(shipment);
    double sum = 0;
    for (auto& p : shipment->getProducts()) {
        sum += p->getPrice() * p->getCount();
    }
    total -= sum * (1 - (shipment->getPercent() / 100.0));
    orderShipments();

    return id;
}

void Storage::orderProducts()
{
    std::sort(this->prods.begin(), this->prods.end(), [&](Product* &a, Product* &b) {
        if (b->getTime_limit() == 0) return true;
        if (a->getTime_limit() == 0) return false;
        if (a->getTime_limit() == b->getTime_limit()) {
            if (a->getPercent() == 0) return true;
            if (b->getPercent() == 0) return false;
            return a->getPrice() < b->getPrice();
        }
        return a->getTime_limit() < b->getTime_limit();
    });
}

void Storage::orderShipments()
{
    std::sort(this->shpmnts.begin(), this->shpmnts.end(), [&](Shipment* &a, Shipment* &b) {
        return a->getLeft_days() < b->getLeft_days();
    });
}

void Storage::newDay(std::vector<Product*>& all_prods)
{
    processShipments();
    generateQueries();
    processProducts(all_prods);
}

void Storage::processProducts(std::vector<Product*>& all_prods) {
    for (auto& p : prods) {
        if (p->getTime_limit() == 0) {
            continue;
        }
        p->decTimeLimit();
        if (p->getTime_limit() <= 3) {
            p->applyPercent();
        }
    }
    orderProducts();
    std::vector<Product*> need;
    for (auto& pr : all_prods) {
        int count = 0;
        for (auto& x : prods) {
            if (x->getTime_limit() == 0) break;
            if (x->getId() == pr->getId()) {
                count += x->getCount();
            }
        }
        if (count < pr->getCount_ship()) {
            need.emplace_back(pr->copy());
        }
    }
    for (int i = 0; i < need.size(); ++i) {
        auto x = need[i];
        bool was = false;
        for (auto& shp : shpmnts) {
            for (auto& p : shp->getProducts()) {
                if (p->getId() == x->getId()) {
                    was = true;
                    break;
                }
            }
            if (was) break;
        }
        if (was) {
            std::swap(need[i], need.back());
            need.pop_back();
            delete x;
            i--;
        }
    }
    if (!need.empty()) {
        this->addShipment(generateShipment(need, rnd() % 4 + 1));
    }
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

double Storage::getTotal() const {
    return total;
}
