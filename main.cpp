#include <iostream>
#include <vector>
#include <memory>

using namespace std;

void rangeBasedForLoop()
{
    vector<int> vect = {1,2,3,5,6};
    for(auto i: vect)
    {
        cout << i << " ";
    }
}

class MyClass
{
public:
    MyClass()
    {
        cout << "MyClass constructor called." << endl;
    }
    
    ~MyClass()
    {
        cout << "MyClass destructor called." << endl;
    }
    
    void sayHello() const
    {
        cout << "hello from MyClass" << endl;
    }
};

void uniquePointerExercise()
{
    // unique_ptr ensures that the memory allocated to MyClass is released when the pointer goes out of scope
    unique_ptr<MyClass> myPtr = make_unique<MyClass>();
    myPtr->sayHello();
    
    // alternative using standard pointers
//    cout << "standard pointers:" << endl;
//    MyClass* myPtr2 = new MyClass();
//    myPtr2->sayHello();
    // when the standard pointer is used, the destructor is not called
    
}

class Node
{
public:
    int value;
    vector<shared_ptr<Node>> neighbors;
    
    Node(int val): value(val)
    { cout << "Node constructor called with node value " << value << endl;}
    
    ~Node()
    {
        cout << "Node destructor called with value " << value << endl;
    }
    
    void addNeighbor(const shared_ptr<Node>& neighbor)
    {
        neighbors.push_back(neighbor);
    }
    
    void displayNeighbors() const{
        cout << "Node " << value << " has neighbors: " ;
        for(const auto& neighbor: neighbors)
        {
            cout << neighbor-> value << " ";
        }
        cout << endl;
    }
    
};

// shared pointers instead of normal pointers are used for a better memory management
void sharedPointerExercise()
{
    // just create shared pointers to node objects.
    shared_ptr<Node> node1 = make_shared<Node>(1);
    shared_ptr<Node> node2 = make_shared<Node>(2);
    shared_ptr<Node> node3 = make_shared<Node>(3);
    shared_ptr<Node> node4 = make_shared<Node>(4);
    
    // make neighbors in both directions
    node1->addNeighbor(node2);
    node1->addNeighbor(node3);
    
    node3->addNeighbor(node2);
    node3->addNeighbor(node4);
    
    // these 2 below are equivalent
    node1->displayNeighbors();
    node3->displayNeighbors();
    
}

class Resource
{
public:
  Resource()
    {
        cout << "resource is created" << endl;
    }

    ~Resource()
    {
        cout << "resource destroyed" << endl;
    }
    
    void doSomething()
    {
        cout << "resource is doing something" << endl;
    }
    
};

void exampleResource()
{
    shared_ptr<Resource> ptr1;
    
    {
        cout << "entering inner block" << endl;
        shared_ptr<Resource> ptr2 = make_shared<Resource>();
        cout << "ptr2 use_count: " << ptr2.use_count() << endl;
        
        {
            shared_ptr<Resource> ptr3 = ptr2;
            cout << "ptr2 use_count: " << ptr2.use_count() << endl;
            cout << "ptr3 use_count: " << ptr3.use_count() << endl;
        }
        
        std::cout << "ptr2 use_count after ptr3 is out of scope: " << ptr2.use_count() << '\n';
        
        ptr1 = ptr2;
        std::cout << "ptr2 use_count after assigning it to ptr1: " << ptr2.use_count() << '\n';
        cout << "leaving inner block" << endl;
        
    }
    
    cout << "ptr1 use_count after inner block: " << ptr1.use_count() << '\n';

    
}


int main(int argc, const char * argv[]) {

    // c++ 11: 1. smart pointers; 2. move semantics
    
    exampleResource();
    
    return 0;
}
