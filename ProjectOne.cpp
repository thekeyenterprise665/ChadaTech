/*
ProjectOne.cpp 

KEYNEISHA D. MCNEALEY 

PROFESSOR HECKER 

06/05/2024 
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <string>
#include <iomanip>

class Clock {
public:
    Clock() : running(true), thread(&Clock::run, this) {}

    ~Clock() {
        stop();
    }

    void stop() {
        if (running) {
            running = false;
            thread.join();
        }
    }

    void display() {
        std::unique_lock<std::mutex> lock(mutex);
        std::cout << "12-hour clock: " << std::put_time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()), "%I:%M:%S %p") << std::endl;
        std::cout << "24-hour clock: " << std::put_time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()), "%T") << std::endl;
    }

private:
    bool running;
    std::thread thread;
    std::mutex mutex;

    void run() {
        while (running) {
            std::chrono::milliseconds dura(1000); // 1 second
            std::this_thread::sleep_for(dura);

            std::unique_lock<std::mutex> lock(mutex);
            std::cout << "12-hour clock: " << std::put_time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()), "%I:%M:%S %p") << std::endl;
            std::cout << "24-hour clock: " << std::put_time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()), "%T") << std::endl;
        }
    }
};

void displayMenu() {
    std::cout << "*****************************" << std::endl;
    std::cout << "*          Clock           *" << std::endl;
    std::cout << "*****************************" << std::endl;
    std::cout << "* 1. Display Clocks       *" << std::endl;
    std::cout << "* 2. Exit                 *" << std::endl;
    std::cout << "*****************************" << std::endl;
}

int main() {
    Clock clock;

    while (true) {
        displayMenu();

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                clock.display();
                std::cout << std::endl;
                break;
            case 2:
                clock.stop();
                std::cout << "Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }

        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}
