#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
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

public:
    List();

    //Kopieringskonstruktor 
    List(List const& other);

    //Kopieringstilldelningsoperator
    List& operator=(List const& rhs);

    //Destruktor 
    ~List();

    //Flyttkonstruktor
    List(List && other);

    //Flytttilldelingsoperator
    List& operator=(List && rhs);

    void insert(int value, List::Node *current_node = nullptr);
    void remove(int value);


    // Helper functions
    bool is_empty() const;
    int size() const;

    std::string to_string() const;
    int find_at(int index) const;
    int find(int value) const;
};

std::ostream &operator<<(std::ostream& os, List const &list);

#endif