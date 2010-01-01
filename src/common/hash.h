#ifndef _HASH_H_
#define _HASH_H_

#define HASH_SIZE 128
struct gobject_t;
/*typedef struct gobject_t gobject;*/

typedef struct key_val_node_s {
  struct gobject_t *key;
  struct gobject_t *val;
  struct key_val_node_s *next;
} key_val_node;

typedef struct hash_entry_s {
  struct gobject_t *key;
  struct gobject_t *value;
  struct hash_entry_s *next;
} hash_entry;

typedef struct hashtable_s {
  hash_entry **entries;
} hashtable;

/** functions **/

key_val_node* key_val_obj(struct gobject_t *key, struct gobject_t *val, key_val_node *next);

hashtable* new_hash(key_val_node *key_val_list);
hash_entry* new_hash_entry(struct gobject_t *key, struct gobject_t *value);

unsigned int hash_val(struct gobject_t *key);
bool hash_add(hashtable *ht, struct gobject_t *key, struct gobject_t *value);
hash_entry* hash_lookup(hashtable *ht, struct gobject_t *key);
bool hash_includes(hashtable *ht, struct gobject_t *key);
bool hash_remove(hashtable *ht, struct gobject_t *key);
bool hash_equals(hashtable *a, hashtable *b);
bool hash_entries_equal(hash_entry *a, hash_entry *b);

#endif /* _HASH_H_ */
