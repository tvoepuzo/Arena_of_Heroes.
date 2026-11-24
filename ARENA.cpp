#include <Windows.h> 
#pragma execution_character_set("utf-8")
#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Hero {
protected:
    string name;
    int hp;
    int damage;

public:
    Hero(string n, int h, int d) {
        name = n;
        hp = h;
        damage = d;
    }

    string getName() {
        return name;
    }

    int getHP() {
        return hp;
    }

    void takeDamage(int d) {
        hp -= d;

        if (hp < 0) {
            hp = 0;
        }
    }

    virtual int attack() {
        return damage;
    }

    virtual void show() {
        cout << name << " | HP: " << hp
            << " | Урон: " << damage << endl;
    }

    virtual ~Hero() {}
};

// Воин
class Warrior : public Hero {
public:
    Warrior() : Hero("Воин", 120, 20) {}
};

// Лучник
class Archer : public Hero {
public:
    Archer() : Hero("Лучник", 100, 25) {}
};

// Маг
class Mage : public Hero {
public:
    Mage() : Hero("Маг", 80, 30) {}
};

// Создание персонажа
unique_ptr<Hero> createHero(int choice) {
    if (choice == 1)
        return make_unique<Warrior>();

    if (choice == 2)
        return make_unique<Archer>();

    if (choice == 3)
        return make_unique<Mage>();

    return nullptr;
}

// Ввод числа с проверкой
int inputNumber(string message, int min, int max) {
    int number;

    while (true) {
        try {
            cout << message;

            string input;
            getline(cin, input);

            number = stoi(input);

            if (number < min || number > max) {
                cout << "Введите число от " << min
                    << " до " << max << "!\n";
            }
            else {
                return number;
            }
        }
        catch (...) {
            cout << "Ошибка ввода! Введите число.\n";
        }
    }
}

// Выбор персонажа
void showHeroes() {
    cout << "\n--- ВЫБОР ГЕРОЯ ---\n";
    cout << "1. Воин\n";
    cout << "2. Лучник\n";
    cout << "3. Маг\n";
}

// Бой
void battle(Hero& player, Hero& enemy) {
    cout << "\nБитва начинается!\n";
    cout << player.getName() << " против "
        << enemy.getName() << "!\n";

    while (player.getHP() > 0 && enemy.getHP() > 0) {
        cout << "\n-------------------------\n";
        cout << player.getName() << " HP: "
            << player.getHP() << endl;
        cout << enemy.getName() << " HP: "
            << enemy.getHP() << endl;

        cout << "\n1. Атака\n";
        cout << "2. Защита\n";

        int choice = inputNumber("Ваше действие: ", 1, 2);

        int enemyDamage = enemy.attack();

        if (choice == 1) {
            int playerDamage = player.attack();

            enemy.takeDamage(playerDamage);

            cout << "\nВы атаковали!\n";
            cout << "Нанесено " << playerDamage
                << " урона.\n";
        }
        else {
            enemyDamage = enemyDamage / 2;

            cout << "\nВы приняли защитную стойку!\n";
        }

        if (enemy.getHP() <= 0) {
            cout << "\nВы победили "
                << enemy.getName() << "!\n";
            cout << "ПОБЕДА!\n";
            break;
        }

        player.takeDamage(enemyDamage);

        cout << enemy.getName() << " атакует!\n";
        cout << "Вы получили " << enemyDamage
            << " урона.\n";

        if (player.getHP() <= 0) {
            cout << "\nВаш персонаж проиграл!\n";
            cout << "ПОРАЖЕНИЕ!\n";
            cout << "Игра окончена.\n";
        }
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    bool game = true;

    while (game) {
        cout << "\n===== АРЕНА ГЕРОЕВ =====\n";
        cout << "1. Выбрать персонажа\n";
        cout << "0. Выход\n";

        int menu = inputNumber("Выбор: ", 0, 1);

        if (menu == 0) {
            cout << "Выход из игры.\n";
            break;
        }

        showHeroes();

        int heroChoice = inputNumber("Ваш герой: ", 1, 3);

        unique_ptr<Hero> player = createHero(heroChoice);

        cout << "\nВы выбрали: "
            << player->getName() << endl;

        cout << "\n--- ВЫБОР СОПЕРНИКА ---\n";
        cout << "1. Воин\n";
        cout << "2. Лучник\n";
        cout << "3. Маг\n";

        int enemyChoice = inputNumber("Ваш соперник: ", 1, 3);

        unique_ptr<Hero> enemy = createHero(enemyChoice);

        cout << "\nВаш соперник: "
            << enemy->getName() << endl;

        battle(*player, *enemy);

        if (player->getHP() <= 0) {
            game = false;
        }
    }

    return 0;
}