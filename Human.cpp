// Human.cpp

#include "Human.h"
#include "Model_3DS.h"
#include "glut.h"
#include <cstdlib>  
#include <ctime>

Model_3DS model_human;

float human_coords[6][3] = {
    { 2.0f, 0.0f, -220.0f },
    { 0.0f, 0.0f, -225.0f },
    { 0.0f, 0.0f, -230.0f },
    { 2.0f, 0.0f, -240.0f },
    { -1.0f, 0.0f, -250.0f },
    { -1.0f, 0.0f, -255.0f }
};
bool human_collected = false;
int random_number = 0;
void loadHuman() {
    model_human.Load("Models/human/Raymond.3ds");
}

void renderHuman(int remainingTime) {
    if (human_collected) return;
    std::srand(static_cast<unsigned int>(std::time(0)));
    if (remainingTime == 0) {
        int prev = random_number;
        while(true){
        random_number = std::rand() % 6;
        if (random_number != prev)
            break;
        }
    }
   /* human_coords[0] = -2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 4.0f));
    human_coords[2] = -270.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 50.0f));*/


    glPushMatrix();
    glTranslatef(human_coords[random_number][0], human_coords[random_number][1], human_coords[random_number][2]);
    //glTranslatef(0, 0, -10);

    glScaled(0.2, 0.2, 0.2);
    model_human.Draw();
    glPopMatrix();
}


