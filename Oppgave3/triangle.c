#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "triangle.h"
#include "drawline.h"

#define TRIANGLE_PENCOLOR   0xBBBB0000

/*
 * Print triangle coordinates along with a message
 */
void print_triangle(triangle_t *triangle, char *msg)
{
    printf("%s: %d,%d - %d,%d - %d,%d\n",
        msg,
        triangle->x1, triangle->y1,
        triangle->x2, triangle->y2,
        triangle->x3, triangle->y3);
}

/*
 * Return 0 if triangle coordinates are outside the surface boundary. 1 otherwise.
 */
int sanity_check_triangle(SDL_Surface *surface, triangle_t *triangle)
{
    if (triangle->sx1 < 0 || triangle->sx1 >= surface->w ||
        triangle->sx2 < 0 || triangle->sx2 >= surface->w ||
        triangle->sx3 < 0 || triangle->sx3 >= surface->w ||
        triangle->sy1 < 0 || triangle->sy1 >= surface->h ||
        triangle->sy2 < 0 || triangle->sy2 >= surface->h ||
        triangle->sy3 < 0 || triangle->sy3 >= surface->h) {
        return 0;
    } else {
        return 1;
    }
}

/*
 * Scale triangle, altering the on-screen coordinates(e.g. triangle->sx1)
 */
void scale_triangle(triangle_t *triangle)
{

    // TODO: Replace the code below with code that scales each triangle coordinate.
    // The scaling factor is specified in triangle->scale.
    // Remember that this function MUST write to the on-surface coordinates.
    // Do not alter the model coordinates.æ

    triangle->sx1 = triangle->x1 * triangle->scale;
    triangle->sy1 = triangle->y1 * triangle->scale;

    triangle->sx2 = triangle->x2 * triangle->scale;
    triangle->sy2 = triangle->y2 * triangle->scale;

    triangle->sx3 = triangle->x3 * triangle->scale;
    triangle->sy3 = triangle->y3 * triangle->scale;
}

/*
 * Move the triangle to the center of the surface,
 * altering the on-screen coordinates(e.g. triangle->sx1)
 */
void translate_triangle(triangle_t *triangle)
{
    // TODO: Insert code that moves the triangle on the surface.
    // The translation coordinates are specified in triangle->tx and triangle->ty.
    // Remember to use the on-surface coordinates (triangle->sx1, etc.)
    //triangle->tx = (triangle->sx1+triangle->sx2+triangle->sx3)/3;
  //  triangle->ty = (triangle->sy1+triangle->sy2+triangle->sy3)/3;
    //printf("x er %d og y er %d\n",triangle->tx,triangle->ty );
    triangle->tx = 600;
    triangle->ty = 600;
    triangle->sx1 += triangle->tx;
    triangle->sy1 += triangle->ty;

    triangle->sx2 += triangle->tx;
    triangle->sy2 += triangle->ty;

    triangle->sx3 += triangle->tx;
    triangle->sy3 += triangle->ty;

}

/*
 * Calculate the triangle bounding box,
 * altering fields of the triangle's rect(e.g. triangle->rect.x)
 */
