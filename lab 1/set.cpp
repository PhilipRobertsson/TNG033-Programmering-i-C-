#include "set.hpp"

// std::size_t is defined in the C++ standard library
// std::size_t is an unsigned integer type that can store the maximum size of any possible object
// sizes are non-negative integers -- i.e. unsigned integer type

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* ******************************************************** */

// Default constructor
Set::Set():head(new Node),counter(0) {
}

// Constructor for creating a set from an int
Set::Set(int v) : Set{} {
    insert(v);
}

// Constructor: create a set with the elements in V
// V is not sorted and may contain repeated elements
Set::Set(const std::vector<int>& V) :Set{} {
    for (int i = 0; i < std::ssize(V); i++) {
        insert(V[i]);
    }
}

// copy constructor
Set::Set(const Set& source) :Set{} {
    Node* ptr1 = source.head->next;
    Node* ptr2 = head;

    while (ptr1) {
        insert(ptr2, ptr1->value);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    counter = source.counter;
}

// Assignment operator: copy-and-swap idiom
Set& Set::operator=(Set s) {
    std::swap(head, s.head);
    std::swap(counter, s.counter);
    return *this; // destructor for s is called
}

// Destructor: deallocate all nodes
Set::~Set() {
    Node* ptr = head;
    while (ptr) {
        head = head->next;
        delete ptr; // remove(ptr);
        ptr = head;
    }
    head = nullptr;
}


// Return number of elements in the set
std::size_t Set::cardinality() const {
    return counter;
}

// Test if set is empty
bool Set::empty() const {
    return (counter == 0);
}

// Test if x is an element of the set
bool Set::member(int x) const {
    Node* ptr = head;
    while (ptr) {
        if (ptr->value == x) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

bool Set::operator<=(const Set& b) const {
    Node* ptr1 = head->next;
    Node* ptr2 = b.head->next;
    int opperatorCounter = 0;
    while (ptr1) {
        while (ptr2) {
            if (ptr1->value == ptr2->value) {
                opperatorCounter++;
                break;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    return(opperatorCounter == counter);
}

bool Set::operator==(const Set& b) const {
    return(b <= *this && *this <= b);
}

bool Set::operator!=(const Set& b) const {
    Node* ptr1 = head->next;
    Node* ptr2 = b.head->next;
    int opperatorCounter = 0;
    while (ptr1) {
        while (ptr2) {
            if (ptr1->value == ptr2->value) {
                opperatorCounter++;
                break;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    return!(opperatorCounter == counter && counter == b.counter);
}

bool Set::operator<(const Set& b) const {
    Node* ptr1 = head->next;
    Node* ptr2 = b.head->next;
    int opperatorCounter = 0;
    while (ptr1) {
        while (ptr2) {
            if (ptr1->value == ptr2->value) {
                opperatorCounter++;
                break;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    return (opperatorCounter == counter && counter < b.counter);
}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const {
    Node* ptr1 = head->next;
    Node* ptr2 = b.head->next;
    std::vector<int> unionV;
    while (ptr1) {
        unionV.push_back(ptr1->value);
        ptr1 = ptr1->next;
    }
    while (ptr2) {
        unionV.push_back(ptr2->value);
        ptr2 = ptr2->next;
    }
    return Set{unionV};
}

// Set intersection
Set Set::operator*(const Set& b) const {
    Node* ptr = head->next;
    std::vector<int> intersectV;
    while (ptr) {
        if (b.member(ptr->value)) {
            intersectV.push_back(ptr->value);
        }
        ptr = ptr->next;
    }
    return Set{intersectV};
}

// Set difference
Set Set::operator-(const Set& b) const {
    Node* ptr = head->next;
    std::vector<int> diffV;
    while (ptr) {
        if (!b.member(ptr->value)) {
            diffV.push_back(ptr->value);
        }
        ptr = ptr->next;
    }
    return Set{diffV};
}

// set difference with set {x}
Set Set::operator-(int x) const {
    return *this - Set{ x };
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Set& theSet) {
    if (theSet.empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* temp = theSet.head->next;
        os << "{ ";

        while (temp != nullptr) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/

void Set::insert(Node* ptr, int value) {
    Node* newNode = new Node(value, ptr->next);
    ptr->next = newNode;
    counter++;
}
void Set::insert(int value) {
    Node* ptr = head;
    while ((ptr->next != nullptr) && (ptr->next->value < value)) {
        ptr = ptr->next;
    }
    if ((ptr->next == nullptr) || (ptr->next->value != value)) {
        insert(ptr, value);
    }
}
void Set::remove(Node* ptr) {
    delete ptr;
    ptr = nullptr;
}

