#include <iostream>   // cout/cerr: print to console
#include <vector>     // std::vector to store the 2D grid
#include <string>     // std::string to hold each ASCII row
using namespace std;

// Represents a maze cell.
struct Node {
    int r = 0, c = 0;                  // coordinates (row, column) in the grid

    // Neighbor pointers (null if walled off):
    Node *up   = nullptr;
    Node *down = nullptr;
    Node *left = nullptr;
    Node *right= nullptr;

    // Wall flags relative to THIS cell: true = wall present, false = open.
    // N = north, S = south, E = east, W = west
    bool N = true, S = true, E = true, W = true;
};

// Helper: treat SPACE ' ' and STAR '*' characters as “open” (no wall).
// In your ASCII, '*' lies on the path; we ignore it while stripping walls.
static inline bool is_open_char(char ch) { return ch == ' ' || ch == '*'; }

/*
 * import_ascii_min
 * ----------------
 * Purpose: Parse an ASCII maze (may include '*') to produce:
 *  - an R x C grid 'g' of Node objects,
 *  - N,S,E,W wall flags for each node,
 *  - neighbor pointers (up/down/left/right) wherever openings exist.
 *
 * Input:
 *   a  : vector<string> containing ASCII maze rows.
 * Output:
 *   g  : R x C node grid (filled by reference)
 *   R,C: cell dimensions (returned by reference)
 * Returns:
 *   true on success; false on detectable format mismatch.
 */
bool import_ascii_min(vector<string> a, vector<vector<Node>>& g, int& R, int& C) {
    // 0) Trim leading rows that are entirely spaces (your example starts with one).
    while (!a.empty()) {
        bool all_spaces = true;
        for (char ch : a.front()) { if (ch != ' ') { all_spaces = false; break; } }
        if (all_spaces) a.erase(a.begin());
        else break;
    }
    // After trimming, we need at least the top border + one row.
    if (a.size() < 2) { cerr << "Input is too short.\n"; return false; }

    // 1) Derive dimensions from the top border (row 0).
    // Format guarantee: width = 1 + 2*C (leading space, then two chars per cell).
    const string& top = a[0];
    if (top.size() < 3) { cerr << "Top border is too short.\n"; return false; }
    C = (int(top.size()) - 1) / 2;         // number of columns (cells)
    R = (int)a.size() - 1;                 // number of rows (cells) = remaining lines

    // Verify each line has the expected width.
    for (int i = 1; i <= R; ++i) {
        if ((int)a[i].size() < 1 + 2*C) {
            cerr << "Row width mismatch: line " << i << ".\n";
            return false;
        }
    }

    // 2) Allocate the R x C grid of Nodes (value objects; addresses remain stable).
    g.assign(R, vector<Node>(C));
    // Initialize each node’s coordinates (r,c).
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j) { g[i][j].r = i; g[i][j].c = j; }

    // 3) Read NORTH walls of row 0 from the top border characters.
    // Rule: '_' at index 2+2*j denotes a NORTH wall; space/'*' is open.
    for (int j = 0; j < C; ++j) {
        char northCh = (2 + 2*j < (int)top.size() ? top[2 + 2*j] : ' ');
        g[0][j].N = (northCh == '_');
    }

    // 4) For each maze row, resolve WEST/SOUTH/EAST.
    // For i (0..R-1), the text line is a[i+1].
    // line[0]      => WEST wall of cell (i,0) ('|' => wall, ' ' or '*' => open)
    // line[1+2*j]  => SOUTH symbol of cell (i,j) ('_' => wall, ' ' or '*' => open)
    // line[2+2*j]  => EAST  symbol of cell (i,j) ('|' => wall, ' ' or '*' => open)
    // Consistency constraints:
    //   west(i,j)  = east(i,j-1)  (if j>0)
    //   north(i,j) = south(i-1,j) (if i>0)
    for (int i = 0; i < R; ++i) {
        const string& line = a[i+1];

        // WEST boundary of the first cell in this row:
        g[i][0].W = (line[0] == '|');

        // For each cell in this row:
        for (int j = 0; j < C; ++j) {
            char southCh = line[1 + 2*j];   // '_' => SOUTH wall present
            char eastCh  = line[2 + 2*j];   // '|' => EAST  wall present

            g[i][j].S = !is_open_char(southCh); // if not open, wall = true
            g[i][j].E = !is_open_char(eastCh);  // if not open, wall = true

            // Prevent conflicts by copying west/north walls from neighbors.
            if (j > 0) g[i][j].W = g[i][j-1].E; // west = east of left neighbor
            if (i > 0) g[i][j].N = g[i-1][j].S; // north = south of upper neighbor
        }
    }

    // 5) Create neighbor pointers where walls are open.
    // To avoid duplication, only establish RIGHT and DOWN links, then mirror them.
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (j+1 < C && !g[i][j].E) {        // east is open => link to (i,j+1)
                g[i][j].right   = &g[i][j+1];
                g[i][j+1].left  = &g[i][j];
            }
            if (i+1 < R && !g[i][j].S) {        // south is open => link to (i+1,j)
                g[i][j].down    = &g[i+1][j];
                g[i+1][j].up    = &g[i][j];
            }
        }
    }
    return true; // success
}