void calculate_triangle_bounding_box(triangle_t *triangle)
{
    triangle->rect.x = 1600;
    triangle->rect.y = 1600;
    triangle->rect.w = -600;
    triangle->rect.h = -600;
    // TODO: Insert code that calculates the bounding box of a triangle.
    // Remember to use the on-surface coordinates (triangle->sx1, etc.)
    // The bounding box coordinates should be written to
    // triangle->rect.x, triangle->rect.y, triangle->rect.w, triangle->rect.h

    //Finds through all x points and sets the rect.x to the lowest one
    //Does the samething for rect.y and opposite for rect.w and rect.h

    //For loop that increases surface coordinate each cycle
    /*
    int *sx = &triangle->sx1;
    printf("%d\n", *sx);
    int *sy = &triangle->sy1;
    for (int i = 0; i < 3; i++) {
      if (*sx < triangle->rect.x) {
        triangle->rect.x = *sx;
      }

      if (*sy < triangle->rect.y) {
        triangle->rect.y = *sy;
      }

      if (*sy > triangle->rect.h) {
        triangle->rect.h = *sy;
      }

      if (*sx > triangle->rect.w) {
        triangle->rect.w = *sx;
      }
      //Counts up by one
      sx += sizeof(int);
      sy += sizeof(int);
    }
    triangle->rect.w = triangle->rect.w-triangle->rect.x;
    triangle->rect.h = triangle->rect.h-triangle->rect.y;*/
    if (triangle->sx1 < triangle->rect.x){triangle->rect.x = triangle->sx1;}
    if (triangle->sx2 < triangle->rect.x){triangle->rect.x = triangle->sx2;}
    if (triangle->sx3 < triangle->rect.x){triangle->rect.x = triangle->sx3;}

    if (triangle->sy1 < triangle->rect.y){triangle->rect.y = triangle->sy1;}
    if (triangle->sy2 < triangle->rect.y){triangle->rect.y = triangle->sy2;}
    if (triangle->sy3 < triangle->rect.y){triangle->rect.y = triangle->sy3;}

    if (triangle->sx1 > triangle->rect.w){triangle->rect.w = triangle->sx1;}
    if (triangle->sx2 > triangle->rect.w){triangle->rect.w = triangle->sx2;}
    if (triangle->sx3 > triangle->rect.w){triangle->rect.w = triangle->sx3;}

    if (triangle->sy1 > triangle->rect.h){triangle->rect.h = triangle->sy1;}
    if (triangle->sy2 > triangle->rect.h){triangle->rect.h = triangle->sy2;}
    if (triangle->sy3 > triangle->rect.h){triangle->rect.h = triangle->sy3;}

    triangle->rect.w = triangle->rect.w-triangle->rect.x;
    triangle->rect.h = triangle->rect.h-triangle->rect.y;
}

/*
 * Fill the triangle on the surface with the triangle's color
 */




void fill_triangle(SDL_Surface *surface, triangle_t *triangle, int x, int y)
{
    // TODO: Insert code that fills the triangle with the color specified in triangle->fillcolor.
    // Hint: Draw the triangle with color TRIANGLE_PENCOLOR (this color can not
    // occur in e.g. the teapot or the example triangles).  Thus, if your
    // approach to filling the triangle relies on looking for the edges of
    // the triangle on the surface (via the GetPixel function), you will find those
    // edges even if the triangle overlaps with a triangle that has already
    // been drawn on the surface
    //Full første hjørne
    /*
    if (x<triangle->rect.x+triangle->rect.w && y<triangle->rect.y+triangle->rect.h) {
      if(get_pixel(surface,x, y) != TRIANGLE_PENCOLOR &&
           get_pixel(surface,x, y) != triangle->fillcolor)
        {
            set_pixel(surface,x, y, triangle->fillcolor);
            fill_triangle(surface,triangle,x + 1, y);
            fill_triangle(surface,triangle,x, y + 1);
            fill_triangle(surface,triangle,x - 1, y);
            fill_triangle(surface,triangle,x, y - 1);
        }
    }*/

    for (int i = 0; i < 15; i++) {
        set_pixel(surface,x+i,y,triangle->fillcolor);
    }






}

int halfnumber(int i){
  int resultat = i/2;
  return resultat;
}
/*
 * Draw a filled triangle on the given surface
 */
void draw_triangle(SDL_Surface *surface, triangle_t *triangle)
{
    int isOK;


    /* Scale. */
    scale_triangle(triangle);

    /* Translate. */
    translate_triangle(triangle);

    /* Determine bounding box */
    calculate_triangle_bounding_box(triangle);

    /* Sanity check that triangle is within surface boundaries. */
    isOK = sanity_check_triangle(surface, triangle);
    if (!isOK) {
        print_triangle(triangle, "Triangle outside surface boundaries");
        return;
    }

    /*
     * TODO: Insert calls to draw_line to draw the triangle.
     * Remember to use the on-surface coordinates (triangle->sx1, etc.)
     */
     draw_line(surface,triangle->sx1,triangle->sy1,triangle->sx2,triangle->sy2,TRIANGLE_PENCOLOR);
     draw_line(surface,triangle->sx2,triangle->sy2,triangle->sx3,triangle->sy3,TRIANGLE_PENCOLOR);
     draw_line(surface,triangle->sx3,triangle->sy3,triangle->sx1,triangle->sy1,TRIANGLE_PENCOLOR);

    /* Fill triangle */
    int sendx = triangle->sx1+halfnumber(triangle->rect.h);
    int sendy = triangle->sy1+halfnumber(triangle->rect.h);
    fill_triangle(surface, triangle,sendx,sendy);
}
