#include <iostream>
#include <Windows.h>
#include <string>
#include <random>

class Hero
{
public:
	int location = 1;
    bool direction = 0;
    bool canFire = 1;
};

class Projectile
{
public:
    int location;
    bool active;
    bool direction;
};

class Enemy
{
public:
    int location = 0;
    bool alive = 0;
    bool direction = 0;
};




int main2() {
    char map[20] = "___________________";
    Hero myHero = Hero();
    Projectile myProjectile = Projectile();
    Enemy myEnemy = Enemy();

    while (true) {
        system("CLS");
        // Check if a key is pressed
        if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {   
            if (myHero.location > 0) {
                map[myHero.location] = '_';
                myHero.location -= 1;
            }
            myHero.direction = 0;
        }
        if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            if (myHero.location < 18) {
                map[myHero.location] = '_';
                myHero.location += 1;
            }
            myHero.direction = 1;
        }

        if (myEnemy.location == myHero.location) {
            exit(0);
        }

        if (GetKeyState('X') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {   
            if (myHero.canFire) {
                myProjectile.direction = myHero.direction;
                if (myHero.direction) {
                    myProjectile.location = myHero.location + 1;
                }
                else {
                    myProjectile.location = myHero.location - 1;
                }
                myProjectile.active = 1;
                myHero.canFire = 0;
            }

        }

        if (myProjectile.active) {

            map[myProjectile.location] = '_';

            if (myProjectile.direction) {
                myProjectile.location += 1;
            }
            else {
                myProjectile.location -= 1;
            }

            //check if malote and projectil chocan
            if (myEnemy.location == myProjectile.location) {
                myProjectile.active = 0;
                myEnemy.alive = 0;
                map[myProjectile.location] = '_';
                myProjectile.location = -1;
                myHero.canFire = 1;
                myEnemy.location = 200;
            }

            if (myProjectile.location > 18 || myProjectile.location < 0) {
                myProjectile.active = 0;
                myHero.canFire = 1;
            }
            else {
                map[myProjectile.location] = '*';
            }
        }

        if (myEnemy.alive) {
            map[myEnemy.location] = '_';
            if (myEnemy.direction) {
                myEnemy.location += 1;
            }
            else {
                myEnemy.location -= 1;
            }

            //check if projectil y malote chocan
            if (myEnemy.location == myProjectile.location) {
                myProjectile.active = 0;
                myEnemy.alive = 0;
                map[myProjectile.location] = '_';
                myProjectile.location = -1;
                myHero.canFire = 1;
            }
            else {
                map[myEnemy.location] = 'H';
            }
            //check if malote y jugador chocan
            if (myEnemy.location == myHero.location) {
                exit(0);
            }
        }
        else {
            if (myEnemy.direction) {
                myEnemy.location = 0;
            }
            else {
                myEnemy.location = 18;
            }
            myEnemy.alive = 1;
            map[myEnemy.location] = 'H';
        }

        map[myHero.location] = 'A';
        
        
        printf(map);
        Sleep(200);
    }

    return 0;
}



class MyMap
{
public:
    char map[50] = "_________________________________________________";
    int max = 48;
};

class MyMalote {
public:
    int location = 0;
    int direction= 0;
    bool active = 0;
};

class MyHero
{
public:
    int location = 10;
    int direction = 0;
    bool canFire = 1;
};

class MyBullet
{
public:
    int location = 0;
    int direction = 0;
    bool fired = 0;
};


void endGame() {
    //clear the console
    system("CLS");
    // launch endgame msg with a time stamp
    printf("END OF GAME...");
    Sleep(1000);
    // exit game
    exit(0);
}


int moveItem(int location, int direction) {
    // receives a location and direction and returns the next location
    if (direction)
    {
        location += 1;
    }
    else
    {
        location -= 1;
    }
    return location;
}


void moveHero(MyHero& elBueno, MyMap& elMapa) {
    //move left
    if (GetKeyState('A') & 0x8000) 
    {
        if (elBueno.location > 0) 
        {
            elBueno.location -= 1;
        }
        elBueno.direction = 0;
    }
    //move right
    if (GetKeyState('D') & 0x8000) 
    {
        if (elBueno.location < elMapa.max - 1) 
        {
            elBueno.location += 1;
        }
        elBueno.direction = 1;
    }
    elMapa.map[elBueno.location] = 'A';
}


void checkHits(MyHero& elBueno, MyMalote(&malotes)[5], int arraySize) {

    // loop all the array to check locations from hero to enemy
    for (int i = 0; i < arraySize; ++i)
    {
        if (elBueno.location == malotes[i].location && malotes[i].active)
        {   
            // if true go to endgame function
            endGame();
        }
    }

}


