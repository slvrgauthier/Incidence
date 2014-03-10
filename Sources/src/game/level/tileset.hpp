/*******************************************************************
** Description :                                                  **
** Fichier d'en-t�te de la classe TileSet, contenant les textures **
** des cases de la carte (sol, objets et entit�s).                **
**                                                                **
** Cr�ation : 04/03/14                                            **
** Modification : 07/03/14                                        **
*******************************************************************/

#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics.hpp>
#include "sol.hpp"
#include "element.hpp"

class TileSet {

	private:

		sf::Texture m_tileset;
		sf::Vector2u m_tilesize;
		int m_nombreSol;
		int m_nombreElement;
		std::vector<Sol> m_sols;
		std::vector<Element> m_elements;


	public:

		TileSet();
		TileSet(const std::string path);
		~TileSet();

		const sf::Texture* getTileset() const;
		sf::Vector2u getTileSize() const;
		int getNombreSol() const;
		int getNombreElement() const;

		Sol* getSol(int type, bool* bordures);
		Element* getElement(int type, int typeSol);

		bool load(const std::string& path);
		
		void TEST();

};

#endif