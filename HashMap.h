#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdexcept>

template<typename K, typename V>
class MapNode {
  public:
    static MapNode<K, V> *cloneMap(MapNode<K, V> *);
    static MapNode<K, V> *endOfMap(MapNode<K, V> *);
    static void clearMap(MapNode<K, V> *&);
    explicit MapNode(const K &, const V &, MapNode<K, V> * = nullptr);
    K key;
    V value;
    MapNode *next;
};

template<typename K, typename V, typename H = Hash<K>>
class HashMap {
  public:
    static const unsigned int TABLE_SIZE = 1000;
    HashMap();
    HashMap(const HashMap<K, V, H> &);
    ~HashMap();
    const V& get(const K &) const;
    V& get(const K &);
    V& operator[](const K &);
    bool isEmpty() const;
    void clear();
  private:
    MapNode<K, V> **table;
    H hasher;
    MapNode<K, V> *findNode(const K&) const;
    MapNode<K, V> *createNode(const K&, const V& = V());
};

template<typename K, typename V>
MapNode<K, V> *MapNode<K, V>::cloneMap(MapNode<K, V> *n) {
  if (n == nullptr) return nullptr;
  return new MapNode<K, V>(n->key, n->value, cloneMap(n->next));
}

template<typename K, typename V>
MapNode<K, V> *MapNode<K, V>::endOfMap(MapNode<K, V> *n) {
  if (n == nullptr) return nullptr;
  if (n->next == nullptr) return n;
  return endOfMap(n->next);
}

template<typename K, typename V>
void MapNode<K, V>::clearMap(MapNode<K, V> *&n) {
  if (n == nullptr) return;
  clearMap(n->next);
  delete n;
  n = nullptr;
}

template<typename K, typename V>
MapNode<K, V>::MapNode(const K &keyRef, const V &valRef, MapNode<K, V> *next) {
  this->key = keyRef;
  this->value = valRef;
  this->next = next;
}

template<typename K, typename V, typename H>
HashMap<K, V, H>::HashMap() {
  table = new MapNode<K, V> *[TABLE_SIZE]();
}

template<typename K, typename V, typename H>
HashMap<K, V, H>::HashMap(const HashMap<K, V, H> &m) {
  table = new MapNode<K, V> *[TABLE_SIZE]();
  for (unsigned int i = 0; i < TABLE_SIZE; i++) {
    table[i] = MapNode<K, V>::cloneMap(m.table[i]);
  }
}

template<typename K, typename V, typename H>
HashMap<K, V, H>::~HashMap() {
  clear();
}

template<typename K, typename V, typename H>
MapNode<K, V> *HashMap<K, V, H>::findNode(const K &key) const {
  unsigned long hashValue = hasher(key) % TABLE_SIZE;
  MapNode<K, V> *entry = table[hashValue];
  while (entry != nullptr) {
    if (entry->key == key) {
      return entry;
    } else {
      entry = entry->next;
    }
  }
  return nullptr;
}

template<typename K, typename V, typename H>
MapNode<K, V> *HashMap<K, V, H>::createNode(const K& key, const V& val) {
  unsigned long hashValue = hasher(key) % TABLE_SIZE;
  table[hashValue] = new MapNode<K, V>(key, val, table[hashValue]);
  return table[hashValue];
}

template<typename K, typename V, typename H>
const V& HashMap<K, V, H>::get(const K &key) const {
  MapNode<K, V> *n = findNode(key);
  if (n == nullptr) throw new std::out_of_range("missing element");
  return n->value;
}

template<typename K, typename V, typename H>
V& HashMap<K, V, H>::get(const K &key) {
  MapNode<K, V> *n = findNode(key);
  if (n == nullptr) throw new std::out_of_range("missing element");
  return n->value;
}

template<typename K, typename V, typename H>
V& HashMap<K, V, H>::operator[](const K &key) {
  MapNode<K, V> *n = findNode(key);
  if (n == nullptr) n = createNode(key);
  return n->value;
}

template<typename K, typename V, typename H>
bool HashMap<K, V, H>::isEmpty() const {
  for (unsigned int i = 0; i < TABLE_SIZE; i++) {
    if (table[i] != nullptr) return false;
  }
  return true;
}

template<typename K, typename V, typename H>
void HashMap<K, V, H>::clear() {
  for (unsigned int i = 0; i < TABLE_SIZE; i++) {
    MapNode<K, V>::clearMap(table[i]);
  }
}

#endif

