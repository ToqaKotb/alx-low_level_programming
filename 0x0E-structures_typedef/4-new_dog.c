#include <stdlib.h>
#include "dog.h"

/**
 * _strlen - returns the length of a string
 * @s: string to evaluate
 * Return: the length of the string
 * *_strcpy - copies the string pointed to by src
 * including the terminating null byte (\0)
 * to the buffer pointed to by dest
 * @dest: pointer to the buffer in which we copy the string
 * @src: string to be copied
 * Return: the pointer to dest
 * new_dog - creates a new dog
 * @name: name of the dog
 * @age: age of the dog
 * @owner: owner of the dog
 * Return: pointer to the new dog (Success), NULL otherwise
 */
dog_t *new_dog(char *name, float age, char *owner)
{
    dog_t *dog = malloc(sizeof(dog_t));
    if (dog == NULL)
        return NULL;

    dog->name = malloc(_strlen(name) + 1);
    if (dog->name == NULL)
    {
        free(dog);
        return NULL;
    }
    _strcpy(dog->name, name);

    dog->owner = malloc(_strlen(owner) + 1);
    if (dog->owner == NULL)
    {
        free(dog->name);
        free(dog);
        return NULL;
    }
    _strcpy(dog->owner, owner);

    dog->age = age;

    return dog;
}
