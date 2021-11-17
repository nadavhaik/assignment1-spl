#include "Action.h"
#include <string>


using namespace std;

OpenTrainer::OpenTrainer(int id, vector<Customer *> &customersList) : BaseAction(), trainerId(id) {


}

void OpenTrainer::act(Studio &studio) {

}

string OpenTrainer::toString() const {
    return "";
}
