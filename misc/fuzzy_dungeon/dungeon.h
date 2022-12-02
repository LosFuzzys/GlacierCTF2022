#include <string>
#include <map>
#include <chrono>
#include <thread>
#include <iostream>

#define ACTION_SWORD    0
#define ACTION_HEAL     1
#define ACTION_HELMET   2
#define ACTION_DOOR     3
#define NO_ACTION       -1

#define TEXT_START      "Welcome to the FuzzyDungeon. If you are able to make it to the black knight and manage to beat him he will reward you with his treasure. You see the door to the dungeon in front of you."
#define TEXT_ENTRY_HALL "You have entered the entry hall. The walls are decorated with old pictures. You are starting to rethink your idea of slaying the beast and getting the treasure. After some thoughts you commence and see two doors at the end of the hall."
#define TEXT_SWORD      "You seem to be lucky. After you step through the door you see a sword that looks way stronger than your current one lying on a table. At the end of the room there is one door."
#define TEXT_LAKE       "After stepping through the door you almost fall into water. There's a lake covering most of the room. At the other side of the lake you can see a small hut built next to the door."
#define TEXT_GOBLIN     "When you try to sneak past the hut you hear loud noises from inside. As you are a nosy person you can't stop looking through the window and directly looking into the eyes of an angry goblin. It directly charges you. Behind the goblin a door goes to the left."
#define TEXT_POTION     "You enter a beautiful room with a fountain and a small red bottle next to it. The room ends in a door."
#define TEXT_TEMPLE     "The room you enter looks like a greek temple. After taking some time to look at statues of a lot of naked people you find a small hidden door. The way further into the dungeon goes to the right."
#define TEXT_DOOR       "You investigate the hidden door and it doesn't seem that stable. You could try to smash it open using your sword."
#define TEXT_BARDS      "The door opens up to a hall in which a group of bards train to impress the black knight. You take some time to watch them, rest and amuse yourself. You can now choose to go to the left or right."
#define TEXT_GRYFFIN    "Right after walking through the door you hear a screaching noise. Before you can turn around a gryffin descends from the air and attacks you. In the middle of the action you see a door behind the gryffin."
#define TEXT_DWARF      "You walk through the door and directly fall into a hole. As you get up again you realize that you fell into a dwarfs home and destroyed half his house in the process. The dwarf doesn't care about your excuses and charges you. If you defeat him you can commence further."
#define TEXT_ARMORY     "The door leads to an old armory. After taking some time digging through all kinds of armor you find a helmet in A+ condition. There is a giant door to the right which seems to lead to an important place."
#define TEXT_MERMAID    "When you step through the door you already hear beautiful voices singing. There is a beautiful door on the left. A mermaid smiles at you and waves you to get closer. When you get closer she hugs you and suddenly stabs you in the back. You push her away but you will now have to fight for your life."
#define TEXT_BOSS       "You enter the black knights chamber. He smiles and says: \"I didn't think you would make it this far.\"."

#define LINE            "-----------------------------------------------------------------------------------------------------"

std::string fight_sounds[5] = {"Pow!\n", "Bang!\n", "Boom!\n", "Scratch!\n", "Ouch!\n"};
std::string standard_actions = {"You can do the following things: \nS - See your Stats"};

class Enemy;
class Action;
class Room;
class Player;

class Enemy {
    private:

    public:
        int health;
        int damage;
        bool dead;
        bool boss;
        std::string name;

        Enemy(int _health, int _damage, std::string _name, bool _boss)
        {
            health = _health;
            damage = _damage;
            name = _name;
            dead = false;
            boss = _boss;
        }
};

class Player {
    private:

    public:
        int turn_number;
        Room* current_room;
        int health;
        unsigned short int damage;
        bool boss_defeated;

        Player()
        {
            health = 100;
            damage = 5;
            boss_defeated = false;
            turn_number = 0;
            current_room = nullptr;
        }

        std::string get_stats()
        {
            return ("Health: " + std::to_string(health) + "\nDamage: " + std::to_string(damage));
        }
};

class Action{
    public:
        bool done;
        int type;

        Action(int _type)
        {
            type = _type;
            done = false;
        }

        void doAction(Player* _player)
        {
            switch (type)
            {
            case ACTION_SWORD:
                std::cout << "You pick up the sword. Your damage has increased by 3 points." << std::endl;
                _player->damage += 3;
                done = true;
                break;

            case ACTION_HEAL:
                std::cout << "You drink the Potion. Your health gets fully replenished." << std::endl;
                _player->health = 100;
                done = true;
                break;

            case ACTION_HELMET:
                std::cout << "You pick up the helmet. Your health gets increased by 10" << std::endl;
                _player->health += 10;
                done = true;
                break;

            case ACTION_DOOR:
                std::cout << "You hit the door with your sword a few times. It doesn't seem to help.\n You chip a part of your sword. Your damage decreases by 3." << std::endl;
                _player->damage -= 3;
                break;
            
            default:
                std::cout << "[ERROR] This should not happen!" << std::endl;
                break;
            }
        }

        std::string getChoice()
        {
            switch (type)
            {
            case ACTION_SWORD:
                return "Pick up the sword";
                break;

            case ACTION_HEAL:
                return "Drink the potion";
                break;

            case ACTION_HELMET:
                return "Pick up the helmet";
                break;

            case ACTION_DOOR:
                return "Hit the door with your sword";
                break;
            
            default:
                return "[ERROR] This should not happen!";
                break;
            }
        }
};

class Room {
    public:
        std::string text;
        Room* next_right;
        Room* next_center; 
        Room* next_left;
        Enemy* enemy;
        Action* action;

        Room(std::string _text, Room* _next_right, Room* _next_center, Room* _next_left, int _action_type)
        {
            text = _text; 
            next_right = _next_right;
            next_center = _next_center; 
            next_left = _next_left;
            enemy = nullptr;
            if(_action_type != NO_ACTION)
            {
                action = new Action(_action_type);
            }
        }

        /*
        void printInfo()
        {
            std::cout << "text: " + text <<std::endl;
            std::cout << "next_right: " + _next_right <<std::endl;
            std::cout << "next_center: " + _next_center <<std::endl;
            std::cout << "next_left: " + _next_left <<std::endl;
        }

        */
};
