#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>

class List
{
public:
    List();

    // Kopieringskonstruktor
    List(List const &other);

    // Kopieringstilldelningsoperator
    List &operator=(List const &rhs);

    // Destruktor
    ~List();

    // Flyttkonstruktor
    List(List &&other);

    // Flytttilldelingsoperator
    List &operator=(List &&rhs);

    void insert(int value);
    void remove(int value);

    // Helper functions
    bool is_empty() const;
    int size() const;

    std::string to_string() const;
    int find_at(int index) const;
    int find(int value) const;

private:
    struct Node
    {
        int value;
        Node *next;
    };

    Node *first{};

    void insert(int value, Node *current_node);
    Node *find_node_at(int index) const;
};

std::ostream &operator<<(std::ostream &os, List const &list);

#endif