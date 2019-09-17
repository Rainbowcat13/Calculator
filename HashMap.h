#ifndef HASHMAP_H
#define HASHMAP_H

const unsigned int MAP_TABLE_SIZE = 1000;

template<typename K>
struct KeyHash {
  unsigned long operator()(const K& key);
};

#ifdef STRING_H
template<>
struct KeyHash<String> {
  unsigned long operator()(const String &key);
};
#endif

template<typename K, typename V>
class HashNode {
  public:
    HashNode(K key, V value, HashNode *next = nullptr) : key(key), value(value), next(next) {}
    K key;
    V value;
    HashNode *next;
};

template<typename K, typename V>
HashNode<K, V> *cloneNodes(HashNode<K, V> *n) {
  if (n == nullptr) return nullptr;
  return new HashNode<K, V>(n->key, n->value, clone(n->next));
}

template<typename K, typename V>
void clearNodes(HashNode<K, V> *n) {
  if (n == nullptr) return;
  clearNodes(n->next);
  delete n;
}

template<typename K, typename V, typename H = KeyHash<K>>
class HashMap {
  public:
    HashMap();
    HashMap(const HashMap<K, V, H> &);
    V& operator[](const K &);
    bool isEmpty();
    void clear();
  private:
    HashNode<K, V> **table;
    H hashFunction;
};

template<typename K>
unsigned long KeyHash<K>::operator()(const K& key) {
  return static_cast<unsigned long>(key) % MAP_TABLE_SIZE;
}

#ifdef STRING_H
unsigned long KeyHash<String>::operator()(const String &s) {
  const int p = 31;
  long long hashValue = 0, pow = 1;
  for (unsigned int i = 0; i < s.size(); i++) {
    hashValue = (hashValue + s[i] * pow) % MAP_TABLE_SIZE;
    pow = (pow * p) % MAP_TABLE_SIZE;
  }
  return hashValue;
}
#endif

template<typename K, typename V, typename H>
HashMap<K, V, H>::HashMap() {
  table = new HashNode<K, V> *[MAP_TABLE_SIZE]();
}

template<typename K, typename V, typename H>
HashMap<K, V, H>::HashMap(const HashMap<K, V, H> &m) {
  table = new HashNode<K, V> *[MAP_TABLE_SIZE]();
  for (unsigned int i = 0; i < MAP_TABLE_SIZE; i++) {
    table[i] = cloneNodes(m.table[i]);
  }
}

template<typename K, typename V, typename H>
V& HashMap<K, V, H>::operator[](const K &key) {
  unsigned long hashValue = hashFunction(key);
  HashNode<K, V> *entry = table[hashValue];
  while (entry != nullptr) {
    if (entry->key == key) {
      return entry->value;
    } else {
      entry = entry->next;
    }
  }
  entry = new HashNode<K, V>(key, V(), table[hashValue]);
  table[hashValue] = entry;
  return entry->value;
}

template<typename K, typename V, typename H>
bool HashMap<K, V, H>::isEmpty() {
  for (unsigned int i = 0; i < MAP_TABLE_SIZE; i++) {
    if (table[i] != nullptr) return false;
  }
  return true;
}

template<typename K, typename V, typename H>
void HashMap<K, V, H>::clear() {
  for (unsigned int i = 0; i < MAP_TABLE_SIZE; i++) {
    clearNodes(table[i]);
    table[i] = nullptr;
  }
}

#endif

