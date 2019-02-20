#include <iostream>
#include <vector>

using std::vector;

/*primary colors*/
constexpr char R_P_COLOR = 'R';
constexpr char G_P_COLOR = 'G';
constexpr char B_P_COLOR = 'B';

void swap(char *a, char *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

/*this answer is based on dutch flag problem*/
void RGBSort(vector<char>&colors) {
    unsigned int G = 0, R = G, B = colors.size() - 1;
    while (G <= B) {
        switch (colors[G]) {
            case R_P_COLOR: {
                swap(&colors[R], &colors[G]);
                ++R;
                ++G;
            }
                break;
            case G_P_COLOR: {
                ++G;
            }
                break;
            case B_P_COLOR: {
                swap(&colors[G], &colors[B]);
                --B;
            }
        }
    }
}

void printColorVector(vector<char>&colors){
    for(auto color : colors){
        std::cout << color << std::endl;
    }
}

int main() {
    vector<char> colors {'G', 'B', 'R', 'R', 'B', 'R', 'G'};
    RGBSort(colors);
    printColorVector(colors);
    return 0;

}
