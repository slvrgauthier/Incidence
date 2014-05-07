#include "save_menu_state.hpp"

SaveMenuState::SaveMenuState( Game * g ) : m_ui(this)
{
    m_game = g;

	init();
}

SaveMenuState::~SaveMenuState( void )
{

}

void SaveMenuState::init( void )
{
    Button * b;
    TextInsert * ti;
    GameEvent ge;

    ge.type = EV_BACK;

    b = new Button();
    b->setText( "Back", sf::Color::White );
    b->setBorder( sf::Color::Blue );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 100 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ti = new TextInsert();
    ti->setName("textSave");
    ti->setBorder(sf::Color::Blue);
    ti->setBorderSize(1);
    ti->setPositionAbsolute(300,200);
    ti->setSize(300,50);
    ti->select(true);
    m_ui.addWidget(ti);

    ge.type = EV_VALID;

    b = new Button();
    b->setText( "Save", sf::Color::White );
    b->setBorder( sf::Color::Blue );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 300 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);
}

void SaveMenuState::draw( sf::RenderTarget & window )
{
    window.setView(window.getDefaultView());
    m_ui.draw(window);
}

void SaveMenuState::update( void )
{

}

void SaveMenuState::handleEvent( sf::Event & e )
{
    m_ui.handleEvent(e);
}

void SaveMenuState::treatEvent( GameEvent e )
{
    switch(e.type) {

    case EV_BACK :
        StateManager::get()->popState();
        break;

    case EV_VALID :
        {
            std::string savePath((static_cast<TextInsert*>(m_ui.getWidget("textSave")))->getTextEnter());
            m_game->saveGame("saves/"+savePath+".save");
            StateManager::get()->popState();
        }
        break;

    default :
        break;

    }
}