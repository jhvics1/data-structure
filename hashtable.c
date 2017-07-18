#include "stdio.h"
#include "stdlib.h"

#define MAX_LEN (10000)
#define NULL    (0)

typedef struct table_item {
	unsigned long hash_value;
	struct table_item * next;
} st_table_item;

typedef struct hashtable {
    struct table_item ** items;
	int table_size;
	int item_count;
}st_hashtable;

static struct hashtable * ht = NULL;

unsigned long get_value_hash1(unsigned char* str)
{
	unsigned long hash = 5381;
	int c = 0;

	while( c = *str++)
	{
		hash = (hash * 33) + c;
	}

	return hash;
}

void init_table(int size)
{
	printf(" TABLE SIZE : %d\n", size);
	if(ht)
	{
		for(int index = 0 ; index < ht->table_size ; index++)
		{
			if(ht->items[index] != 0) free(ht->items[index]);
			ht->items[index] = NULL;
		}
		free(ht);
		ht = NULL;
	}

	ht = malloc (sizeof(st_hashtable));
	ht->table_size = (unsigned long)size;
	ht->items = malloc (sizeof (st_table_item) * size);
	for(int index = 0 ; index < ht->table_size ; index++)
	{
		ht->items[index] = NULL;
	}
	ht->item_count = 0;
}

void put_into_table(char* value)
{
	unsigned long hash = get_value_hash1((unsigned char*)value);
	st_table_item * item = ht->items[ hash % ht->table_size ];

	printf("PUT Index : %d \t hash : %u \t value : %s\n", (hash%ht->table_size), hash, value );

	while(item != NULL)
	{
		if(item->hash_value == hash) return;
		item = item->next;
	}

	if( (item = malloc(sizeof(struct table_item)) ) == NULL)
	{
		printf("ERROR~~~~~~~~!!!!\n");
			return;
	}

    item->next = ht->items[ hash % ht->table_size ];
    item->hash_value = hash;
    ht->items[ hash % ht->table_size ] = item;
    ht->item_count++;
}
void delete_from_table(char* value)
{
	if(ht->item_count > 0)
	{
		unsigned long hash = get_value_hash1((unsigned char*)value);
		printf("DEL hash : %u\n", hash);
		struct table_item * item = ht->items[ hash % ht->table_size ];

		struct table_item * prev = NULL;
		while(item != NULL)
		{
			printf("\t item hash : %u\n", item->hash_value);
			if(item->hash_value == hash)
			{
				if(prev == NULL)
				{
					printf("\t\tFirst item in hash array\n");
					ht->items[ hash % ht->table_size ] = item->next;
					free(item);
					ht->item_count--;
				}
				else
				{
					printf("\t\tNot the first item\n");
					prev->next = item->next;
					free(item);
					ht->item_count--;
				}
				return;
			}
			prev = item;
			item = item->next;
		}
	}
}
void print_table()
{
	if(ht->item_count > 0)
	{
		for(int pos = 0 ; pos < ht->table_size ; pos++)
		{
			struct table_item * item = ht->items[ pos ];
			while(item != NULL)
			{
				printf("PRN Index : %d \t hash : %u\n", pos, item->hash_value);
				item = item->next;
			}
		}
	}
}


