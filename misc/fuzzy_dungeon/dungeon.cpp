#include "dungeon.h"


Room** rooms;
bool debug = true;

void fight(Player* _player, Enemy* _enemy, bool player_attacks)
{
    std::cout << "\n" << std::endl;

    while (_player->health > 0 && _enemy->health > 0)
    {
        std::cout << LINE << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        if (player_attacks)
        {
            std::cout << "You attack the enemy. Your weapon has a damage of " + std::to_string(_player->damage) + "." << std::endl;
            _enemy->health -= _player->damage;
            
            if(_enemy->health < 0)
            {
                _enemy->health = 0;
            }

            std::cout << fight_sounds[rand()%5] << std::endl;

            std::cout << "You reduce your enemys health to " + std::to_string(_enemy->health) + " HP." << std::endl;

            player_attacks = false;
        }
        else
        {
            std::cout << "The " + _enemy->name + " attacks you. You will lose " + std::to_string(_enemy->damage) + " HP." << std::endl;
            
            _player->health -= _enemy->damage;
            
            if(_player->health < 0)
            {
                _player->health = 0;
            }

            std::cout << fight_sounds[rand()%5] << std::endl;

            std::cout << "The attack reduces your health to " + std::to_string(_player->health) + " HP." << std::endl;

            player_attacks = true;
        }

        std::cout << LINE << std::endl;
    }

    if(_player->health == 0)
    {
        std::cout << "You lost this fight :(" << std::endl;
    }
    else if (_enemy->health == 0)
    {
        std::cout << "You won this fight :)" << std::endl;

        _enemy->dead = true;

        if (_enemy->boss)
        {
            _player->boss_defeated = true;
        }
    }
    else
    {
        std::cout << "ERROR: THis should not happen!" << std::endl;
    }
}

void turn(Player* _player)
{
    bool room_finished = false;

    std::cout << LINE << std::endl;
    std::cout << "This is your turn number: " + std::to_string(_player->turn_number) << std::endl;

    std::cout << _player->current_room->text << std::endl;

    if (_player->current_room->enemy)
    {
        fight(_player, _player->current_room->enemy, true);
    }

    while (!room_finished && _player->health != 0 && !_player->boss_defeated)
    {
        std::cout << "\n" + standard_actions << std::endl;

        if (_player->current_room->next_right != nullptr)
        {
            //TODO: Add special case for Hidden door
            if (_player->current_room == rooms[7])
            {
                std::cout << "R - Go back into the temple" << std::endl;
            }
            else
            {
                std::cout << "R - Go to the right door" << std::endl;
            }
        }

        if (_player->current_room->next_center != nullptr)
        {
            std::cout << "C - Go to the door" << std::endl;
        }

        if (_player->current_room->next_left != nullptr)
        {
            if (_player->current_room == rooms[6])
            {
                std::cout << "L - Go to the hidden door" << std::endl;
            }
            else
            {
                std::cout << "L - Go to the left door" << std::endl;
            }
            
        }

        if (_player->current_room->action != nullptr && !(_player->current_room->action->done))
        {
            std::cout << "A - " + _player->current_room->action->getChoice() << std::endl;
        }

        std::cout << "\nEnter your choice:\n";
        
        std::string input;
        char input_char;

        std::getline(std::cin, input);

        if(input.length() != 1)
        {
            std::cout << "Invalid Input, only one char is allowed" << std::endl;
        }
        else
        {
            input_char = input[0];
        }  
        
        if (input_char == 'S')
        {
            std::cout << _player->get_stats() << std::endl;
        }
        else if(input_char == 'R' && _player->current_room->next_right != nullptr)
        {
            _player->current_room = _player->current_room->next_right;
            room_finished = true;
        }
        else if(input_char == 'C' && _player->current_room->next_center != nullptr)
        {
            _player->current_room = _player->current_room->next_center;
            room_finished = true;
        }
        else if(input_char == 'L' && _player->current_room->next_left != nullptr)
        {
            _player->current_room = _player->current_room->next_left;
            room_finished = true;
        }
        else if (input_char == 'A' && _player->current_room->action != nullptr)
        {
            _player->current_room->action->doAction(_player);
        }
        else
        {
            std::cout << "Invalid Input!" << std::endl;
        }
    }

    _player->turn_number++;
}

void play(){
    Player* player = new Player();

    player->current_room = rooms[0];

    rooms[4]->enemy  = new Enemy(10, 3, "Goblin", false);
    rooms[9]->enemy  = new Enemy(30, 5, "Gryffin", false);
    rooms[10]->enemy = new Enemy(8, 2, "Dwarf", false);
    rooms[12]->enemy = new Enemy(20, 2, "Mermaid", false);
    rooms[13]->enemy = new Enemy(1000, 50, "Black Knight", true);

    while (player->health > 0 && !player->boss_defeated)
    {
        turn(player);
    }

    if (player->boss_defeated)
    {
        std::cout << "glacierctf{1t5_oNlY_4_fl35h_w0unD}" << std::endl;
    }
    else
    {
        std::cout << "Unfortunately you died. You have to restart." << std::endl;
    }
}

void init()
{
    rooms = (Room**)calloc(14, sizeof(Room*));

    //Bossfight
    rooms[13] = new Room(TEXT_BOSS, nullptr, nullptr, nullptr, NO_ACTION);

    //Mermaid
    rooms[12] = new Room(TEXT_MERMAID, nullptr,nullptr,rooms[13],NO_ACTION);

    //Armory
    rooms[11] = new Room(TEXT_ARMORY,rooms[13], nullptr, nullptr, ACTION_HELMET);

    //Dwarf
    rooms[10] = new Room(TEXT_DWARF,nullptr,rooms[11], nullptr, NO_ACTION);

    //Gryffin
    rooms[9] = new Room(TEXT_GRYFFIN, nullptr, rooms[12], nullptr, NO_ACTION);

    //Bards
    rooms[8] = new Room(TEXT_BARDS,rooms[9], nullptr, rooms[10], NO_ACTION);

    //Hidden Door
    rooms[7] = new Room(TEXT_DOOR, rooms[6], nullptr, nullptr, ACTION_DOOR);

    //Temple
    rooms[6] = new Room(TEXT_TEMPLE, rooms[5], nullptr, rooms[7], NO_ACTION);
    rooms[7]->next_right = rooms[6];

    //Healing Potion
    rooms[5] = new Room(TEXT_POTION, nullptr, rooms[8], nullptr, ACTION_HEAL);
    rooms[6]->next_right = rooms[5];

    //Goblin Hut
    rooms[4] = new Room(TEXT_GOBLIN, nullptr, nullptr, rooms[5], NO_ACTION);
    
    //Lake
    rooms[3] = new Room(TEXT_LAKE, nullptr,rooms[4], nullptr, NO_ACTION);

    //Sword Room
    rooms[2] = new Room(TEXT_SWORD, nullptr, rooms[6], nullptr, ACTION_SWORD);

    //Entry Hall
    rooms[1] = new Room(TEXT_ENTRY_HALL, rooms[3], nullptr, rooms[2], NO_ACTION);

    //Start
    rooms[0] = new Room(TEXT_START, nullptr, rooms[1], nullptr, NO_ACTION);
}

int main(){
    init();

    while(1)
    {
        play();
    }
}