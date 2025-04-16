/*
Continuous Cellular Automaton using the Empirical Toolkit (emp-toolkit). 
Exploring rules that bias the north/east direction using a non-linear function.
*/

#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

emp::web::Document doc{"target"};

class CAAnimator : public emp::web::Animate {

    const int num_h_boxes = 10;
    const int num_w_boxes = 15;
    const double RECT_SIDE = 25;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};
    int update_count = 0;

    std::vector<std::vector<float>> cells;
    emp::web::Canvas canvas{width, height, "canvas"};

public:

    CAAnimator() {
        /*Constructor to initialize grid and cells*/
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        // Initialize cell grid with zeros
        cells.resize(num_w_boxes, std::vector<float>(num_h_boxes, 0));

        // Set initial configuration
        InitializeCells();
    }

    void DoFrame() override {
        /*Our update step that loops over all the cells, updates their values based on their neighbours,
         and draws the new state of the cells*/
         
        canvas.Clear();

        // Create new grid to hold next state
        std::vector<std::vector<float>> new_cells = cells;

        if (update_count != 0) {
            UpdateCells(new_cells);
        }

        // Draw updated cells
        cells = new_cells;
        DrawCells();
        update_count++;
    }

private:

    void InitializeCells() {
        /*Sets up the initial state on the grid*/

        //Initial state. Starts small, expands into stable-ish pattern
        /* cells[5][2] = 1;
        cells[4][2] = 1;
        cells[6][2] = 1;
        cells[5][3] = 1;
        cells[6][3] = 1;
        cells[7][3] = 1;
        cells[7][4] = 1; */

        // Other states for testing
        cells[5][5] = 1.0;
        cells[6][4] = 1.0;
        cells[7][3] = 1.0; 


        // Circle initial state
        /*
        cells[5][1] = 1;
        cells[5][2] = 1;
        cells[5][3] = 1;
        cells[6][1] = 1;
        cells[6][3] = 1;
        cells[7][1] = 1;
        cells[7][2] = 1;
        cells[7][3] = 1;
        */
    }

    void UpdateCells(std::vector<std::vector<float>>& new_cells) {
        /*Iterates through the cells, updating their values based on their neighbours*/
        for (int x = 0; x < num_w_boxes; x++) {
            for (int y = 0; y < num_h_boxes; y++) {
                float sum = 0.0;
                int num_neighbors = 0;

                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (dx == 0 && dy == 0) continue;

                        int nx = emp::Mod(x + dx, num_w_boxes);
                        int ny = emp::Mod(y + dy, num_h_boxes);

                        if ((dx == 0 && dy == -1) || (dx == 1 && dy == 0)) { // only north and east neighbors contribute
                            sum += cells[nx][ny];
                        }

                        if (cells[nx][ny] > 0.5) {
                            num_neighbors++;
                        }
                    }
                }

                float updated_value = 1.0 / (1.0 + exp(-3.0 * (sum - 1.0)));
                if (num_neighbors == 1) {
                    updated_value = 1.0; // override if exactly one strong active neighbor
                }

                new_cells[x][y] = updated_value;
            }
        }
    }

    void DrawCells() {
        /*Draws the cells on the canvas*/
        for (int x = 0; x < num_w_boxes; x++) {
            for (int y = 0; y < num_h_boxes; y++) {
                float b = 1.0 - cells[x][y];
                canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE,
                            emp::ColorHSV(0, 0, b), "black");
            }
        }
    }

};

CAAnimator animator;

int main() {
    animator.Step(); 
}
