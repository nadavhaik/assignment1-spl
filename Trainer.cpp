Trainer::Trainer(int t_capacity): capacity(t_capacity) {}

void Trainer::openTrainer(){
    open = true;
}
void Trainer::closeTrainer(){
    open = false;
}

bool Trainer::isOpen(){
    return open;
}

void Trainer::addCustomer(Customer* customer){
    customersList.push_back(customer);
}
void Trainer::removeCustomer(int id){
    for(std::size_t i = 0; i<customersList.size();i++) {
        Customer *c = customersList[i];
        if(c->getId() == id) {
            // only deleting *FROM THE LIST*
            customersList.erase(customersList.begin() + i);
            break;
        }
    }
}

int Trainer::getCapacity() const {
    return capacity;
}
