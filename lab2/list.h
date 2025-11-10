#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <vector>

class List
{
private:
    struct Node
    {
        int value;
        Node *next;
    };

    Node *first{};

    Node *find_node_at(int index) const;
    Node *get_last_node() const;

public:
    List();

    void insert(int value, List::Node *current_node = nullptr);

    void remove(int search, bool search_by_value = true);

    // Helper functions
    bool is_empty() const;
    int size() const;


    int find_at(int index) const;
    int get_last() const;
    int find(int value) const;

    std::vector<int> get_values_vector() const;
};

std::ostream &operator<<(std::ostream& os, List const &list);

#endif