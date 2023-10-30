#include "query.h"

Query::Query()
{

}

size_t Query::size() const
{
    return prods.size();
}

std::pair<int, int> Query::at(int &x) const
{
    if (x >= this->size()) throw std::exception();
    return prods[x];
}

Selling_Point *Query::getS_pt() const
{
    return s_pt;
}

void Query::setS_pt(Selling_Point *newS_pt)
{
    s_pt = newS_pt;
}

std::vector<std::pair<int, double> > Query::getProds() const
{
    return prods;
}

void Query::setProds(const std::vector<std::pair<int, double> > &newProds)
{
    prods = newProds;
}

Query *generate_query(std::vector<Product *> all_prods)
{
    Query* q = new Query;
    int sz = 0;
    while (sz < all_prods.size() && all_prods[sz]->getTime_limit() != 0) sz++;
    int priced = 0;
    while (priced < sz && all_prods[priced]->getPercent() != 0) priced++;
    std::vector<std::pair<int, double>> pr;
    if (sz == 0) {
        q->setProds(pr);
        return q;
    }
    if (sz == 1) {
        int id = 0;
        int weight = rnd() % 90 + 10;
        pr.emplace_back(id, weight);
        q->setProds(pr);
        return q;
    }
    int k = rnd() % (sz / 2) + 2;
    for (int i = 0; i < std::min((k + 2) / 2, priced); ++i) {
        int id = rnd() % priced;
        int weight = rnd() % 90 + 10;
        pr.emplace_back(id, weight);
    }
    for (int i = std::min((k + 2) / 2, priced); i < k; ++i) {
        int id = rnd() % (all_prods.size() - priced) + priced;
        int weight = rnd() % 90 + 10;
        pr.emplace_back(id, weight);
    }
    q->setProds(pr);
    return q;
}
