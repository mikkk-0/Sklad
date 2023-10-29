#include "query.h"

Query::Query()
{

}

int Query::getDate() const
{
    return date;
}

void Query::setDate(int newDate)
{
    date = newDate;
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
    int priced = 0;
    while (priced < all_prods.size() && all_prods[priced]->getPercent() != 0) priced++;
    int k = rnd() % (all_prods.size() / 2) + 2;
    for (int i = 0; i < std::min((k + 2) / 2, priced); ++i) {
        int id = rnd() % priced;
        id = all_prods[id]->getId();
        int weight = rnd() % 90 + 10;
        q->prods.emplace_back(id, weight);
    }
    for (int i = std::min((k + 2) / 2, priced); i < k; ++i) {
        int id = rnd() % (all_prods.size() - priced) + priced;
        id = all_prods[id]->getId();
        int weight = rnd() % 90 + 10;
        q->prods.emplace_back(id, weight);
    }
    return q;
}
