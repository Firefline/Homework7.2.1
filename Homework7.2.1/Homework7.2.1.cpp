// Homework7.2.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

class Window
{
protected:
    std::atomic<int> max_people = 0;
    std::atomic<int> people = 1;
    //int max_people = 0;
    //int people = 1;
public:
    Window(int max_people_)
    {
        max_people.exchange (max_people_);
    }
    void income()
    {
        while (people != max_people)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            //people.fetch_add(1);
            ++people;
            std::cout << people << " ";
        }
    }
    void outcome()
    {
        while (people != 0)
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            //people.fetch_sub(1);
            --people;
            std::cout << people << " ";
        }
    }
    unsigned operator++(int) 
    {
        return people.fetch_add(1);
    }
    unsigned operator--(int)
    {
        return people.fetch_sub(1);
    }
};

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");

    int people_num = 5;

    Window window(people_num);

    std::cout << "Current workload: ";
    std::thread t1(&Window::income, &window);
    std::thread t2(&Window::outcome, &window);
    t1.join();
    t2.join();

    return 0;
}