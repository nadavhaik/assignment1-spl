
#include "Customer.h"

Customer::Customer(std::string c_name, int c_id) :
        id(c_id), name(c_name) {}

int Customer::getId() const {
    return id;
}