/*
 * print_clean_ascii_min
 * ---------------------
 * Purpose: Re-render the maze in the same ASCII format but WITHOUT any '*'.
 * Uses walls from g (N,S,E,W). This lets the user see a clean maze.
 */
void print_clean_ascii_min(const vector<vector<Node>>& g, int R, int C) {
    // Top border: print one leading space, then for each cell
    // print " _" if there is a north wall, otherwise "  ".
    cout << " ";
    for (int j = 0; j < C; ++j) cout << (g[0][j].N ? " _" : "  ");
    cout << "\n";

    // Each maze row:
    for (int i = 0; i < R; ++i) {
        // Left boundary: print '|' if the west wall of (i,0) exists, else space.
        cout << (g[i][0].W ? "|" : " ");
        // For each cell, print two characters: first the south symbol, then the east symbol.
        for (int j = 0; j < C; ++j) {
            cout << (g[i][j].S ? '_' : ' ')    // '_' if south wall, else space
                 << (g[i][j].E ? '|' : ' ');   // '|' if east wall, else space
        }
        cout << "\n";
    }
}

int main() {
    // Example input: your 15x27 maze with an initial line of spaces.
    const vector<string> ascii = {
        "-------------------------------------------------------",
        "   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ ",
        "|_ _ _ _ _ *| |  _ _ _   _ _|  _ _ _ * *|* _ _ _ _ *| |",
        "|  _ _  | |*|_  |_ _  |_ _ _ _|* _ _ _|_ _|_   _|* _| |",
        "| |_ _  | |_ *|_ _  |_   _  | |*| |    _ _  | |* _|  _|",
        "| |* *|_  | |*|_  |_ _ _|  _| |*|_  |_  |  _ _|_ *|_  |",
        "|* _|*| |_  |_ *|  _ _  | |  _|_ *| |  _|_  |* _ _|* *|",
        "|*| |*|_ _ _|* _| |_  |_ _|_ _  |*|_|   |_  |_ _ _ _|*|",
        "|_ *|_ _ _ _ _| |_  |   |    _ _|_ *| |_  |_|* _ * _|*|",
        "| |_ *|_ _   _ _ _| | |  _|_|* _ _ _|_|   |* _| |_ _ _|",
        "|* *|_ _ *| |   |  _ _|_|* _ _|* *|* * _|_|*|  _ _ _  |",
        "|*|_ * _|*|  _| | | |* *|*| |* _|_ _|_ *|* _|_|* _ *| |",
        "|_ *|_ _ _|_  | | | |*|_ _|* _|  _ _  |_ _|* _ _| |*| |",
        "|* _|_ _ * *|_|_ _ _|_ *|* _|  _ _ _|  _ _ *|* *|* _| |",
        "|_ _ *|* _|_ _ _ _ _ _ _|*|  _| |* *| |* _ _|*|_ _|* *|",
        "|* _ _|*|  _ _   _|   |* _|_ _ _|*|*|_|*| |* _|* _ _|*|",
        "|_ _ _ _|_ _ _|_ _ _|_ _ _ _ _ _ _|_ _ _|_ _ _ _|_ _ *|"
    };

    vector<vector<Node>> g; // output grid
    int R = 0, C = 0;       // dimensions (rows, columns)

    // Build the graph from ASCII; exit on parse error.
    if (!import_ascii_min(ascii, g, R, C)) return 1;

    // Reprint the maze without stars so the user sees a clean layout.
    print_clean_ascii_min(g, R, C);

    return 0;
}
