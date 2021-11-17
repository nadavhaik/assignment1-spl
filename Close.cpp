#include "Action.h"
using namespace std;

Close::Close(int id) : BaseAction(), trainerId(id) {

}

void Close::act(Studio &studio) {

}

std::string Close::toString() const {
    return std::string();
}
