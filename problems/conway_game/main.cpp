#include <iostream>
#include <map>
#include <list>


/*Conway's Game*/

using std::pair, std::list;

class Point {

public:
    Point() : x{0}, y{0} {}

    Point(long int xVal, long int yVal) : x{xVal}, y{yVal} {}

    long int X() const {
        return this->x;
    }

    long int Y() const {
        return this->y;
    }

    bool operator<(const Point &p) const {
        if (this->x < p.X()) {
            return true;
        }

        if (this->x > p.x) {
            return false;
        }

        return (this->y < p.Y());

    }

    bool operator<=(const Point &p) const {

        return operator<(p) || ((p.X() == x) && (p.Y() == y));

    }

private:
    long int x, y;
};


/*the solution  for this problem is much easier using a sparse matrix,
 * but i couldn't find an implementation in stdlib, therefore i used a map to mimic the behavior
 * of a sparse matrix instead*/
class Board {
public:
    Board(char aliveChar, char deadChar) : defaultAliveChar{aliveChar}, defaultDeadChar{deadChar} {}


    void insert(Point coordinate) {
        if (board.find(coordinate) == board.end()) {
            board[coordinate] = defaultAliveChar;
        } else {
            throw "element already exist on the board";
        }
    }

    void remove(Point coordinate) {
        if (board.find(coordinate) == board.end()) {
            throw "this element isn't in the board";
        }

        board.erase(coordinate);
    }

    void processTick() {
        /*in order to verify if the neighbors of this point can be activated, we need to take a look at the
             * neighbors of the neighbors of this point*/
        topLeftCorner = Point(INT32_MAX, INT32_MAX);
        bottomRightCorner = Point();
        if (board.size() == 0)
            return;

        for (std::map<Point, char>::iterator iter = board.begin(); iter != board.end(); ++iter) {
            Point currentPoint = iter->first;
            list<Point> deadNeighBoors;

            unsigned short int livingNeighbors = 0;
            for (short int lineIncrement = -1; lineIncrement < 2; ++lineIncrement) {
                for (short int columnIncrement = -1; columnIncrement < 2; ++columnIncrement) {
                    if (lineIncrement == 0 && columnIncrement == 0) {
                        continue;
                    }
                    Point neighbor;
                    neighbor = Point(currentPoint.X() + columnIncrement, currentPoint.Y() + lineIncrement);
                    if (board.find(neighbor) != board.end()) {
                        ++livingNeighbors;
                    } else {
                        deadNeighBoors.emplace_back(neighbor);
                    }
                }
            }

            if (livingNeighbors < 2 || livingNeighbors > 3) {
                pointsToBeDelete.emplace_back(currentPoint);
            } else {
                updateCorners(currentPoint);
            }


            for (Point deadP: deadNeighBoors) {
                livingNeighbors = 0;
                for (short int lineIncrement = -1; lineIncrement < 2; ++lineIncrement) {
                    for (short int columnIncrement = -1; columnIncrement < 2; ++columnIncrement) {
                        if (lineIncrement == 0 && columnIncrement == 0) {
                            continue;
                        }
                        Point neighbor;
                        neighbor = Point(deadP.X() + columnIncrement, deadP.Y() + lineIncrement);
                        if (board.find(neighbor) != board.end()) {
                            ++livingNeighbors;
                        }


                    }
                }

                if (livingNeighbors == 3) {
                    pointsToBeInserted.emplace_back(deadP);
                    updateCorners(deadP);
                }


            }
        }

        insertCachedPoints();
        deleteCachedPoints();
        printTick();

    }

private:
    list<Point> pointsToBeDelete;
    list<Point> pointsToBeInserted;
    Point topLeftCorner, bottomRightCorner;
    std::map<Point, char> board;
    const char defaultAliveChar, defaultDeadChar;

    void updateCorners(Point p) {
        if (p.X() > bottomRightCorner.X()) {
            bottomRightCorner = Point(p.X(), bottomRightCorner.Y());
        }

        if (p.Y() > bottomRightCorner.Y()) {
            bottomRightCorner = Point(bottomRightCorner.X(), p.Y());
        }

        if (p.X() < topLeftCorner.X()) {
            topLeftCorner = Point(p.X(), topLeftCorner.Y());
        }

        if (p.Y() < topLeftCorner.Y()) {
            topLeftCorner = Point(topLeftCorner.X(), p.Y());
        }
    }

    void printTick() {
        for (long int y = topLeftCorner.Y(); y <= bottomRightCorner.Y(); ++y) {
            for (long int x = topLeftCorner.X(); x <= bottomRightCorner.X(); ++x) {
                if (board.find(Point(x, y)) != board.end()) {
                    std::cout << defaultAliveChar;
                } else {
                    std::cout << defaultDeadChar;
                }
            }

            std::cout << "\n" << std::flush;
        }
    }

    void deleteCachedPoints() {
        for (Point &p: pointsToBeDelete) {
            remove(p);
        }
        pointsToBeDelete.clear();
    }

    void insertCachedPoints() {
        for (Point &p: pointsToBeInserted) {
            insert(p);
        }
        pointsToBeInserted.clear();
    }
};

int main() {
    constexpr unsigned int ticks = 10;
    const list<Point> cellsAlive = {{0, 0},
                                    {1, 0},
                                    {1, 1},
                                    {0, 1}};
    Board board{'*', '.'};
    for (Point p: cellsAlive) {
        board.insert(p);
    }
    for (unsigned int i = 0; i < ticks; ++i) {
        board.processTick();
        std::cout << "---------------------------------------------" << std::endl;
    }
    return 0;
}
