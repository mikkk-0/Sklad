#ifndef QUERY_H
#define QUERY_H
#include "Includes.h"
#include "product.h"

class Query
{
public:
    Query();
    int getDate() const;
    void setDate(int newDate);
    friend Query* generate_query(std::vector<Product*> all_prods);
    size_t size() const;
    std::pair<int, int> at(int& x) const;

    Selling_Point *getS_pt() const;
    void setS_pt(Selling_Point *newS_pt);
    std::vector<std::pair<int, double> > getProds() const;
    void setProds(const std::vector<std::pair<int, double> > &newProds);

private:
    int date;
    Selling_Point* s_pt;
    std::vector<std::pair<int, double>> prods; // {Product_id, weight}
};

#endif // QUERY_H
