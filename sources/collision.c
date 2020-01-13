#include "collision.h"
#include <stdio.h>

struct collision_object{
    int (*getX)(struct collision_object*);
    int (*getY)(struct collision_object*);
    int (*getWidth)(struct collision_object*);
    int (*getHeight)(struct collision_object*);
};

int check_collision(struct collision_object *obj1, struct collision_object *obj2)
{
	if (obj1->getX(obj1) < obj2->getX(obj2) + obj2->getWidth(obj2) 
		&& obj1->getX(obj1) + obj1->getWidth(obj1) > obj2->getX(obj2)
		&& obj1->getY(obj1) < obj2->getY(obj2) + obj2->getHeight(obj2) 
		&& obj1->getY(obj1) + obj1->getHeight(obj1) > obj2->getY(obj2)
		)
		return 1;
	
	return 0;
}

