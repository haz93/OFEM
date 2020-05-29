#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "StandardCursor.hpp"
#include <iostream>
#include "Display.hpp"
#include <Eigen/Dense>
#include <Eigen/Sparse>
//#include <string>
//#include <fstream>
//#include <vector>


class triangles : public sf::Drawable, public sf::Transformable
{
public:
    triangles(unsigned int count)
    {
        m_verticest.setPrimitiveType(sf::Triangles);
        m_verticest.resize(count);
        m_verticest[0].position = sf::Vector2f(10.f, 10.f);
        m_verticest[1].position = sf::Vector2f(100.f, 10.f);
   //   m_verticest[2].position = sf::Vector2f(100.f, 100.f);

    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // our particles don't use a texture
        states.texture = NULL;

        // draw the vertex array
        target.draw(m_verticest, states);
    }

private:
    sf::VertexArray m_verticest;
};




    class axises : public sf::Drawable, public sf::Transformable
    {
    public:
        axises(unsigned int count, std::vector<int>* eles, Eigen::VectorXf* xs, Eigen::VectorXf* ys, Eigen::VectorXf* dispxs, Eigen::VectorXf* dispys, std::vector<float> postp) : m_vertices(sf::Lines, 10)
        {


            nodenumber = 0;
            m_vertices2.setPrimitiveType(sf::Lines);
            m_vertices2.resize(count * 6);

            m_vertices3.setPrimitiveType(sf::Lines);
            m_vertices3.resize(count * 6);
            
            shapes.resize(count); 


          int ofs = 0;
          int ofs2 = 0;

          float min = postp[0];
          float max = postp[0];
          for (int i = 1; i < count; i++)

          {
              if(postp[i] > max)
              {
                  max = postp[i];
              }
              else if (postp[i] < min)
              {
                  min = postp[i];
              }

          }
         for (int i = 0; i < count; i++)
         {
             sf::Uint8 color = ((postp[i] - min )/ (max-min)) * 255;
             std::cout << color;
             shapes[i].setPointCount(3);
             shapes[i].setFillColor(sf::Color::Color(color,0,0,255));
             shapes[i].setPoint(0, sf::Vector2f((100.f * (*dispxs)[(*eles)[ofs]]), (100.f * (*dispys)[(*eles)[ofs]])));
             shapes[i].setPoint(1, sf::Vector2f((100.f * (*dispxs)[(*eles)[ofs+1]]), (100.f * (*dispys)[(*eles)[ofs+1]])));
             shapes[i].setPoint(2, sf::Vector2f((100.f * (*dispxs)[(*eles)[ofs+2]]), (100.f * (*dispys)[(*eles)[ofs+2]])));


             //first line
         m_vertices2[(ofs2+0)].position.x = (100.f * (*xs)[(*eles)[ofs]]);
         m_vertices2[(ofs2 + 0)].position.y = (100.f * (*ys)[(*eles)[ofs]]);


          m_vertices2[(ofs2 + 1)].position.x = (100.f * (*xs)[((*eles)[ofs+1])]);
          m_vertices2[(ofs2 + 1)].position.y = (100.f * (*ys)[((*eles)[ofs+1])]);
          
          //second line


            m_vertices2[(ofs2 + 2)].position.x = (100.f * (*xs)[((*eles)[ofs+1])]);
            m_vertices2[(ofs2 + 2)].position.y = (100.f *(*ys)[((*eles)[ofs+1])]);

            m_vertices2[(ofs2 + 3)].position.x = (100.f * (*xs)[((*eles)[ofs + 2])]);
            m_vertices2[(ofs2 + 3)].position.y = (100.f * (*ys)[((*eles)[ofs + 2])]);


            //third line

            m_vertices2[(ofs2 + 4)].position.x = (100.f * (*xs)[((*eles)[ofs + 2])]);
            m_vertices2[(ofs2 + 4)].position.y = (100.f * (*ys)[((*eles)[ofs + 2])]);


            m_vertices2[(ofs2 + 5)].position.x = (100.f * (*xs)[((*eles)[ofs])]);
            m_vertices2[(ofs2 + 5)].position.y = (100.f * (*ys)[((*eles)[ofs])]);

           ///////////////////////
                   //first line
            m_vertices3[(ofs2 + 0)].position.x = (100.f * (*dispxs)[(*eles)[ofs]]);
            m_vertices3[(ofs2 + 0)].position.y = (100.f * (*dispys)[(*eles)[ofs]]);
            m_vertices3[(ofs2 + 0)].color = sf::Color::Blue;


            m_vertices3[(ofs2 + 1)].position.x = (100.f * (*dispxs)[((*eles)[ofs + 1])]);
            m_vertices3[(ofs2 + 1)].position.y = (100.f * (*dispys)[((*eles)[ofs + 1])]);
            m_vertices3[(ofs2 + 1)].color = sf::Color::Blue;
            //second line


            m_vertices3[(ofs2 + 2)].position.x = (100.f * (*dispxs)[((*eles)[ofs + 1])]);
            m_vertices3[(ofs2 + 2)].position.y = (100.f * (*dispys)[((*eles)[ofs + 1])]);
            m_vertices3[(ofs2 + 2)].color = sf::Color::Blue;

            m_vertices3[(ofs2 + 3)].position.x = (100.f * (*dispxs)[((*eles)[ofs + 2])]);
            m_vertices3[(ofs2 + 3)].position.y = (100.f * (*dispys)[((*eles)[ofs + 2])]);
            m_vertices3[(ofs2 + 3)].color = sf::Color::Blue;


            //third line

            m_vertices3[(ofs2 + 4)].position.x = (100.f * (*dispxs)[((*eles)[ofs + 2])]);
            m_vertices3[(ofs2 + 4)].position.y = (100.f * (*dispys)[((*eles)[ofs + 2])]);
            m_vertices3[(ofs2 + 4)].color = sf::Color::Blue;


            m_vertices3[(ofs2 + 5)].position.x = (100.f * (*dispxs)[((*eles)[ofs])]);
            m_vertices3[(ofs2 + 5)].position.y = (100.f * (*dispys)[((*eles)[ofs])]);
            m_vertices3[(ofs2 + 5)].color = sf::Color::Blue;





               ofs += 3;
               ofs2 += 6;

          }
    
         //draws xy axis
            m_vertices[0].position = sf::Vector2f(0, 0);
            m_vertices[1].position = sf::Vector2f(std::numeric_limits<float>::max(), 0);
            m_vertices[2].position = sf::Vector2f(0, 0);
            m_vertices[3].position = sf::Vector2f(-1.17549 * std::pow(10, 38), 0);

            m_vertices[0].color = sf::Color::Red;
            m_vertices[1].color = sf::Color::Red;
            m_vertices[2].color = sf::Color::Red;
            m_vertices[3].color = sf::Color::Red;

            m_vertices[4].position = sf::Vector2f(0, 0);
            m_vertices[5].position = sf::Vector2f(0, std::numeric_limits<float>::max());
            m_vertices[6].position = sf::Vector2f(0, 0);
            m_vertices[7].position = sf::Vector2f(0, -1.17549 * std::pow(10, 38));

            m_vertices[4].color = sf::Color::Green;
            m_vertices[5].color = sf::Color::Green;
            m_vertices[6].color = sf::Color::Green;
            m_vertices[7].color = sf::Color::Green;

        }

        void setEmitter(sf::Vector2f position)
        {
            if (nodenumber == 0)
            {
                m_vertices[8].position = position;
                nodenumber = 1;
                std::cout << position.x << " " << position.y << std::endl;
            }
            else if (nodenumber == 1)
            {
                m_vertices[9].position = position;
                nodenumber = 0;
                std::cout << position.x << " " << position.y << std::endl;
            }
        }

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // apply the transform
            states.transform *= getTransform();

            // our particles don't use a texture
            states.texture = NULL;

            // draw the vertex array
            target.draw(m_vertices, states);
         

            for (int i = 0; i < shapes.size(); ++i)
            {

              target.draw(shapes[i], states);
        
            }
            target.draw(m_vertices2, states);
            target.draw(m_vertices3, states);
        }

    private:
        sf::VertexArray m_vertices;
        sf::VertexArray m_vertices2;
        sf::VertexArray m_vertices3;
        int nodenumber;
        std::vector<sf::ConvexShape> shapes;
    


    };

        int dsp::dispxx::maindisplay(Eigen::VectorXf* nodesx, Eigen::VectorXf* nodesy, int nodescount, int elementcount, Eigen::VectorXf* dispnodesx, Eigen::VectorXf* dispnodesy, std::vector<int>* elids, std::vector<float> postp)
        {
           
            // create the window
            sf::RenderWindow window(sf::VideoMode(800, 600), "Particles");
            sf::View view1(sf::FloatRect(0, 600, 800.f, -600.f));
            int windowmodex = 800;
            int windowmodey = 600;
            axises plot2D(elementcount, elids, nodesx, nodesy,dispnodesx,dispnodesy,postp);


            bool middlepressed = false;
            sf::Vector2i middlemousecords;

            float currzoom = 1;
         

            // run the main loop
            while (window.isOpen())
            {
                // handle events
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            sf::Vector2i mouse = sf::Mouse::getPosition(window);
                            plot2D.setEmitter(window.mapPixelToCoords(mouse));
                        }
                        else if (event.mouseButton.button == sf::Mouse::Middle)
                        {
                            middlepressed = true;
                            middlemousecords = sf::Mouse::getPosition(window);
                            sf::StandardCursor Cursor(sf::StandardCursor::HAND);
                            Cursor.set(window.getSystemHandle());

                        }

                    }
                    else if (event.type == sf::Event::MouseButtonReleased)
                    {
                        if (event.mouseButton.button == sf::Mouse::Middle)
                        {
                            middlepressed = false;
                            sf::StandardCursor Cursor(sf::StandardCursor::NORMAL);
                            Cursor.set(window.getSystemHandle());
                        }

                    }

                    if (middlepressed)
                    {
                        sf::Vector2i newmiddlemousecords = sf::Mouse::getPosition(window);
                        sf::Vector2i deltamouse = newmiddlemousecords - middlemousecords;


                        view1.move(-1 * deltamouse.x * currzoom, deltamouse.y * currzoom);
                        middlemousecords = newmiddlemousecords;
                    }

                    if (event.type == sf::Event::MouseWheelMoved)
                    {

                        if (event.mouseWheel.delta == 1)
                        {
                            view1.zoom(0.8);
                            currzoom *= 0.8;
                        }
                        else if (event.mouseWheel.delta == -1)
                        {
                            view1.zoom(1.25);
                            currzoom *= 1.25;
                        }
                    }

                    if (event.type == sf::Event::Resized)
                    {
                        // update the view to the new size of the window

                        sf::Vector2f viewsize = view1.getSize();
                        float scalex = event.size.width;
                        float scaley = event.size.height;
                        view1.setSize(scalex, -1 * scaley);
                        window.setView(view1);
                        currzoom = 1;

                        windowmodex = event.size.width;
                        windowmodey = event.size.height;
                    }

                }

             window.setView(view1);

             window.clear();

             window.draw(plot2D);
             window.display();
            }

            return 0;
        }
   
