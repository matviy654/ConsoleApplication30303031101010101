#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Car {
    std::string model;

public:
    explicit Car(const std::string& modelName) : model(modelName) {}
    void showModel() const {
        std::cout << "Car model: " << model << std::endl;
    }
};

class Person {
    std::string name;
    int age;

public:
    Person(const std::string& name, int age) : name(name), age(age) {}
    void showInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

class Edge; 
class Node {
public:
    std::shared_ptr<Edge> edge;
    void connect(const std::shared_ptr<Edge>& e) {
        edge = e;
    }
};

class Edge {
public:
    std::weak_ptr<Node> node; 
    void connect(const std::shared_ptr<Node>& n) {
        node = n;
    }
};

class FileManager {
    FILE* file;

public:
    explicit FileManager(const std::string& fileName) {
        file = fopen(fileName.c_str(), "w");
        if (file) {
            std::cout << "File opened: " << fileName << std::endl;
        }
    }
    ~FileManager() {
        if (file) {
            fclose(file);
            std::cout << "File closed.\n";
        }
    }
};
void dynamicArrayExample() {
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
    }
    std::cout << "Dynamic array elements: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
 
    {
        std::unique_ptr<Car> car1 = std::make_unique<Car>("Tesla Model S");
        car1->showModel();

        std::unique_ptr<Car> car2 = std::move(car1);
        if (!car1) {
            std::cout << "car1 no longer owns the object.\n";
        }
        car2->showModel();
    }

    {
        std::shared_ptr<Person> person = std::make_shared<Person>("Alice", 30);
        std::shared_ptr<Person> personShared = person;

        person->showInfo();
        std::cout << "Shared pointer use count: " << person.use_count() << std::endl;
    }

    {
        std::shared_ptr<Node> node = std::make_shared<Node>();
        std::shared_ptr<Edge> edge = std::make_shared<Edge>();

        node->connect(edge);
        edge->connect(node);

        std::cout << "Cycle avoided using weak_ptr.\n";
    }

    {
        std::unique_ptr<FileManager> fileManager = std::make_unique<FileManager>("example.txt");
    }

    dynamicArrayExample();

    return 0;
}
