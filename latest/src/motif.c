#include <stdio.h>
#include "motif.h"
#include "tile.h"
#include "color.h"


struct motif square()
{
    struct motif m1;
    struct color *b = color_from_name("BLACK");
    struct color *w = color_from_name("WHITE");
    m1.rank = 1;
    m1.distance = 1;
    m1.score_motif = 34;
    //m1.motiff = {{{{ b,b,b,b }},{{ b,w,b,b }},{{ b,b,b,b }}},
    //            {{{ b,b,w,b }},{{ w,w,w,w }},{{ b,b,b,w }}},
    //            {{{ b,b,b,b }},{{ w,b,b,b }},{{ b,b,b,b }}}};
    
    struct tile t2 = {{ b,w,b,b }};
    struct tile t4 = {{ b,b,w,b }};
    struct tile t5 = {{ w,w,w,w }};
    struct tile t6 = {{ b,b,b,w }};
    struct tile t1 = {{ b,b,b,b }}; // t1 , t3 , t7 , t9
    struct tile t8 = {{ w,b,b,b }};

    m1.motiff[0][0] = t1;
    m1.motiff[0][1] = t2;
    m1.motiff[0][2] = t1;
    m1.motiff[1][0] = t4;
    m1.motiff[1][1] = t5;
    m1.motiff[1][2] = t6;
    m1.motiff[2][0] = t1;
    m1.motiff[2][1] = t8;
    m1.motiff[2][2] = t1;
   
    
    return m1;
}

struct motif heart()
{
    struct motif m2;
    struct color *b = color_from_name("BLACK");
    struct color *w = color_from_name("White");
    m2.rank = 2;
    m2.distance = 1;
    m2.score_motif = 60;

    struct tile t1 = {{ b,w,w,b }};
    struct tile t2 = {{ b,w,w,w }};
    struct tile t3 = {{ b,w,b,w }};
    struct tile t4 = {{ w,b,w,b }};
    struct tile t5 = {{ w,w,w,w }};
    struct tile t6 = {{ w,b,b,w }};
    struct tile t7 = {{ b,b,b,b }};
    struct tile t8 = {{ w,b,b,b }};
    
    //m2.motiff = {{ t1 , t2 , t3 },
    //             { t4 , t5 , t6 },
    //             { t7 , t8 , t7 }};
    m2.motiff[0][0] = t1;
    m2.motiff[0][1] = t2;
    m2.motiff[0][2] = t3;
    m2.motiff[1][0] = t4;
    m2.motiff[1][1] = t5;
    m2.motiff[1][2] = t6;
    m2.motiff[2][0] = t7;
    m2.motiff[2][1] = t8;
    m2.motiff[2][2] = t7;
    return m2;
}


