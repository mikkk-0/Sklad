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

private:
    int date;
    std::vector<std::pair<int, int>> prods; // {Product_id, weight}
};

#endif // QUERY_H
