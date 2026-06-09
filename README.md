# 2D Graphics Editor in C

## Project Description

This project is a menu-driven 2D Graphics Editor implemented in C using a 2D character array as the drawing canvas. The canvas is initialized with underscore (`_`) characters, and graphical objects are drawn using asterisk (`*`) characters.

The editor allows users to add, delete, modify, and display graphical objects such as rectangles, lines, triangles, and circles.

---

## Features

- 2D Character Array Canvas
- Draw Rectangle
- Draw Line
- Draw Triangle
- Draw Circle
- Add Objects
- Delete Objects
- Modify Objects
- Display Canvas
- Object ID Management
- Menu-Driven Interface

---

## Data Structures Used

### Canvas

```c
char canvas[ROWS][COLS];
```

### Shape Structure

```c
typedef struct
{
    int id;
    int active;
    int type;
    int p[8];
} Shape;
```

---

## Algorithms Used

### 1. Bresenham Line Drawing Algorithm

Used to draw lines efficiently between two points.

### 2. Midpoint Circle Algorithm

Used to draw circles with integer arithmetic.

---

## Supported Shapes

### Rectangle

Input:
- Starting Row
- Starting Column
- Width
- Height

### Line

Input:
- (x1, y1)
- (x2, y2)

### Triangle

Input:
- (x1, y1)
- (x2, y2)
- (x3, y3)

### Circle

Input:
- Center Row
- Center Column
- Radius

---

## Menu Options

1. Add Rectangle
2. Add Line
3. Add Triangle
4. Add Circle
5. Display Canvas
6. List Objects
7. Delete Object
8. Modify Object
9. Exit

---

## Compilation

Compile using GCC:

```bash
gcc graphics_editor.c -o editor
```

---

## Execution

Run the program:

```bash
./editor
```

---

## Sample Output

```text
===================================
      2D GRAPHICS EDITOR
===================================
1. Add Rectangle
2. Add Line
3. Add Triangle
4. Add Circle
5. Display Canvas
6. List Objects
7. Delete Object
8. Modify Object
9. Exit
Choice:
```

---

## Project Workflow

1. Create an empty canvas.
2. Add graphical objects.
3. Store objects using structures.
4. Redraw the canvas whenever an object is modified or deleted.
5. Display the updated drawing.

---

## Learning Outcomes

- Arrays and 2D Arrays
- Structures
- Functions
- Graphics Algorithms
- Menu-Driven Programming
- Object Management
- C Programming Concepts

---

## Future Enhancements

- Save Drawing to File
- Load Drawing from File
- ncurses-Based Interface
- Undo/Redo Operations
- Object Movement
- Colored Shapes
- Export Canvas

---

## Author

**Name:** O. Bhavishya Lakshmi

**USN/Roll Number:** R25EH082

**Course:** C Programming Laboratory

---

## License

This project is created for academic and educational purposes.
