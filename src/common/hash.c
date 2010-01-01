#include "includes.h"

key_val_node* key_val_obj(gobject *key, gobject *val, key_val_node *next)
{
  key_val_node *node = malloc(sizeof(key_val_node));

  assert(node);

  node->key = key;
  node->val = val;
  node->next = next;
  return node;
}

hashtable* new_hash(key_val_node *key_val_list)
{
  hashtable *ht = malloc(sizeof(hashtable));
  ht->entries = malloc(HASH_SIZE * sizeof(hash_entry));

  assert(ht);
  assert(ht->entries);

  return ht;
}

hash_entry* new_hash_entry(gobject *key, gobject *value)
{
  if(key && value) {
    hash_entry *entry = malloc(sizeof(hash_entry));
    assert(entry);
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    return entry;
  } else {
    return NULL;
  }
}

unsigned int hash_val(gobject *key)
{
  unsigned int hashval;
  char *str;
  
  switch(key->type) {
  case OBJ_NIL: return 0;
  case OBJ_T: return 0;
  case OBJ_INTEGER: 
    hashval = key->value.intval;
    break;
  case OBJ_DOUBLE:
    hashval = (unsigned int)key->value.doubleval;
    break;
  case OBJ_IDENTIFIER:
    str = key->value.identifier;
    for(hashval = 0; *str != '\0'; str++) {
      hashval = *str + 31 * hashval;      
    }
    break;
  case OBJ_STRING:
    str = key->value.string;
    for(hashval = 0; *str != '\0'; str++) {
      hashval = *str + 31 * hashval;      
    }
    break;
  case OBJ_HASH:
    return 100; /* hash objects always go here */
  case OBJ_CONS:
    return 101; /* cons objects here */
  default:
    return 127; /* default to 127 */
  }
  
  return hashval % HASH_SIZE;
}

bool hash_add(hashtable *ht, gobject *key, gobject *value)
{
  if(ht && key && value) {
    int hashval = hash_val(key);
    hash_entry *first_entry = ht->entries[hashval];
    hash_entry *curr_entry = first_entry;
    hash_entry *last_entry = curr_entry;

    if(first_entry) {
      /* 
         find entry with same key. if none found, add new entry at end
         of entry list for given hashval
      */
      for(; curr_entry; curr_entry = curr_entry->next) {
        last_entry = curr_entry;

        /* TODO: make this something like: if(obj_equals(key, curr_entry->key) */
        if(key == curr_entry->key) {
          curr_entry->value = value;
          return false;
        }
      }
      
      /* none found -> add after last_entry */
      last_entry->next = new_hash_entry(key, value);
      return true;
    } else {
      /* no entries for hashval available yet -> add new one */
      first_entry = new_hash_entry(key, value);
      ht->entries[hashval] = first_entry;
      return true;
    }
  } else {
    return false;
  }
}

hash_entry* hash_lookup(hashtable *ht, gobject *key)
{
  unsigned int hashval;
  hash_entry *current;

  assert(ht);
  assert(key);
  hashval = hash_val(key);

  for(current = ht->entries[hashval]; 
      current; current = current->next) {
    /* TODO: make this something like: if(obj_equals(key, current->key) */
    if(key == current->key) {
      return current;
    }
  }

  return NULL;
}

bool hash_includes(hashtable *ht, gobject *value)
{
  return (hash_lookup(ht, value) != NULL);
}

bool hash_remove(hashtable *ht, gobject *key)
{
  unsigned int hashval = hash_val(key);
  hash_entry *current, *last;
  current = ht->entries[hashval];
  last = current;
  for(; current; current = current->next) {
    /* TODO: make this something like: if(obj_equals(key, current->key) */
    if(key == current->key) {
      last->next = current->next;
      free(current);
      return true;
    }
    last = current;
  }
  
  return false; 
}

bool hash_equals(hashtable *a, hashtable *b)
{
  unsigned int i;

  if(a && b) {

    for(i = 0; i < HASH_SIZE; i++) {
      if(!hash_entries_equal(a->entries[i], b->entries[i])) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}

bool hash_entries_equal(hash_entry *a, hash_entry *b)
{
  hash_entry *tmp_a, *tmp_b;

  if(a && b) {

    tmp_a = a;
    tmp_b = b;

    while(tmp_a && tmp_b) {
      if(obj_equals(tmp_a->key, tmp_b->key) != t
         || obj_equals(tmp_a->value, tmp_b->value) != t) {
        return false;
      }
      tmp_a = tmp_a->next;
      tmp_b = tmp_b->next;
    }

    /* one list has ended before the other one -> false */
    if(!(tmp_a->next && tmp_b->next))
      return false;

    /* otherwise, we should have the same lists */
    return true;
  } else {
    if(!a && !b)
      return true;

    return false;
  }
}
