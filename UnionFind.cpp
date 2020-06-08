#include "UnionFind.h"
#include <iostream>

using namespace std;

void UnionFind::connect(ActorNode* actorA, ActorNode* actorB){
	if (find(actorA) != find(actorB)){
		find(actorB)->prev = find(actorA);
	}
}

ActorNode* UnionFind::find(ActorNode* actor_find){
	if (actor_find->prev != nullptr){
		return find(actor_find->prev);
	}
	return actor_find;
}
