#ifndef INCIDENCES_HPP
#define INCIDENCES_HPP

#include "level/tilemap.hpp"
#include "weather.hpp"
#include "entity/entity_type.hpp"
#include "entity/entity.hpp"
#include <vector>
#include <iostream>

class Entity;

#define ALEATOIRE 3

// --- fonction principale ---
void doIncidences(TileMap* tilemap,Weather* weather, sf::Vector2i posHome);
// ---------------------------

// --- fonctions "privées" ---
void spreadGround(TileMap* tilemap, int type, sf::Vector2i position);

void dilateGround(TileMap* tilemap, TileBehavior behavior);
void erodeGround(TileMap* tilemap, TileBehavior behavior);

void dilateNearGround(TileMap* tilemap, TileBehavior behavior, TileBehavior behaviorNear);
void erodeNearGround(TileMap* tilemap, TileBehavior behavior, TileBehavior behaviorNear);

void dilateElement(TileMap* tilemap, TileBehavior behavior);
void erodeElement(TileMap* tilemap, TileBehavior behavior);

int spawnEntities(EntityType type, std::vector< Entity * > list);
int killEntities(EntityType type, std::vector< Entity * > list);
// ---------------------------

// --- fonctions à utiliser ---
void dilateFluids(TileMap* tilemap);
void erodeFluids(TileMap* tilemap);

void dilateNearFluids(TileMap* tilemap);
void erodeNearFluids(TileMap* tilemap);

void dilateNearCliffs(TileMap* tilemap);
void erodeNearCliffs(TileMap* tilemap);

void dilateForests(TileMap* tilemap);
void erodeForests(TileMap* tilemap);

void spawnRessources(TileMap* tilemap);
void burnRessources(TileMap* tilemap);

void allyCitizenBirth(Game* game);
void enemyCitizenBirth(Game* game);
void wildAnimalBirth(Game* game);
void peacefulAnimalBirth(Game* game);
    
void allyCitizenDeath(Game* game);
void enemyCitizenDeath(Game* game);
void wildAnimalDeath(Game* game);
void peacefulAnimalDeath(Game* game);

void citizenFeeding(TileMap* tilemap);
void citizenSicken(TileMap* tilemap);
void citizenJobUpdate(TileMap* tilemap);

void bonusPI(TileMap* tilemap);
// ----------------------------

#endif
