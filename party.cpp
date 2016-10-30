#include "party.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Zombie.hpp"
#include "NoTengoMuffins.hpp"

Party::Party(){
    InputManager::bind(InputAction::moveX0, 0, sf::Joystick::Axis::X);
    InputManager::bind(InputAction::moveY0, 0, sf::Joystick::Axis::Y);
    InputManager::bind(InputAction::recharge0, 0, 2);
    InputManager::bind(InputAction::shot0, 0, 0);
    InputManager::bind(InputAction::moveX1, 1, sf::Joystick::Axis::X);
    InputManager::bind(InputAction::moveY1, 1, sf::Joystick::Axis::Y);
    InputManager::bind(InputAction::recharge1, 1, 2);
    InputManager::bind(InputAction::shot1, 1, 0);

    ASSERT(collisionMap.loadFromFile("Resources/BackgroundCollider.png"));
    ASSERT(backgroundMap.loadFromFile("Resources/Background.png"));
    ASSERT(zombieTex.loadFromFile("Resources/zombieMuffin.png"));
    ASSERT(playerTexFace.loadFromFile("Resources/mafin.png"));
    ASSERT(playerTex.loadFromFile("Resources/mafinPepptiter.png"));
    ASSERT(playerTex2.loadFromFile("Resources/mafinPepptiter2.png"));
    ASSERT(bulletTex.loadFromFile("Resources/ShittyPepitty.png"));
    ASSERT(numberText.loadFromFile("Resources/numbers.png"));
    ASSERT(bulletTex2.loadFromFile("Resources/ShittyPepitty2.png"));
    players.push_back(new Player(this, &playerTex, &playerTexFace, &collisionMap,
    {
                                     InputAction::shot0,
                                     InputAction::recharge0,
                                     InputAction::moveX0,
                                     InputAction::moveY0
                                 } , 9 , 8
                                 ));
    players.push_back(new Player(this, &playerTex2, &playerTexFace, &collisionMap,
    {
                                     InputAction::shot1,
                                     InputAction::recharge1,
                                     InputAction::moveX1,
                                     InputAction::moveY1
                                 } , 9 , 8
                                 ));
    for(int i = 0; i < 100; ++i)
        zombies.push_back(new Zombie(this, &zombieTex, &collisionMap,8,8));
    map = new Map(&backgroundMap);

}

Party::~Party(){
    for(auto p : players)
        delete p;
    for(auto p : zombies)
        delete p;
    for(auto p : bullets)
        delete p;

}

void Party::update(float deltaTime, sf::RenderWindow* window){
    InputManager::update();
    for(Player* p : players)
        p->update(deltaTime);
    for(Zombie* z : zombies)
        z->update(deltaTime);
    std::set<Bullet*> toDelete;
    std::set<Zombie*> toDeleteZombies;
    for(Bullet* b : bullets) {
        b->update(deltaTime);
        if(b->hasCollided()) {
            toDelete.insert(b);
            continue;
        }
        for(Zombie* z : zombies) {
            if(b->getGlobalBounds().intersects(z->getGlobalBounds())){
                toDeleteZombies.insert(z);
                toDelete.insert(b);
                b->player->upScore(z->getPoints());
                break;
            }
        }

        for(Player* p : players) {
            if(p != b->player && b->getGlobalBounds().intersects(p->getGlobalBounds())){
                p->push(b->getMov()*3.0f);
                toDelete.insert(b);
                break;
            }
        }
    }
    for(std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end();) {
        if(toDelete.find(*it) != toDelete.end()) {
            delete *it;
            it = bullets.erase(it);
        }
        else ++it;
    }
    for(std::vector<Zombie*>::iterator it = zombies.begin(); it != zombies.end();) {
        if(toDeleteZombies.find(*it) != toDeleteZombies.end()) {
            delete *it;
            it = zombies.erase(it);
        }
        else ++it;
    }
    calcScores();
}

void Party::draw(sf::RenderWindow*window){
    map->draw(window);
    for(Player* p : players)
        p->draw(window);
    for(Zombie* z : zombies)
        z->draw(window);
    for(Bullet* b : bullets)
        b->draw(window);
    for(int i = 0; i < scores.size(); ++i){
        for(int j = 0; j < scores[i].size(); ++j){
            window->draw(scores[i][j]);
        }
    }
}

void Party::updateButtons(sf::Event e){

}

void Party::newShot(Player* id, sf::Vector2f dir){

    bullets.push_back(new Bullet(this,((id == players[0])? &bulletTex : &bulletTex2),&collisionMap,1,1,dir,id));
}

void Party::calcScores(){
    for( int i = 0; i < players.size(); ++i){
        std::vector<sf::Sprite> aux = std::vector<sf::Sprite>(0);
        std::vector<int> splitScore;
        split_score(splitScore, players[i]->getScore());
        for(int j = 0; j < splitScore.size();++j){
            sf::Sprite sn;
            int n = splitScore[j];
            sn.setTexture(numberText);
            sn.setTextureRect(sf::IntRect((numberText.getSize().x/10)*n,0,numberText.getSize().x/10,numberText.getSize().y));
            sn.setPosition(1500*i+(scoreOffset+j*numberText.getSize().x/10),scoreOffset);
            aux.push_back(sn);
        }
        scores[i] = aux;
    }
}

void Party::split_score(std::vector<int>& v, int score){
    if(score == 0) v.push_back(0);
    else{
        while(score > 0){
            int n = score%10;
            score = score/10;
            v.push_back(n);
        }

        std::reverse(v.begin(),v.end());
    }
}
