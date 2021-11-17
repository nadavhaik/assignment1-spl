#include "Action.h"
#include "Studio.h"
using namespace std;

Order::Order(int id) : trainerId(id) {

}

void Order::act(Studio &studio) {

}

std::string Order::toString() const {
    return "";
}