void checkBullets(MyBullet(&bullets)[6], int clipSize, MyMalote(&malotes)[5], int arraySize, MyMap& elMapa) {

    for (int i = 0; i < arraySize; ++i) {
        if (malotes[i].active) {
            for (int k = 0; k < clipSize; ++k) {
                if (bullets[k].location == malotes[i].location && bullets[k].fired)
                {
                    bullets[k].fired = 0;
                    malotes[i].active = 0;
                    elMapa.map[bullets[k].location] = '_';
                }
            }
        }
    }

}

void moveBullets(MyHero& elBueno, MyBullet(&bullets)[6], int clipSize, MyMap& elMapa) {

    // first we check if player is firing
    bool shoot = 0;
    if (GetKeyState('X') & 0x8000)
    {
        shoot = 1;
    }

    // only will fire if firing and there are available bullets
    for (int i = 0; i < clipSize; ++i)
    {   
        // if bullet is fired then move it
        if (bullets[i].fired)
        {
            bullets[i].location = moveItem(bullets[i].location, bullets[i].direction);
            //if bullet is out of map limits then deactivate it
            if (bullets[i].location < elMapa.max && bullets[i].location >= 0)
            {   
                //if valid then print it in map
                elMapa.map[bullets[i].location] = '*';
            }
            else 
            {
                bullets[i].fired = 0;
            }
        }
        else if (shoot)
        {
            // when firing a bullet we block firing and set the bullets values
            shoot = 0;
            bullets[i].fired = 1;
            bullets[i].direction = elBueno.direction;
            bullets[i].location = moveItem(elBueno.location, bullets[i].direction);
            elMapa.map[bullets[i].location] = '*';
        }
    }
}


bool getRandomBoolean() {
    // Use random_device to generate a seed for the random number generator
    std::random_device rd;

    // Use the Mersenne Twister algorithm for random number generation
    std::mt19937 gen(rd());

    // Use the uniform distribution to generate a random boolean value
    std::uniform_int_distribution<> dis(0, 1);

    // Return the randomly generated boolean value
    return dis(gen) == 1;
}


void moveEnemies(MyMalote(&malotes)[5], int arraySize, MyMap& elMapa, int& spawner) {
    //we only spawn one per 4 frames using spawner
    //for all that are active we check new location
    for (int i = 0; i < arraySize; ++i) 
    {   
        // only move the active enemies
        if (malotes[i].active) {
            malotes[i].location = moveItem(malotes[i].location, malotes[i].direction);
            elMapa.map[malotes[i].location] = 'H';
        }
        // select the firt inactive if spawner is ready for spawn
        else if(spawner <= 0)
        {   
            spawner = 6;
            // the spawn occurs in one random edge of the map
            malotes[i].active = 1;
            malotes[i].direction = getRandomBoolean();
            // direction is dependant of the spawn location
            if (malotes[i].direction) 
            {
                malotes[i].location = 0;
            }
            else 
            {
                malotes[i].location = elMapa.max;
            }
            
        }
    }

}


void resetMap(MyMap& elMapa) {
    //put all the chars to _ for map setting later
    for (int i = 0; i < elMapa.max + 1; ++i) 
    {
        elMapa.map[i] = '_';
    }
}


int main(){
    //definimos el hero
    MyHero elBueno = MyHero();

    //definimos el mapa
    MyMap mapa = MyMap();

    // definimos los malotes
    const int arraySize = 5;
    MyMalote malotes[arraySize];

    for (int i = 0; i < arraySize; ++i) {
        // You can customize the initial values as needed
        malotes[i] = MyMalote();
    }

    // definimos el cargador de balas
    const int clipSize = 6;
    MyBullet bullets[clipSize];


    for (int i = 0; i < clipSize; ++i) {
        // You can customize the initial values as needed
        bullets[i] = MyBullet();
    }

    // spawn enemy every 6 frames
    int spawner = 6;

    while (true) {
        
        system("CLS");
        resetMap(mapa);
        //hero movement control
        moveHero(elBueno, mapa);
        // check if hero hits with any malote and if hit end game
        checkHits(elBueno, malotes, arraySize);
        //fire hero control
        moveBullets(elBueno, bullets, clipSize, mapa);
        // check if any bullets have collided with any enemies
        checkBullets(bullets, clipSize, malotes, arraySize, mapa);
        //move all enemies control
        moveEnemies(malotes, arraySize, mapa, spawner);
        // check if any bullets have collided with any enemies
        checkBullets(bullets, clipSize, malotes, arraySize, mapa);
        // check for enemy hits with hero
        checkHits(elBueno, malotes, arraySize);
        //update the map with all the new cosos
        printf(mapa.map);
        Sleep(200);

        // enemy spawn control to stop overcrowd
        if (spawner > 0)
        {
            spawner -= 1;
        }
    }
}