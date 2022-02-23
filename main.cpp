#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>

const unsigned int WINDOW_WIDTH = 350; 
const unsigned int WINDOW_HEIGHT = 420; 

double EuclideanDistance(sf::Vector2f p1, sf::Vector2f p2 ){
    return sqrt(
        pow(p1.x- p2.x,2) + pow(p1.y - p2.y,2) 
    ); 
}
class Target  
{
    sf::Vector2f targetPosition; 
    unsigned int speed;
    unsigned int count; 
    double radius; 
    public:
        sf::CircleShape shape; 
        
        Target(float radius, sf::Color color){
            this->radius = radius;
            shape = sf::CircleShape(radius);
            shape.setFillColor(color);
            this->setInitialTargetPosition(); 
            count = 0;  
        }
        bool updateCaptures(sf::Vector2f agent){
            bool got_it= false;
            if(EuclideanDistance(this->shape.getPosition(), agent) < radius){
                count++; 
                got_it = true; 
                setNewRandomTargetPosition();
                this->shape.setPosition(targetPosition);
            }
            return got_it;
        } 
        unsigned int getNumberOfCaputers(){
            return count;
        }
        void setInitialTargetPosition(){
            setNewRandomTargetPosition(); 
        }
        void setSpeed(unsigned int speed){
            this->speed = speed; 
        }
        void setNewRandomTargetPosition(){
            this->targetPosition.x = rand()%WINDOW_WIDTH;
            this->targetPosition.y = rand()%WINDOW_HEIGHT; 
        }
        void moveToTarget(){
            const sf::Vector2f position = this->shape.getPosition(); 
            sf::Vector2f new_position;
            sf::Vector2i offset; 
            if(position.x < targetPosition.x and position.x < WINDOW_WIDTH)
                offset.x = 1; 
            else if(position.x > targetPosition.x and position.x > 0)
                offset.x = -1 ;
            else{
                setNewRandomTargetPosition(); 
            }
            if(position.y < targetPosition.y and position.y < WINDOW_HEIGHT)
                offset.y = 1; 
            else if(position.y > targetPosition.y and position.y > 0)
                offset.y = -1;
            else {
                setNewRandomTargetPosition(); 
            }
            this->shape.move(offset.x, offset.y);

        }    


        void moveToRandomPosition(){
            const sf::Vector2f position = this->shape.getPosition();
            if(position == this->targetPosition){
                this->setNewRandomTargetPosition(); 
            }
            else{
                moveToTarget(); 
            }
        }
}; 

void moveToTarget(sf::CircleShape& agent, Target& target ){
            const sf::Vector2f targetPosition = target.shape.getPosition(); 
            const sf::Vector2f position = agent.getPosition();
            sf::Vector2i offset; 
            if(position.x < targetPosition.x and position.x < WINDOW_WIDTH)
                offset.x = 2; 
            else if(position.x > targetPosition.x and position.x > 0)
                offset.x = -2 ;
            else{
                target.updateCaptures(agent.getPosition());
            }
            if(position.y < targetPosition.y and position.y < WINDOW_HEIGHT)
                offset.y = 2; 
            else if(position.y > targetPosition.y and position.y > 0)
                offset.y = -2;
            else {
                target.updateCaptures(agent.getPosition());
            }
            if(target.updateCaptures(agent.getPosition())){
                agent.setRadius(agent.getRadius() + 2.F); 
            }
            agent.move(offset.x, offset.y); 

}   

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Hello From SFML");
    sf::CircleShape shape(10.F);
    sf::CircleShape agent(3.F); 
    agent.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    shape.setPosition(0,0);
    agent.setFillColor(sf::Color::Cyan);
    agent.setOutlineColor(sf::Color::Red);
    Target tgt(4.F, sf::Color::Yellow); 
    sf::Clock clock;
    float time_interval;
    float last_oc = 0;
    sf::Text counting_txt; 
    std::string counting_str = "Captured: "; 
    counting_txt.setCharacterSize(20); 
    counting_txt.setFillColor(sf::Color::Red); 
    sf::Font font; 
    if (!font.loadFromFile("Roboto_Mono/RobotoMono-VariableFont_wght.ttf")){
        std::cerr<< "ERROR "; 
    }
    counting_txt.setFont(font);
    while (window.isOpen())
    {
        std::stringstream ss; 
        std::string s; 
        time_interval = clock.getElapsedTime().asSeconds(); 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        std::cout << time_interval << ' ' << last_oc << '\n';
        if((time_interval - last_oc) > 0.1 ){
            shape.move(1,1);
            last_oc = time_interval;
            tgt.moveToRandomPosition();
            moveToTarget(agent,tgt);
        }
        ss << tgt.getNumberOfCaputers(); 
        ss >> s;
        counting_txt.setString(counting_str + s); 
        counting_txt.setPosition(199,300);
        window.draw(tgt.shape);
        window.draw(agent);
        window.draw(counting_txt);  
        window.display();
    }
    return 0;
}
