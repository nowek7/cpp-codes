#include <iostream>

// Simply single-forward-list
struct Node
  {
  int theValue = 0;
  Node *theNext = nullptr;

  Node(int aValue): theValue(aValue) {};
  };
Node *node = nullptr;

void push_front(int aValue)
  {
  if (node)
    {
    Node *newNode = new Node(aValue);
    newNode->theNext = node;
    node = newNode;
    }
  else
    node = new Node(aValue);
  }

void pop_front()
  {
  if (node)
    {
    Node *old = node;
    node = old->theNext;

    delete old;
    }
  else
    throw new std::logic_error("Forward list is empty!");
  }

bool empty()
  {
  return node ? true : false;
  }

int front()
  {
  if (node)
    return node->theValue;
  else
    throw std::logic_error("Node is empty!");
  }

int back()
  {
  if (node)
    {
    if (!node->theNext)
      return node->theValue;

    Node *nextNode = node->theNext;
    do
      {
      if (!nextNode->theNext)
        return nextNode->theValue;

      nextNode = nextNode->theNext;
      }
    while (nextNode);
    }
  else
    throw std::logic_error("Node is empty!");
  }

int size()
  {
  auto size = int{0};
  if (node)
    {
    size++;
    Node *next = node->theNext;
    while (next)
      {
      size++;
      next = next->theNext;
      }
    }

  return size;
  }

int main()
  {
  push_front(10);
  push_front(20);
  push_front(40);
  push_front(80);
  pop_front();
  std::cout << empty() << std::endl;
  std::cout << size() << std::endl;

  std::cout << front() << std::endl;
  std::cout << back() << std::endl;
  }