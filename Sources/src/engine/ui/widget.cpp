#include "widget.hpp"

#include <iostream>
#include <fstream>

#include "../foo.hpp"

Widget::Widget( char t ) : wType(t)
{
    this->name = "";
    this->content = NULL;

    this->setBackground( sf::Color::Transparent );
    this->setBorder( sf::Color::Transparent );
    this->setBorderSize( 0 );
    this->setPadding(0, 0);
    this->setSize(0, 0);

    this->setPositionAbsolute(0, 0);
    this->show = true;
}

Widget::~Widget( void ) { }

void Widget::loadFromFile( const std::string & path, const std::string & name )
{
    std::ifstream file;
    file.open( path.c_str() );

    std::string buffer = "";
    bool b = true;

    std::string wt = "+Widget";
    if(this->wType == 'b')
    {
        wt = "+Button";
    }
    else if(this->wType == 'c')
    {
        wt = "+Container";
    }
    else if(this->wType == 't')
    {
        wt = "+TextInsert";
    }

    do {
        file >> buffer;

        if(buffer == wt)
        {
            file >> buffer;
            if(buffer == name)
            {
                b = false;
            }
        }
    } while( b || file.eof());

    this->setName( buffer );

    while( buffer != "+End" && !file.eof() )
    {
        if( buffer == "Border" )
        {
            int r, g, b;
            file >> r >> g >> b;
            this->setBorder( sf::Color(r, g, b) );
        }
        else if( buffer == "Background")
        {
            int r, g, b;
            file >> r >> g >> b;
            this->setBackground( sf::Color(r, g, b) );
        }
        else if( buffer == "BorderSize" )
        {
            int s;
            file >> s;
            this->setBorderSize( s );
        }
        else if( buffer == "Content" )
        {
            std::string type, val = "";
            int r, g, b;
            sf::Color c(0, 0, 0);
            WidgetContent * d = NULL;

            file >> type;

            if(type == "TEXT")
            {
                char s;
                file >> s; // Read the first '"'
                file.get(s); // Read the first character of the text
                while( s != '"')
                {
                    val.push_back(s);
                    file.get(s);
                }

                file >> r >> g >> b;
                c.r = r;
                c.b = b;
                c.g = g;

                d = new WidgetContent(type, val, c);
            }
            else
            {
                file >> val;

                d = new WidgetContent(type, val);
            }

            this->setContent( d );
        }
        else if( buffer == "PosRel" )
        {
            std::string val;
            RelativePosition p = NONE;

            file >> val;
            if(val == "TOP")
            {
                p = TOP;
            }
            else if(val == "BOTTOM")
            {
                p = BOTTOM;
            }
            else if(val == "CENTER")
            {
                p = CENTER;
            }
            else if(val == "LEFT")
            {
                p = LEFT;
            }
            else if(val == "RIGHT")
            {
                p = RIGHT;
            }
            else if(val == "MIDDLE")
            {
                p = MIDDLE;
            }

            this->setPositionRelative( p );
        }
        else if( buffer == "PosAbs" )
        {
            int x, y;
            file >> x >> y;

            this->setPositionAbsolute(x, y);
        }
        else if( buffer == "Move" )
        {
            int x, y;
            file >> x >> y;

            this->move(x, y);
        }
        else if( buffer == "Padding" )
        {
            int x, y;
            file >> x >> y;

            this->setPadding(x, y);
        }
        else if( buffer == "Size" )
        {
            int x, y;
            file >> x >> y;

            this->setSize(x, y);
        }
        else if( buffer == "Show" )
        {
            int b;
            bool s;
            file >> b;

            s = (b==1?true:false);
            this->setShow(s);
        }
        else if( buffer == "+Widget" || buffer == "+Button" || buffer == "+TextInsert" || buffer == "+Container" )
        {
            while(buffer != "+End")
            {
                file >> buffer;
            }
        }

        file >> buffer;
    }

    file.close();

}

void Widget::setName( std::string name )
{
    this->name = name;
}

std::string Widget::getName( void ) const
{
    return this->name;
}

void Widget::setBackground( sf::Color c )
{
    this->background = c;
    this->shape.setFillColor( c );
}

void Widget::setBorder( sf::Color c )
{
    this->border = c;
    this->shape.setOutlineColor( c );
}

void Widget::setBorderSize( int s )
{
    this->border_size = s;
    this->shape.setOutlineThickness( s );
}

void Widget::setContent( WidgetContent * d )
{
    if(this->content)
    {
        delete this->content;
    }

    this->content = d;
    this->update();
}

void Widget::setPositionRelative( RelativePosition p )
{
    this->position = getAbsolutePosition( this->shape.getGlobalBounds(), this->parentBounds, p );
    this->position.x += this->shape.getOutlineThickness();
    this->position.y += this->shape.getOutlineThickness();
    this->update();
}

void Widget::setPositionAbsolute( float x, float y )
{
    this->setPositionAbsolute( sf::Vector2f(x, y) );
}

void Widget::setPositionAbsolute( sf::Vector2f p )
{
    this->position.x = p.x + this->parentBounds.left;
    this->position.y = p.y + this->parentBounds.top;
    this->update();
}

void Widget::setPadding( float x, float y )
{
    this->setPadding( sf::Vector2f(x, y) );
}

void Widget::setPadding( sf::Vector2f p )
{
    /*
    sf::Vector2f m;
    m.x = this->padding.x - p.x;
    m.y = this->padding.y - p.y;

    this->position.x += m.x;
    this->position.y += m.y;
*/
    this->padding = p;
    this->update();
}


void Widget::setSize( float x, float y )
{
    this->setSize( sf::Vector2f(x, y) );
}

void Widget::setSize( sf::Vector2f p )
{
    this->size = p;
    this->update();
}


void Widget::setParentBounds( sf::FloatRect r )
{
    this->parentBounds = r;
    this->update();
}

sf::FloatRect Widget::getBounds( void )
{
    return this->shape.getGlobalBounds();
}


void Widget::move( float x, float y )
{
    this->move( sf::Vector2f(x, y) );
}

void Widget::move( sf::Vector2f p )
{
    this->position.x += p.x;
    this->position.y += p.y;
    this->update();
}

void Widget::update( void )
{
    sf::FloatRect r(0, 0, 0, 0);
    if(this->content)
    {
        r = this->content->getContentBounds();
    }

    sf::Vector2f s1( r.width + this->padding.x*2, r.height + this->padding.y*2 );
    sf::Vector2f s2( this->size );
    sf::Vector2f sf;
    sf.x = std::max( s1.x, s2.x );
    sf.y = std::max( s1.y, s2.y );

    this->shape.setSize( sf );
    this->shape.setPosition( this->position );

    if(this->content)
    {
        int x = getAbsolutePosition( r, shape.getGlobalBounds(), CENTER).x;
        int y = getAbsolutePosition( r, shape.getGlobalBounds(), MIDDLE).y;
        sf::Vector2f p(x, y);

        this->content->setContentPosition( p );
    }
}

void Widget::setShow( bool b )
{
    this->show = b;
}

bool Widget::isShow( void )
{
    return this->show;
}

bool Widget::isOver( const sf::Vector2i & p ) const
{
    return isInner( this->shape.getGlobalBounds(), p );
}

void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(this->show)
    {
        target.draw( this->shape );

        if(this->content)
        {
            sf::Drawable * d = this->content->getContentDraw();
            if(d)
            {
                target.draw( *d );
            }
        }
    }
}

