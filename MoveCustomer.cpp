#include "Action.h"
using namespace std;

MoveCustomer::MoveCustomer(int src, int dst, int customerId): BaseAction(), srcTrainer(src), dstTrainer(dst), id(customerId) {

}

void MoveCustomer::act(Studio &studio) {

}

std::string MoveCustomer::toString() const {
    return std::string();
}
