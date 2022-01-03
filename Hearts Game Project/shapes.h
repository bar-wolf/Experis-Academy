#ifndef __SHAPES_H__
#define __SHAPES_H__

typedef enum
{
    CLAV,
    DIAMOND,
    HEART,
    PEAK,
    NUM_OF_SHAPES,
    
    JACK = 9,
    QUEEN,
    KING,
    ACE,
    NUM_OF_CARDS_AT_SHAPE         
}Shape;

#define CLAV_SHAPE(card)     card >= CLAV_2 && card <= CLAV_A 
#define DIAMOND_SHAPE(card)  card >= DIAMOND_2 && card <= DIAMOND_A
#define HEART_SHAPE(card)    card >= HEART_2 && card <= HEART_A
#define PEAK_SHAPE(card)     card >= PEAK_2 && card <= PEAK_A

#endif 


