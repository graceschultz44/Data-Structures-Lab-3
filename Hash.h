#ifndef HASH_H
#define HASH_H
#include <map>
#include <functional>
#include <ostream>

// Template class for a hash table
template <typename Comparable, typename Value>
class Hash
{
private:
    // Nested struct representing a node in the hash table
    struct HashNode
    {
        Comparable comp;           // Key of the node
        std::map<Value, int> maps; // Map to store values and their counts
        HashNode *next;            // Pointer to the next node in the same bucket

        // Constructor for a node with a key and a value
        HashNode(Comparable c, Value v)
        {
            comp = c;
            maps[v] = 1;
            next = nullptr;
        }

        // Constructor for a node with a key and a map of values
        HashNode(Comparable c, std::map<Value, int> v)
        {
            comp = c;
            maps = v;
            next = nullptr;
        }

        // Copy constructor for a node
        HashNode(const HashNode &n) : comp(n.comp), maps(n.maps), next(nullptr) {}
    };

    int capacity;     // Capacity of the hash table
    int size;         // Current size of the hash table
    HashNode **table; // Pointer to the array of hash buckets

    // Method to resize and rehash the hash table
    void rehash()
    {
        // Logic for rehashing
        int storeCapacity = capacity;
        capacity = capacity * 2;
        HashNode **storeTable = table;
        createHash(capacity);
        for (int i = 0; i < storeCapacity; i++)
        {
            HashNode *itr = storeTable[i];
            while (itr != nullptr)
            {
                secondInsert(itr->comp, itr->maps);
                HashNode *temp = itr;
                itr = itr->next;
                delete temp;
            }
            storeTable[i] = nullptr;
        }
        delete[] storeTable;
    }

    // Hash function to compute the bucket index
    int hash(Comparable comp)
    {
        int index = std::hash<Comparable>{}(comp);
        return abs(index % capacity);
    }

public:
    Hash() : table{nullptr} // default constructor
    {
        createHash();
    }
    ~Hash() // destructor
    {
        clear();
        delete[] table;
    }

    Hash(const Hash &rhs) : table{nullptr} // copy constructor
    {
        clone(rhs);
    }

    Hash &operator=(const Hash &rhs) // assignment operator
    {
        if (this != &rhs)
        {
            clear();
            clone(rhs);
        }
        return *this;
    }

    // Get the current size of the hash table
    int getSize()
    {
        return size;
    }

    void clear() // clears the hash table
    {
        for (int i = 0; i < capacity; i++)
        {
            HashNode *itr = table[i];
            while (itr != nullptr)
            {
                HashNode *prev = itr;
                itr = itr->next;
                delete prev;
            }
            table[i] = nullptr;
        }
        delete[] table;
        createHash(capacity);
        size = 0;
    }

    void createHash(int x = 100) // Create a new hash table with a specified capacity (default is 100)
    {
        capacity = x;
        size = 0;
        table = new HashNode *[capacity];
        for (int i = 0; i < capacity; i++)
        {
            table[i] = nullptr;
        }
    }

    void clone(const Hash &copy) // clones a hash
    {
        createHash(copy.capacity);
        size = copy.size;
        for (int i = 0; i < capacity; i++)
        {
            HashNode *itr1 = copy.table[i];
            HashNode *prev = nullptr;
            while (itr1 != nullptr)
            {
                HashNode *newNode = new HashNode(*itr1);
                if (prev == nullptr)
                {
                    table[i] = newNode;
                }
                else
                {
                    prev->next = newNode;
                }
                prev = newNode;
                itr1 = itr1->next;
            }
        }
    }

    void insert(Comparable comp, Value val) // inserts a comp into a hash at val
    {
        int index = hash(comp);
        if (table[index] == nullptr)
        {
            table[index] = new HashNode(comp, val);
            size++;
        }
        else
        {
            HashNode *itr = table[index];
            HashNode *prev = nullptr;
            while (itr != nullptr)
            {
                if (itr->comp == comp)
                {
                    if (itr->maps.find(val) == itr->maps.end())
                    {
                        itr->maps[val] = 1;
                    }
                    else
                    {
                        itr->maps[val] += 1;
                    }
                    break;
                }
                prev = itr;
                itr = itr->next;
            }
            if (itr == nullptr)
            {
                if (prev != nullptr)
                {
                    prev->next = new HashNode(comp, val);
                    size++;
                }
            }
        }
        if (size == capacity)
        {
            rehash();
        }
    }

    // Insert a key-value pair with a frequency into the hash table
    void insert(Comparable comp, Value val, int freq) // inserts a comp into a hash at val
    {
        int index = hash(comp);
        if (table[index] == nullptr)
        {
            table[index] = new HashNode(comp, val);
            table[index]->maps[val] = freq;
            size++;
        }
        else
        {
            HashNode *itr = table[index];
            HashNode *prev = nullptr;
            while (itr != nullptr)
            {
                if (itr->comp == comp)
                {
                    if (itr->maps.find(val) == itr->maps.end())
                    {
                        itr->maps[val] = freq;
                    }
                    else
                    {
                        itr->maps[val] += freq;
                    }
                    break;
                }
                prev = itr;
                itr = itr->next;
            }
            if (itr == nullptr)
            {
                if (prev != nullptr)
                {
                    prev->next = new HashNode(comp, val);
                    size++;
                }
            }
        }
        if (size == capacity)
        {
            rehash();
        }
    }

    // Print the hash table to an output stream
    void printHash(std::ostream &out)
    {
        for (int i = 0; i < capacity; i++)
        {
            HashNode *itr = table[i];
            while (itr != nullptr)
            {
                out << itr->comp << ":";
                for (const auto &itr : itr->maps)
                {
                    out << itr.first << "," << itr.second << ";";
                }
                out << std::endl;
                itr = itr->next;
            }
        }
    }

    // Insert a key with a map of values into the hash table
    void secondInsert(Comparable comp, std::map<Value, int> val) // inserts a comp into a hash at val
    {
        int index = hash(comp);
        if (table[index] == nullptr)
        {
            table[index] = new HashNode(comp, val);
            size++;
        }
        else
        {
            HashNode *itr = table[index];
            HashNode *prev = nullptr;
            while (itr != nullptr)
            {
                if (itr->comp == comp)
                {
                    for (const auto &entry : val)
                    {
                        itr->maps[entry.first] = entry.second;
                    }
                    break;
                }
                prev = itr;
                itr = itr->next;
            }
            if (itr == nullptr)
            {
                prev->next = new HashNode(comp, val);
                size++;
            }
        }
        if (size == capacity)
        {
            rehash();
        }
    }
    
    // Find and return the map of values for a given key
    std::map<Value, int> find(const Comparable comp) // finds a comp in the hash
    {
        int index = hash(comp);
        HashNode *itr = table[index];
        while (itr != nullptr)
        {
            if (itr->comp == comp)
            {
                return itr->maps;
            }
            itr = itr->next;
        }
        return std::map<Value, int>();
    }
};
#endif
