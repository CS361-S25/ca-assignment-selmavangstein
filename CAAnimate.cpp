/*
This program implements a simple cellular automaton (CA) using the emp-toolkit.
The program uses the rules of Conways Game of Life to update the state of the cells.
It implements the lightweight rocket ship pattern as the initial state, found at https://conwaylife.com/wiki/Lightweight_spaceship
*/

#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

emp::web::Document doc{"target"};

class CAAnimator : public emp::web::Animate {

// grid width and height
const int num_h_boxes = 10;
const int num_w_boxes = 15;
const double RECT_SIDE = 25;
const double width{num_w_boxes * RECT_SIDE};
const double height{num_h_boxes * RECT_SIDE};
int update_count = 0;


//some vectors to hold information about the CA
std::vector<std::vector<int> > cells;
        

// where we'll draw
emp::web::Canvas canvas{width, height, "canvas"};

public:

    CAAnimator() {
        // shove canvas into the div
        // along with some control buttons
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        //fill the vectors with 0 to start
        cells.resize(num_w_boxes, std::vector<int>(num_h_boxes, 0));

        //set initial state of the cells here - og glider pattern
        /* cells[2][4] = 1;
        cells[3][4] = 1;
        cells[4][4] = 1;
        cells[4][3] = 1;
        cells[3][2] = 1; */

        //lightweight rocket ship
        cells[2][2] = 1;
        cells[5][2] = 1;
        cells[1][3] = 1;
        cells[1][4] = 1;
        cells[1][5] = 1;
        cells[2][5] = 1;
        cells[3][5] = 1;
        cells[4][5] = 1;
        cells[5][4] = 1;

        
    }

    void DoFrame() override {
        canvas.Clear();

        //copy cell structure to keep track of the current state
        std::vector<std::vector<int> > old_cells = cells;

        //iterate through the cells
        for (int x = 0; x < num_w_boxes; x++){
            for (int y = 0; y < num_h_boxes; y++) {
                //check the neighbors of each cell
                int num_neighbors = 0;
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (dx == 0 && dy == 0) continue;
                        int nx = emp::Mod(x + dx, num_w_boxes);
                        int ny = emp::Mod(y + dy, num_h_boxes);
                        if (old_cells[nx][ny] == 1) {
                            num_neighbors++;
                        }
                    }
                }

                if (update_count != 0){
                    //apply rules of the CA
                    if (old_cells[x][y] == 1) {
                        if (num_neighbors < 2 || num_neighbors > 3) {
                            cells[x][y] = 0;
                        }
                    } else {
                        if (num_neighbors == 3) {
                            cells[x][y] = 1;
                        }
                    }
                }
            }
        }

        //redraw the cells
        for (int x = 0; x < num_w_boxes; x++){
             for (int y = 0; y < num_h_boxes; y++) {

                if (cells[x][y] == 0) {
                    //Draw a rectangle on the canvas filled with white and outlined in black
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
                } else {
                    //Draw a rectangle filled with black
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "black");
                }
                
            }
        }
        update_count++;
    }

};

CAAnimator animator;

int main() {
    //Have animator call DoFrame once to start
    animator.Step();
}