#include <stdio.h>
#include "color.h"
#include "tile.h"
#include <string.h>
#define MAX_STR 100

struct color{
  const char name[MAX_STR];
  const char code[MAX_STR];
};

struct color Black={{"Black"},{"\\u001b[30m"}};
struct color Red={{"Red"},{"\\u001b[31m"}};
struct color Green={{"GREEN"},{"\\u001b[32m"}};
struct color Yellow={{"YELLOW"},{"\\u001b[33m"}};
struct color Blue={{"BLUE"},{"\\u001b[34m"}};
struct color White={{"WHITE"},{"\\u001b[37m"}};

static struct color *colors_table[6]={&Black,&Red,&Green,&Yellow,&Blue,&White};

// A string giving the color name
const char* color_name(struct color* t){
  return t->name;
}

// An ANSI-colored string describing the color
const char* color_cstring(struct color* t){
  return t->code;
}

// Return a color from its name, or NULL
struct color* color_from_name(const char* name)
{
  for (int i=0;i<6;i++)
    {
      if (!strcmp(name,(colors_table[i])->name))
	    return colors_table[i];
    }
  return NULL;
}
