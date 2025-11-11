#include <iostream>
#include <vector>
#include <stdexcept>
#include "list.h"

using namespace std;

List::List() : first(nullptr)
{
}

// Kopieringskonstruktor
List::List(List const &other)
{
    vector<int> values = other.get_values_vector();
    
    Node* first_node = new List::Node{values[0], nullptr};
    Node* previous_node = first_node;
    this->first = first_node;

    for (long unsigned int i = 1; i < values.size(); i++)
    {
    List::Node *new_node = new List::Node{values[i], nullptr};
    previous_node->next = new_node;
    }
}

// Kopieringstilldelningsoperator
List &List::operator=(List const &rhs)
{
    List tmp {rhs};
    this->first = tmp.first;

    return *this; 
}

// Destruktor
List::~List()
{
    Node* current_node = this->first;
    while (current_node->next != nullptr)
    {
        Node* next = current_node->next;
        delete current_node;
        current_node = next;
    }
}

// Flyttkonstruktor
List::List(List &&other)
{
    this->first = other.first;
    other.first = nullptr;
}

// Flytttilldelingsoperator
List &List::operator=(List &&rhs)
{
}

void List::insert(int value, List::Node *current_node)
{
    // If trying to insert into a new list: Create it
    if (this->first == nullptr)
    {
        List::Node *new_node = new List::Node{value, nullptr};
        this->first = new_node;
        return;
    }

    // If its the first round of recursion
    if (current_node == nullptr)
    {
        current_node = this->first;

        // Check if the first item is smaller than new_node: insert new_node on the first place
        if (current_node->value > value)
        {
            List::Node *new_node = new List::Node{value, this->first};
            this->first = new_node;
            return;
        }
    }

    // If current_node is the last item: Make our item last (with an edgecase)
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
    }

    // If next node is still smaller: Move on one step
    else
    {
        List::insert(value, current_node->next);
    }
}

void List::remove(int search, bool search_by_value)
{
    int index = {};
    if (search_by_value)
    {
        index = this->find(search);
    }
    else
    {
        index = search;
    }

    List::Node *node_to_delete = this->find_node_at(index);

    // If the item to remove is the only one: clear list
    if (index == 0 && this->size() == 1)
    {
        delete node_to_delete;
        this->first = nullptr;
    }

    // If the item to remove is in the beggining: reassign first pointer
    else if (index == 0)
    {
        List::Node *next_node = this->find_node_at(index + 1);
        delete node_to_delete;
        this->first = next_node;
    }

    // If the item to remove is at the end: set pointer before it to nullptr
    else if (this->size() == index + 1)
    {
        List::Node *prev_node = this->find_node_at(index - 1);
        delete node_to_delete;
        prev_node->next = nullptr;
    }

    // If the item to remove is somewhere in the middle: pointer before it to item after it
    else
    {
        List::Node *prev_node = this->find_node_at(index - 1);
        List::Node *next_node = this->find_node_at(index + 1);
        delete node_to_delete;
        prev_node->next = next_node;
    }
}

// Helper functions
bool List::is_empty() const
{
    return this->first == nullptr;
}

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
    int count = 0;
    List::Node *current_node = this->first;
    while (count < index && current_node->next != nullptr)
    {
        current_node = current_node->next;
        count++;
    }

    if (current_node->next == nullptr && count < index)
    {
        throw logic_error("Invazlid index: index out of range");
    }
    return current_node;
}

List::Node *List::get_last_node() const
{
    return this->find_node_at(this->size() - 1);
}

int List::find(int value) const
{
    int index = {0};
    List::Node *current_node = this->first;
    while (current_node->value != value && current_node->next != nullptr)
    {
        current_node = current_node->next;
        index++;
    }

    if (current_node->next == nullptr && current_node->value != value)
    {
        throw logic_error("Couldnt find the value");
    }
    return index;
}

int List::find_at(int index) const
{
    return (this->find_node_at(index))->value;
}

int List::get_last() const
{
    return (this->get_last_node())->value;
}

vector<int> List::get_values_vector() const
{
    if (this->first == nullptr)
    {
        vector<int> empty_vector = {};
        return empty_vector;
    }

    List::Node *current_node = this->first;
    vector<int> values = {current_node->value};

    while (current_node->next != nullptr)
    {
        current_node = current_node->next;
        values.push_back(current_node->value);
    }
    return values;
}

std::ostream &operator<<(std::ostream &os, List const &list)
{
    vector<int> values = list.get_values_vector();
    for (long unsigned int i = 0; i < values.size(); i++)
    {
        if (i != values.size() - 1)
        {
            os << values[i] << " -> ";
        }
        else
        {
            os << values[i];
        }
    }
    return os;
}
