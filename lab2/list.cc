#include "list.h"
#include <sstream>
#include <stdexcept>

using namespace std;

List::List() : first(nullptr) {}

// Kopieringskonstruktor
List::List(List const &other)
{
    if (other.is_empty())
    {
        return;
    }

    Node *first_node = new List::Node{other.first->value, nullptr};
    this->first = first_node;

    Node *previous_node = first_node;
    Node *current_other = other.first->next;
    while (current_other != nullptr)
    {
        List::Node *new_node = new List::Node{current_other->value, nullptr};
        previous_node->next = new_node;

        previous_node = new_node;
        current_other = current_other->next; 
    }
}

// Kopieringstilldelningsoperator
List &List::operator=(List const &rhs)
{
    List tmp{rhs};
    swap(this->first, tmp.first);

    return *this;
}

// Destruktor
List::~List()
{
    if (this->is_empty())
    {
        return;
    }

    Node *current_node = this->first;
    while (current_node != nullptr)
    {
        Node *next = current_node->next;
        delete current_node;
        current_node = next;
    }
    this->first = nullptr;
}

// Flyttkonstruktor
List::List(List &&other)
{
    // Swap lists, so that this receives the wanted other.first
    // While other gets the unwanted old list (if not nullptr)
    // and we dont need to deal with it because it will destructure on
    // out-of-scope
    swap(this->first, other.first);
}

// Flytttilldelingsoperator
List &List::operator=(List &&rhs)
{
    swap(this->first, rhs.first);
    return *this;
}

void List::insert(int value, List::Node *current_node)
{
    // If trying to insert into a new list: Create it
    if (this->is_empty())
    {
        List::Node *new_node = new List::Node{value, nullptr};
        this->first = new_node;
        return;
    }

    // If its the first round of recursion
    if (current_node == nullptr)
    {
        current_node = this->first;

        // Check if the first item is smaller than new_node: insert new_node on the
        // first place
        if (current_node->value > value)
        {
            List::Node *new_node = new List::Node{value, this->first};
            this->first = new_node;
            return;
        }
    }

    // If current_node is the last item: Make our item last
    if (current_node->next == nullptr)
    {
        List::Node *new_node = new List::Node{value, nullptr};
        current_node->next = new_node;
        return;
    }

    // If next node is bigger: Insert new node between it
    if (current_node->next->value > value)
    {
        List::Node *new_node = new List::Node{value, current_node->next};
        current_node->next = new_node;
        return;
    }

    List::insert(value, current_node->next);
}

void List::remove(int value)
{
    if (this->is_empty())
    {
        throw logic_error("Trying to remove a value from an empty list");
        return;
    }

    List::Node *prev_node = nullptr;
    List::Node *current_node = this->first;
    while (current_node != nullptr)
    {
        // If we found the node to delete:
        if (current_node->value == value)
        {
            // If we are on the first node: reassign first pointer
            if (prev_node == nullptr)
            {
                this->first = current_node->next;
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
bool List::is_empty() const { return this->first == nullptr; }

int List::size() const
{
    if (this->is_empty())
        return 0;

    int count = {1};
    List::Node *current_node = this->first;
    while (current_node->next != nullptr)
    {
        current_node = current_node->next;
        count++;
    }
    return count;
}

List::Node *List::find_node_at(int index) const
{
    if(index >= this->size())
    {
        throw logic_error("Invalid index: index out of range");
    }

    int count = 0;
    List::Node *current_node = this->first;
    while (count < index && current_node != nullptr)
    {
        current_node = current_node->next;
        count++;
    }

    return current_node;
}

int List::find(int value) const
{
    if(this->is_empty())
    {
        throw logic_error("The list is empty, cant find anything");
    }

    int index = {0};
    List::Node *current_node = this->first;
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
    return (this->find_node_at(index))->value;
}

string List::to_string() const
{
    if (this->first == nullptr)
    {
        return "";
    }

    stringstream stream{};
    List::Node *current_node = this->first;
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