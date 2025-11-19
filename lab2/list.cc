#include "list.h"
#include <sstream>
#include <stdexcept>

using namespace std;

// Kommentar: Jag ser att ni växlar språk på era kommentarer. Det är lite udda.
// Kommentar: Ni har ganska mycket liknande funktionalitet i era find-funktioner 
//    (huvudsakligen era loopar). Finns det något sätt man hade kunnat bryta ut loopandet?

List::List() : first(nullptr) {}

// Kopieringskonstruktor
List::List(List const &other): first(nullptr)
{
    Node *previous_node {nullptr};
    Node *current_other {other.first};
    while (current_other != nullptr)
    {
        Node *new_node {new Node{current_other->value, nullptr}};

        if (previous_node == nullptr) 
        {
            first = new_node;
        }
        else {
            previous_node->next = new_node;
        }
        
        previous_node = new_node;
        current_other = current_other->next; 
    }
}

// Kopieringstilldelningsoperator
List &List::operator=(List const &rhs)
{
    List tmp{rhs};
    swap(first, tmp.first);

    return *this;
}

// Destruktor
List::~List()
{
    if (is_empty())
    {
        return;
    }

    Node *current_node {first};
    while (current_node != nullptr)
    {
        Node *next {current_node->next};
        delete current_node;
        current_node = next;
    }
    first = nullptr;
}

// Flyttkonstruktor
List::List(List &&other): first(nullptr)
{
    // Swap lists, so that this receives the wanted other.first
    // While other gets the unwanted old list (if not nullptr)
    // and we dont need to deal with it because it will destructure on
    // out-of-scope
    swap(first, other.first);
}

// Flytttilldelingsoperator
List &List::operator=(List &&rhs)
{
    swap(first, rhs.first);
    return *this;
}

void List::insert(int value)
{
    List::insert(value, nullptr);
}

void List::insert(int value, Node *current_node)
{
    // If trying to insert into a new list: Create it
    if (is_empty())
    {
        Node *new_node {new Node{value, nullptr}};
        first = new_node;
        return;
    }

    // If its the first round of recursion
    if (current_node == nullptr)
    {
        current_node = first;

        // Check if the first item is smaller than new_node: insert new_node on the
        // first place
        if (current_node->value > value)
        {
            Node *new_node {new Node{value, first}};
            first = new_node;
            return;
        }
    }

    // If current_node is the last item: Make our item last
    if (current_node->next == nullptr)
    {
        Node *new_node {new Node{value, nullptr}};
        current_node->next = new_node;
        return;
    }

    // If next node is bigger: Insert new node between it
    if (current_node->next->value > value)
    {
        Node *new_node {new Node{value, current_node->next}};
        current_node->next = new_node;
        return;
    }

    insert(value, current_node->next);
}

void List::remove(int value)
{
    if (is_empty())
    {
        throw logic_error("Trying to remove a value from an empty list");
        return;
    }

    Node *prev_node {nullptr};
    Node *current_node {first};
    while (current_node != nullptr)
    {
        // If we found the node to delete:
        if (current_node->value == value)
        {
            // If we are on the first node: reassign first pointer
            if (prev_node == nullptr)
            {
                first = current_node->next;
            }
            // If we are somewhere in the middle
            else
            {
                prev_node->next = current_node->next;
            }
            delete current_node;
            return;
        }

        prev_node = current_node;
        current_node = current_node->next;
    }
    throw logic_error("Couldnt find node to delete");
}

// Helper functions
bool List::is_empty() const { return first == nullptr; }

int List::size() const
{
    if (is_empty())
        return 0;

    int count = {1};
    Node *current_node {first};
    while (current_node->next != nullptr)
    {
        current_node = current_node->next;
        count++;
    }
    return count;
}

List::Node *List::find_node_at(int index) const
{
    if(index >= size())
    {
        throw logic_error("Invalid index: index out of range");
    }

    int count {0};
    Node *current_node {first};
    while (count < index && current_node != nullptr)
    {
        current_node = current_node->next;
        count++;
    }

    return current_node;
}

int List::find(int value) const
{
    if(is_empty())
    {
        throw logic_error("The list is empty, cant find anything");
    }

    int index {0};
    Node *current_node {first};
    while (current_node != nullptr && current_node->value != value)
    {
        current_node = current_node->next;
        index++;
    }

    if (current_node == nullptr)
    {
        throw logic_error("Couldnt find the value");
    }
    return index;
}

int List::find_at(int index) const
{
    return (find_node_at(index))->value;
}

string List::to_string() const
{
    if (first == nullptr)
    {
        return "";
    }

    stringstream stream{};
    Node *current_node {first};
    while (current_node->next != nullptr)
    {
        stream << current_node->value << " -> ";
        current_node = current_node->next;
    }
    stream << current_node->value;
    return stream.str();
}

std::ostream &operator<<(std::ostream &os, List const &list)
{
    os << list.to_string();
    return os;
}