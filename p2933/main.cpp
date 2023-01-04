#include <iostream>
#include <queue>

using namespace std;

constexpr int MAX_CAVE_SIZE = 105;
constexpr int MAX_THROW_NUM = 105;
constexpr char EMPTY = '.';
constexpr char MINERAL = 'x';

int r, c;
char cave[MAX_CAVE_SIZE][MAX_CAVE_SIZE];

int n;
int heights[MAX_THROW_NUM];

bool grounded[MAX_CAVE_SIZE][MAX_CAVE_SIZE];
bool visited[MAX_CAVE_SIZE][MAX_CAVE_SIZE];

class Point
{
public:
    Point() : row(-1), column(-1) {}
    Point(int row, int column) : row(row), column(column) {}

public:
    int row, column;
};

bool isMineral(char c)
{
    return c == MINERAL;
}

void input()
{
    cin >> r >> c;

    for (int i = 0; i < r; i++)
    {
        cin >> cave[i];
    }

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> heights[i];
    }
}

bool isInCave(int row, int column)
{
    return row >= 0 && row < r && column >= 0 && column < c;
}

void clearGrounded()
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            grounded[i][j] = false;
        }
    }
}

void setGroundedBfs(int row, int column)
{
    int rowDelta[4] = {-1, 1, 0, 0};
    int columnDelta[4] = {0, 0, -1, 1};

    queue<Point> q;
    q.push(Point(row, column));
    grounded[row][column] = true;

    while (!q.empty())
    {
        Point p = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nextRow = p.row + rowDelta[i];
            int nextColumn = p.column + columnDelta[i];
            if (isInCave(nextRow, nextColumn) && isMineral(cave[nextRow][nextColumn]) && !grounded[nextRow][nextColumn])
            {
                grounded[nextRow][nextColumn] = true;
                q.push(Point(nextRow, nextColumn));
            }
        }
    }
}

void clearVisited()
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            visited[i][j] = false;
        }
    }
}

vector<Point> getClusterPoints(int row, int column)
{
    clearVisited();

    vector<Point> cluster;

    int rowDelta[4] = {-1, 1, 0, 0};
    int columnDelta[4] = {0, 0, -1, 1};

    queue<Point> q;
    Point start = Point(row, column);
    q.push(start);
    cluster.push_back(start);
    visited[row][column] = true;


    while (!q.empty())
    {
        Point p = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nextRow = p.row + rowDelta[i];
            int nextColumn = p.column + columnDelta[i];
            if (isInCave(nextRow, nextColumn) && isMineral(cave[nextRow][nextColumn]) && !visited[nextRow][nextColumn])
            {
                visited[nextRow][nextColumn] = true;
                Point nextPoint = Point(nextRow, nextColumn);
                q.push(nextPoint);
                cluster.push_back(nextPoint);
            }
        }
    }

    return cluster;
}

vector<Point> findLowestPointsInCluster(vector<Point> cluster)
{
    int lowestHeightInColumn[MAX_CAVE_SIZE];
    Point lowestPointInColumn[MAX_CAVE_SIZE];

    for(int i = 0; i < c; i++)
    {
        lowestHeightInColumn[i] = -1;
    }

    for (vector<Point>::iterator iter = cluster.begin(); iter != cluster.end(); iter++)
    {
        int row = (*iter).row;
        int column = (*iter).column;
        if (row <= lowestHeightInColumn[column])
            continue;

        if (row > lowestHeightInColumn[column])
        {
            lowestPointInColumn[column] = *iter;
            lowestHeightInColumn[column] = row;
        }
    }

    vector<Point> lowestPoints;
    for(int i = 0; i < c; i++)
    {
        lowestPoints.push_back(lowestPointInColumn[i]);
    }

    return lowestPoints;
}

int calculateFallingDistance(Point point)
{
    for (int i = point.row; isInCave(i, point.column); i++)
    {
        if (grounded[i][point.column])
        {
            return i - point.row - 1;
        }
    }
    return r - point.row - 1;
}

int calculateFallingDistance(vector<Point> points)
{
    int minimumFallingDistance;

    for (vector<Point>::iterator iter = points.begin(); iter != points.end(); iter++)
    {
        int fallingDistance = calculateFallingDistance(*iter);
        if (minimumFallingDistance > fallingDistance)
            minimumFallingDistance = fallingDistance;
    }

    return minimumFallingDistance;
}

void remove(vector<Point> cluster)
{
    for (vector<Point>::iterator iter = cluster.begin(); iter != cluster.end(); iter++)
    {
        cave[(*iter).row][(*iter).column] = EMPTY;
    }
}

void fall(vector<Point> cluster, int fallingDistance)
{
    remove(cluster);
    for (vector<Point>::iterator iter = cluster.begin(); iter != cluster.end(); iter++)
    {
        cave[(*iter).row + fallingDistance][(*iter).column] = MINERAL;
    }
}

bool isFloated(int row, int column)
{
    return isMineral(cave[row][column]) && !grounded[row][column];
}

bool fallConnectedCluster(int row, int column)
{
    vector<Point> cluster = getClusterPoints(row, column);
    vector<Point> lowestPoints = findLowestPointsInCluster(cluster);
    int fallingDistance = calculateFallingDistance(lowestPoints);
    fall(cluster, fallingDistance);

    return true;
}

void clearAndSetGroundedBfs()
{
    clearGrounded();
    for (int i = 0; i < c; i++)
    {
        int ground = r - 1;
        if (isMineral(cave[ground][i]) && !grounded[ground][i])
        {
            setGroundedBfs(ground, i);
        }
    }
}

void destroy(int row, int column)
{
    cave[row][column] = EMPTY;

    clearAndSetGroundedBfs();
    int rowDelta[4] = {-1, 1, 0, 0};
    int columnDelta[4] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++)
    {
        int nextRow = row + rowDelta[i];
        int nextColumn = column + columnDelta[i];
        if (isInCave(nextRow, nextColumn) && isFloated(nextRow, nextColumn))
        {
            fallConnectedCluster(nextRow, nextColumn);
            break;
        }
    }
}

int castRayFromLeft(int height)
{
    int y = r - height;
    for (int i = 0; i < c; i++)
    {
        if (isMineral(cave[y][i]))
            return i;
    }
    return -1;
}

int castRayFromRight(int height)
{
    int y = r - height;
    for (int i = c - 1; i >= 0; i--)
    {
        if (isMineral(cave[y][i]))
            return i;
    }
    return -1;
}

void process()
{
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            int column = castRayFromLeft(heights[i]);
            if (column == -1)
                continue;
            destroy(r - heights[i], column);
        }
        else
        {
            int column = castRayFromRight(heights[i]);
            if (column == -1)
                continue;
            destroy(r - heights[i], column);
        }
    }
}

void output()
{
    for (int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            printf("%c", cave[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    input();
    process();
    output();

    cin >> n;

    return 0;
}