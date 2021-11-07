#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include "Customer.h"
#include "Workout.h"
//#include "Studio.h"
#include "iostream"

typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    Trainer(int t_capacity);
    int getCapacity() const{
        return capacity;
    }
    void addCustomer(Customer* customer){
        customersList.push_back(customer);
    }
    void removeCustomer(int id){}

    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer(){
        open = true;
    }
    void closeTrainer(){
        open = false;
    }
    int getSalary();
    bool isOpen(){
        return open;
    }
private:
    int capacity;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)

};

Trainer::Trainer (int t_capacity):
    capacity(t_capacity) {}


#endif