#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

template<typename Type>
struct Node
{
  Type        data;
  Node<Type>* next;

  explicit Node(const Type& v):
    data(v),
    next(nullptr)
  { }
};

template<typename Type>
struct List
{
  Node<Type>* first;
  Node<Type>* last;
  size_t      lsize;

  List():
    first(nullptr),
    last(nullptr),
    lsize(0)
  { }

  ~List()
  {
    Node<Type>* node = first;
    while (node)
    {
      Node<Type>* todelete = node;
      node = node->next;
      delete todelete;
    }
  }

  void Add(const Type& v)
  {
    Node<Type>* node = new Node<Type>(v);

    if (first)
    {
      last->next = node;
    }
    else
    {
      first = node;
    }
    last = node;
    ++lsize;
  }

  size_t Size() const
  {
    return lsize;
  }

  void Trace() const
  {
    for (auto node = first; node; node = node->next)
    {
      cout << "trace item=" << node->data << endl;
    }
  }

  class iterator : public std::iterator<forward_iterator_tag, Type>
  {
    
  private:
    
    Node<Type>* curr_node;

  public:
    
    explicit iterator(Node<Type>* node):
      curr_node(node)
    { }
    
    ~iterator()
    { }

    iterator& operator=(const iterator& other)
    {
      if (&other == this)
      {
        return *this;
      }
      curr_node = other.curr_node;
    }

    bool operator==(const iterator& other)
    {
      return curr_node == other.curr_node;
    }

    bool operator!=(const iterator& other)
    {
      return curr_node != other.curr_node;
    }

    iterator& operator++()
    {
      if (curr_node)
      {
        curr_node = curr_node->next;
      }
      return *this;
    }

    iterator& operator++(int)
    {
      if (curr_node)
      {
        curr_node = curr_node->next;
      }
      return *this;
    }

    Type& operator*()
    {
      return curr_node->data;
    }

    Type* operator->()
    {
      return &(curr_node->data);
    }
  };

  iterator begin()
  {
    return iterator(first);
  }
  iterator end()
  {
    return iterator(nullptr);
  }
  
};

struct Entry
{
  int a;
  int b;
  int c;

  friend ostream& operator<<(ostream& os, const Entry& e)
  {
    os << "a="  << e.a
       << ",b=" << e.b
       << ",c=" << e.c;
    return os;
  }  
};


int main()
{
  List<Entry> l;

  l.Add({1,2,3});
  l.Add({4,5,6});
  l.Add({7,8,9});

  cout << "list size is " << l.Size() << endl;
  l.Trace();

  for (const auto& i : l)
  {
    cout << "range item=" << i << endl;
  }

  for (auto it = l.begin(); it != l.end(); ++it)
  {
    cout << "iterator ref item=" << *it << endl;
    cout << "iterator ptr item(a)=" << it->a << endl;
  }

  for_each(l.begin(), l.end(),
           [](const Entry& i)
           {
             cout << "for_each=" << i << endl;
           });
  
  return 0;
}
