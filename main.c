#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ROWS 40
#define COLS 80
#define MAX_OBJECTS 100

char canvas[ROWS][COLS];

typedef enum
{
    RECTANGLE = 1,
    LINE,
    TRIANGLE,
    CIRCLE
} ShapeType;

typedef struct
{
    int id;
    int active;
    ShapeType type;

    int p[8];
} Shape;

Shape shapes[MAX_OBJECTS];
int shapeCount = 0;
int nextID = 1;

/* ---------------- CANVAS ---------------- */

void initializeCanvas()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    printf("\n");

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

void plot(int x, int y)
{
    if (x >= 0 && x < ROWS && y >= 0 && y < COLS)
    {
        canvas[x][y] = '*';
    }
}

/* ---------------- DRAWING FUNCTIONS ---------------- */

void drawLineCanvas(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (1)
    {
        plot(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void drawRectangleCanvas(int x, int y, int width, int height)
{
    for (int i = x; i < x + height; i++)
    {
        for (int j = y; j < y + width; j++)
        {
            plot(i, j);
        }
    }
}

void drawTriangleCanvas(
    int x1, int y1,
    int x2, int y2,
    int x3, int y3)
{
    drawLineCanvas(x1, y1, x2, y2);
    drawLineCanvas(x2, y2, x3, y3);
    drawLineCanvas(x3, y3, x1, y1);
}

void drawCircleCanvas(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int d = 1 - r;

    while (x <= y)
    {
        plot(xc + x, yc + y);
        plot(xc - x, yc + y);
        plot(xc + x, yc - y);
        plot(xc - x, yc - y);

        plot(xc + y, yc + x);
        plot(xc - y, yc + x);
        plot(xc + y, yc - x);
        plot(xc - y, yc - x);

        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }

        x++;
    }
}

/* ---------------- SHAPE MANAGEMENT ---------------- */

void drawShape(Shape s)
{
    switch (s.type)
    {
        case RECTANGLE:
            drawRectangleCanvas(
                s.p[0],
                s.p[1],
                s.p[2],
                s.p[3]);
            break;

        case LINE:
            drawLineCanvas(
                s.p[0],
                s.p[1],
                s.p[2],
                s.p[3]);
            break;

        case TRIANGLE:
            drawTriangleCanvas(
                s.p[0],
                s.p[1],
                s.p[2],
                s.p[3],
                s.p[4],
                s.p[5]);
            break;

        case CIRCLE:
            drawCircleCanvas(
                s.p[0],
                s.p[1],
                s.p[2]);
            break;
    }
}

void redrawCanvas()
{
    initializeCanvas();

    for (int i = 0; i < shapeCount; i++)
    {
        if (shapes[i].active)
        {
            drawShape(shapes[i]);
        }
    }
}

void listObjects()
{
    printf("\nObjects:\n");

    for (int i = 0; i < shapeCount; i++)
    {
        if (shapes[i].active)
        {
            printf("ID: %d  Type: ", shapes[i].id);

            switch (shapes[i].type)
            {
                case RECTANGLE:
                    printf("Rectangle");
                    break;

                case LINE:
                    printf("Line");
                    break;

                case TRIANGLE:
                    printf("Triangle");
                    break;

                case CIRCLE:
                    printf("Circle");
                    break;
            }

            printf("\n");
        }
    }
}

int findShape(int id)
{
    for (int i = 0; i < shapeCount; i++)
    {
        if (shapes[i].id == id && shapes[i].active)
        {
            return i;
        }
    }

    return -1;
}

/* ---------------- ADD SHAPES ---------------- */

void addRectangle()
{
    Shape s;

    s.id = nextID++;
    s.active = 1;
    s.type = RECTANGLE;

    printf("Top Row: ");
    scanf("%d", &s.p[0]);

    printf("Left Column: ");
    scanf("%d", &s.p[1]);

    printf("Width: ");
    scanf("%d", &s.p[2]);

    printf("Height: ");
    scanf("%d", &s.p[3]);

    shapes[shapeCount++] = s;

    redrawCanvas();

    printf("Rectangle Added. ID = %d\n", s.id);
}

void addLine()
{
    Shape s;

    s.id = nextID++;
    s.active = 1;
    s.type = LINE;

    printf("x1 y1: ");
    scanf("%d %d", &s.p[0], &s.p[1]);

    printf("x2 y2: ");
    scanf("%d %d", &s.p[2], &s.p[3]);

    shapes[shapeCount++] = s;

    redrawCanvas();

    printf("Line Added. ID = %d\n", s.id);
}

void addTriangle()
{
    Shape s;

    s.id = nextID++;
    s.active = 1;
    s.type = TRIANGLE;

    printf("x1 y1: ");
    scanf("%d %d", &s.p[0], &s.p[1]);

    printf("x2 y2: ");
    scanf("%d %d", &s.p[2], &s.p[3]);

    printf("x3 y3: ");
    scanf("%d %d", &s.p[4], &s.p[5]);

    shapes[shapeCount++] = s;

    redrawCanvas();

    printf("Triangle Added. ID = %d\n", s.id);
}

void addCircle()
{
    Shape s;

    s.id = nextID++;
    s.active = 1;
    s.type = CIRCLE;

    printf("Center Row: ");
    scanf("%d", &s.p[0]);

    printf("Center Column: ");
    scanf("%d", &s.p[1]);

    printf("Radius: ");
    scanf("%d", &s.p[2]);

    shapes[shapeCount++] = s;

    redrawCanvas();

    printf("Circle Added. ID = %d\n", s.id);
}

/* ---------------- DELETE ---------------- */

void deleteObject()
{
    int id;

    listObjects();

    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    int index = findShape(id);

    if (index == -1)
    {
        printf("Object not found.\n");
        return;
    }

    shapes[index].active = 0;

    redrawCanvas();

    printf("Object deleted.\n");
}

/* ---------------- MODIFY ---------------- */

void modifyObject()
{
    int id;

    listObjects();

    printf("\nEnter ID to modify: ");
    scanf("%d", &id);

    int index = findShape(id);

    if (index == -1)
    {
        printf("Object not found.\n");
        return;
    }

    Shape *s = &shapes[index];

    switch (s->type)
    {
        case RECTANGLE:

            printf("New Row: ");
            scanf("%d", &s->p[0]);

            printf("New Column: ");
            scanf("%d", &s->p[1]);

            printf("New Width: ");
            scanf("%d", &s->p[2]);

            printf("New Height: ");
            scanf("%d", &s->p[3]);
            break;

        case LINE:

            printf("New x1 y1: ");
            scanf("%d %d", &s->p[0], &s->p[1]);

            printf("New x2 y2: ");
            scanf("%d %d", &s->p[2], &s->p[3]);
            break;

        case TRIANGLE:

            printf("New x1 y1: ");
            scanf("%d %d", &s->p[0], &s->p[1]);

            printf("New x2 y2: ");
            scanf("%d %d", &s->p[2], &s->p[3]);

            printf("New x3 y3: ");
            scanf("%d %d", &s->p[4], &s->p[5]);
            break;

        case CIRCLE:

            printf("New Center Row: ");
            scanf("%d", &s->p[0]);

            printf("New Center Column: ");
            scanf("%d", &s->p[1]);

            printf("New Radius: ");
            scanf("%d", &s->p[2]);
            break;
    }

    redrawCanvas();

    printf("Object modified.\n");
}

/* ---------------- MAIN ---------------- */

int main()
{
    initializeCanvas();

    int choice;

    while (1)
    {
        printf("\n");
        printf("===================================\n");
        printf("      2D GRAPHICS EDITOR\n");
        printf("===================================\n");
        printf("1. Add Rectangle\n");
        printf("2. Add Line\n");
        printf("3. Add Triangle\n");
        printf("4. Add Circle\n");
        printf("5. Display Canvas\n");
        printf("6. List Objects\n");
        printf("7. Delete Object\n");
        printf("8. Modify Object\n");
        printf("9. Exit\n");
        printf("Choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addRectangle();
                break;

            case 2:
                addLine();
                break;

            case 3:
                addTriangle();
                break;

            case 4:
                addCircle();
                break;

            case 5:
                displayCanvas();
                break;

            case 6:
                listObjects();
                break;

            case 7:
                deleteObject();
                break;

            case 8:
                modifyObject();
                break;

            case 9:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
