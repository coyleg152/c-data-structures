// File: hashmap.c
// Include this file *after* including <stdlib.h>
typedef struct
{
  char ** hash_keys;
  int * values;
  int arr_length;
  int str_length;
  int free_slots;
}
hashmap;

int hm_hash(hashmap * map, char * str);
int hm_strcmp(char * str1, char * str2);
void hm_strcpy(char * ref, char * dest);

// Core functions

hashmap * hm_new(int arr_size, int str_size)
{
  hashmap * map = malloc(sizeof(hashmap));
  map->hash_keys = calloc(arr_size, sizeof(char *));
  map->values = malloc(arr_size * sizeof(int));
  map->arr_length = arr_size;
  map->str_length = str_size;
  map->free_slots = arr_size;
  return map;
}

void hm_free(hashmap * map)
{
  if (map == NULL) return;
  for (int i = 0; i < map->arr_length; i++)
  {
    if (map->hash_keys[i] != NULL) free(map->hash_keys[i]);
  }
  free(map->hash_keys);
  free(map->values);
  free(map);
}

int hm_insert(hashmap * map, char * str, int val)
{
  if (map->free_slots < 1) return -1;
  int hash = hm_hash(map, str);
  if (hash < 0) return -1;
  while (map->hash_keys[hash] != NULL)
  {
    if (hm_strcmp(str, map->hash_keys[hash]) == 0) break;
    hash += 1;
    if (hash == map->arr_length) hash = 0;
  }
  if (map->hash_keys[hash] == NULL)
  {
    map->hash_keys[hash] = malloc(map->str_length * sizeof(char));
    hm_strcpy(str, map->hash_keys[hash]);
    map->free_slots -= 1;
  }
  map->values[hash] = val;
  return 0;
}

int * hm_find(hashmap * map, char * str)
{
  int hash = hm_hash(map, str);
  if (hash < 0) return NULL;
  while (map->hash_keys[hash] != NULL)
  {
    if (hm_strcmp(str, map->hash_keys[hash]) == 0) break;
    hash++;
    if (hash == map->arr_length) hash = 0;
  }
  if (map->hash_keys[hash] == NULL) return NULL;
  return map->values + hash;
}

// Helper functions

int hm_hash(hashmap * map, char * str)
{
  int hash = 0;
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (i >= map->str_length) return -1;
    hash += (int) str[i];
  }
  hash %= map->arr_length;
  return hash;
}

int hm_strcmp(char * str1, char * str2)
{
  if (str1 == NULL || str2 == NULL)
  {
    if (str1 != NULL) return -1;
    if (str2 != NULL) return 1;
    return 0;
  }
  int i;
  for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++)
  {
    if (str1[i] > str2[i]) return -1;
    if (str1[i] < str2[i]) return 1;
  }
  if (str1[i] != '\0') return -1;
  if (str2[i] != '\0') return 1;
  return 0;
}

void hm_strcpy(char * ref, char * dest)
{
  int i;
  for (i = 0; ref[i] != '\0'; i++) dest[i] = ref[i];
  dest[i] = '\0';
}
