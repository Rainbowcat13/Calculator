#ifndef HASHMAP_H
#define HASHMAP_H

#include "Hash.h"
#include "List.h"
#include <stdexcept>

template <typename K, typename V> struct MapNode {
  static MapNode<K, V> *cloneMap(MapNode<K, V> *);
  static void clearMap(MapNode<K, V> *&);
  explicit MapNode(const K &, const V &, MapNode<K, V> * = nullptr);
  K key;
  V value;
  MapNode *next;
};

template <typename K, typename V, typename H = Hash<K>> class HashMap {
public:
  static const unsigned int TableSize = 1000;
  HashMap();
  HashMap(const HashMap<K, V, H> &);
  ~HashMap();
  List<K> keys() const;
  List<V> values() const;
  V remove(const K &);
  void clear();
  bool contains(const K &) const;
  unsigned int size() const;
  bool isEmpty() const;
  HashMap<K, V, H> &operator=(const HashMap<K, V, H> &);
  V &operator[](const K &);
  const V &operator[](const K &) const;

private:
  MapNode<K, V> **table;
  H hasher;
  unsigned int count;
  MapNode<K, V> *findNode(const K &) const;
  MapNode<K, V> *takeNode(const K &);
  MapNode<K, V> *insertNode(const K &, const V & = V());
};

template <typename K, typename V>
MapNode<K, V> *MapNode<K, V>::cloneMap(MapNode<K, V> *n) {
  if (n == nullptr)
    return nullptr;
  return new MapNode<K, V>(n->key, n->value, cloneMap(n->next));
}

template <typename K, typename V>
void MapNode<K, V>::clearMap(MapNode<K, V> *&n) {
  if (n == nullptr)
    return;
  clearMap(n->next);
  delete n;
  n = nullptr;
}

template <typename K, typename V>
MapNode<K, V>::MapNode(const K &keyRef, const V &valRef,
                       MapNode<K, V> *nextPtr) {
  key = keyRef;
  value = valRef;
  next = nextPtr;
}

template <typename K, typename V, typename H> HashMap<K, V, H>::HashMap() {
  table = new MapNode<K, V> *[TableSize]();
  count = 0;
}

template <typename K, typename V, typename H>
HashMap<K, V, H>::HashMap(const HashMap<K, V, H> &m) {
  table = new MapNode<K, V> *[TableSize]();
  count = m.count;
  for (unsigned int i = 0; i < TableSize; i++) {
    table[i] = MapNode<K, V>::cloneMap(m.table[i]);
  }
}

template <typename K, typename V, typename H> HashMap<K, V, H>::~HashMap() {
  clear();
  delete[] table;
}

template <typename K, typename V, typename H>
List<K> HashMap<K, V, H>::keys() const {
  List<K> res;
  for (unsigned int i = 0; i < TableSize; i++) {
    MapNode<K, V> *n = table[i];
    while (n != nullptr) {
      res.insert(n->key, 0);
      n = n->next;
    }
  }
  return res;
}

template <typename K, typename V, typename H>
List<V> HashMap<K, V, H>::values() const {
  List<V> res;
  for (unsigned int i = 0; i < TableSize; i++) {
    MapNode<K, V> *n = table[i];
    while (n != nullptr) {
      res.insert(n->value, 0);
      n = n->next;
    }
  }
  return res;
}

template <typename K, typename V, typename H> V remove(const K &k) {
  MapNode<K, V> *n = takeNode(k);
  if (n == nullptr)
    throw std::out_of_range("missing element");
  V res = n->value;
  delete n;
  return res;
}

template <typename K, typename V, typename H> void HashMap<K, V, H>::clear() {
  for (unsigned int i = 0; i < TableSize; i++) {
    MapNode<K, V>::clearMap(table[i]);
  }
  count = 0;
}

template <typename K, typename V, typename H>
bool HashMap<K, V, H>::contains(const K &k) const {
  return findNode(k) != nullptr;
}

template <typename K, typename V, typename H>
unsigned int HashMap<K, V, H>::size() const {
  return count;
}

template <typename K, typename V, typename H>
bool HashMap<K, V, H>::isEmpty() const {
  return count == 0;
}

template <typename K, typename V, typename H>
HashMap<K, V, H> &HashMap<K, V, H>::operator=(const HashMap<K, V, H> &o) {
  for (unsigned int i = 0; i < TableSize; i++) {
    delete[] table[i];
    table[i] = MapNode<K, V>::cloneMap(o.table[i]);
  }
  count = o.count;
  return *this;
}

template <typename K, typename V, typename H>
const V &HashMap<K, V, H>::operator[](const K &key) const {
  MapNode<K, V> *n = findNode(key);
  if (n == nullptr)
    throw std::out_of_range("missing element");
  return n->value;
}

template <typename K, typename V, typename H>
V &HashMap<K, V, H>::operator[](const K &key) {
  MapNode<K, V> *n = findNode(key);
  if (n == nullptr)
    n = insertNode(key);
  return n->value;
}

template <typename K, typename V, typename H>
MapNode<K, V> *HashMap<K, V, H>::findNode(const K &key) const {
  unsigned long hash = hasher(key) % TableSize;
  MapNode<K, V> *entry = table[hash];
  while (entry != nullptr) {
    if (entry->key == key)
      return entry;
    entry = entry->next;
  }
  return nullptr;
}

template <typename K, typename V, typename H>
MapNode<K, V> *HashMap<K, V, H>::takeNode(const K &key) {
  unsigned long hash = hasher(key) % TableSize;
  MapNode<K, V> *entry = table[hash];
  if (entry == nullptr)
    return nullptr;
  if (entry->key == key) {
    table[hash] = entry->next;
    entry->next = nullptr;
    count--;
    return entry;
  }
  while (entry->next != nullptr) {
    if (entry->next->key == key) {
      MapNode<K, V> *res = entry->next;
      entry->next = entry->next->next;
      res->next = nullptr;
      count--;
      return res;
    }
    entry = entry->next;
  }
  return nullptr;
}

template <typename K, typename V, typename H>
MapNode<K, V> *HashMap<K, V, H>::insertNode(const K &key, const V &val) {
  unsigned long hashValue = hasher(key) % TableSize;
  table[hashValue] = new MapNode<K, V>(key, val, table[hashValue]);
  count++;
  return table[hashValue];
}

#endif
