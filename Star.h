// Star.h

#ifndef STAR_H
#define STAR_H
extern float star_coords[5][3];
extern bool star_collected[5];

void loadStar();
void renderStar(float translate_x,float translate_y, float translate_z);
void renderStars();

#endif // STAR_H
