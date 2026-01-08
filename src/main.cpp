#include <iostream>
#include <sstream>
#include <string>

#include "memory_manager.h"

#include "allocator.h"

class first_fit_allocator;
class best_fit_allocator;
class worst_fit_allocator;

#include "allocator/first_fit.cpp"
#include "allocator/best_fit.cpp"
#include "allocator/worst_fit.cpp"

int main()          
{
    memory_manager* manager = nullptr;

    first_fit_allocator first_fit;
    best_fit_allocator best_fit;
    worst_fit_allocator worst_fit;
    buddy_allocator buddy(1024); 

    std::string line;

    std::cout << "memory simulator started\n";


    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            break;
        }

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "exit") {
            break;
        }

        else if (command == "init") {
            std::string word;
            std::size_t size;
            ss >> word >> size; 

            if (manager != nullptr) {
                delete manager;
            }

            manager = new memory_manager(size);
            std::cout << "memory initialized with size " << size << "\n";
        }

        else if (command == "set") {
            std::string word, type;
            ss >> word >> type; 

            if (manager == nullptr) {
                std::cout << "memory not initialized\n";
                continue;
            }

            if (type == "first_fit") {
                manager->set_allocator(&first_fit);
                std::cout << "allocator set to first_fit\n";
            } else if (type == "best_fit") {
                manager->set_allocator(&best_fit);
                std::cout << "allocator set to best_fit\n";
            } else if (type == "worst_fit") {
                manager->set_allocator(&worst_fit);
                std::cout << "allocator set to worst_fit\n";
            } else if (type == "buddy") {
                manager->set_buddy_allocator(&buddy);
                std::cout << "allocator set to buddy\n";
            } else {
                std::cout << "unknown allocator\n";
            }
        }

        else if (command == "malloc") {
            std::size_t size;
            ss >> size;

            if (manager == nullptr) {
                std::cout << "memory not initialized\n";
                continue;
            }

            int id = manager->malloc_block(size);
            if (id == -1) {
                std::cout << "allocation failed\n";
            } else {
                std::cout << "allocated block id=" << id << "\n";
            }
        }

        else if (command == "free") {
            int id;
            ss >> id;

            if (manager == nullptr) {
                std::cout << "memory not initialized\n";
                continue;
            }

            manager->free_block(id);
        }

        else if (command == "dump") {
            if (manager == nullptr) {
                std::cout << "memory not initialized\n";
                continue;
            }

            manager->dump_memory();
        }

        else if (command == "stats") {
            if (manager == nullptr) {
                std::cout << "memory not initialized\n";
                continue;
            }

            manager->print_stats();
        }

        else {
            std::cout << "unknown command\n";
        }
    }

    delete manager;
    std::cout << "exiting simulator\n";
    return 0;
}
