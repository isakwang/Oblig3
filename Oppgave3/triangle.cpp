#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "triangle.h"
#include "drawline.h"
#include "graphics.h"

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
    // Do not alter the model coordinates.
    triangle->sx1 = triangle->x1 * triangle->scale;
    triangle->sy1 = triangle->y1 * triangle->scale;
    printf("scaled %d non scaled %d\n",triangle->sx1, triangle->x1 );

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
    triangle->tx = (triangle->sx1+triangle->sx2+triangle->sx3)/3;
    triangle->ty = (triangle->sy1+triangle->sy2+triangle->sy3)/3;
    printf("x er %d og y er %d\n",triangle->tx,triangle->ty );
}

/*
 * Calculate the triangle bounding box,
 * altering fields of the triangle's rect(e.g. triangle->rect.x)
 */
void calculate_triangle_bounding_box(triangle_t *triangle)
{
    triangle->rect.x = 1600;
    triangle->rect.y = 1600;
    triangle->rect.w = 0;
    triangle->rect.h = 0;
    // TODO: Insert code that calculates the bounding box of a triangle.
    // Remember to use the on-surface coordinates (triangle->sx1, etc.)
    // The bounding box coordinates should be written to
    // triangle->rect.x, triangle->rect.y, triangle->rect.w, triangle->rect.h

    if(triangle->sx1 < triangle->rect.x){
      triangle->rect.x = triangle->sx1;
    }

    if(triangle->sx2 < triangle->rect.x){
      triangle->rect.x = triangle->sx2;
    }

    if(triangle->sx3 < triangle->rect.x){
      triangle->rect.x = triangle->sx3;
    }

    if(triangle->sy1 < triangle->rect.y){
      triangle->rect.y = triangle->sy1;
    }

    if(triangle->sy2 < triangle->rect.y){
      triangle->rect.y = triangle->sy2;
    }

    if(triangle->sy3 < triangle->rect.y){
      triangle->rect.y = triangle->sy3;
    }





    if(triangle->sx1 > triangle->rect.w){
      triangle->rect.w = triangle->sx1;
    }

    if(triangle->sx2 > triangle->rect.w){
      triangle->rect.w = triangle->sx2;
    }

    if(triangle->sx3 > triangle->rect.w){
      triangle->rect.w = triangle->sx3;
    }

    if(triangle->sy1 > triangle->rect.h){
      triangle->rect.h = triangle->sy1;
    }

    if(triangle->sy2 > triangle->rect.h){
      triangle->rect.h = triangle->sy2;
    }

    if(triangle->sy3 > triangle->rect.h){
      triangle->rect.h = triangle->sy3;
    }

    triangle->rect.w -= triangle->rect.x;
    triangle->rect.h -= triangle->rect.y;


}

/*
 * Fill the triangle on the surface with the triangle's color
 */
void fill_triangle(SDL_Surface *surface, triangle_t *triangle)
{
    // TODO: Insert code that fills the triangle with the color specified in triangle->fillcolor.
    // Hint: Draw the triangle with color TRIANGLE_PENCOLOR (this color can not
    // occur in e.g. the teapot or the example triangles).  Thus, if your
    // approach to filling the triangle relies on looking for the edges of
    // the triangle on the surface (via the GetPixel function), you will find those
    // edges even if the triangle overlaps with a triangle that has already
    // been drawn on the surface.
    int x = triangle->rect.x;
    int y = triangle->rect.y;
    while(GetPixel(x,y) != TRIANGLE_PENCOLOR){
      while(GetPixel(x,y) != TRIANGLE_PENCOLOR){
        putpixel(x,y,triangle->fillcolor);
        x++;
      }
      y++;
    }
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

    /* Fill triangle */
    fill_triangle(surface, triangle);
}
