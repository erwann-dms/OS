// kernel/kheap.h
#ifndef KHEAP_H
#define KHEAP_H

void *kmalloc(size_t size);
void kfree(void *ptr);
void heap_init();

#endif