#include "simulation.hpp"
#include <vector>
#include <utility>

void Simulation::Draw()
{
    grid.Draw();
}
void Simulation::SetCellValue(int row, int column, int value)
{
    grid.SetValue(row, column, value);
}
int Simulation::CountLiveNeighbors(int row, int column)
{
    int liveNeighbors = 0;
    std::vector<std::pair<int, int>> neigborOffsets = 
        {
            {-1,0},     // Directly above
            {1,0},      // Directly below
            {0,-1},     // To the left
            {0,1},      // To the right
            {-1,-1},    // Diag upper left
            {-1,1},     // Diag upper right 
            {1, -1},    // Diag lower left
            {-1, 1},    // Diag lower right
        };

    for (const auto& offset : neigborOffsets)
    {
        int neigborRow = ( row + offset.first + grid.GetRows() ) % grid.GetRows();
        int neigborColumn = ( column + offset.second + grid.GetColumns() ) % grid.GetColumns();
        liveNeighbors += grid.GetValue(neigborRow, neigborColumn);
    }
    return liveNeighbors;
}
void Simulation::Update()
{
    for(int row = 0; row < grid.GetRows(); row++)
    {
        for(int column = 0; column < grid.GetColumns(); column++)
        {
            int liveNeighbors = CountLiveNeighbors(row, column);
            int cellValue = grid.GetValue(row, column);

            if (cellValue == 1)
            {
                if(liveNeighbors > 3 || liveNeighbors < 2)
                {
                    tempGrid.SetValue(row, column, 0);
                }
                else 
                {
                    tempGrid.SetValue(row, column, 1);
                }
            }
            else 
            {
                if (liveNeighbors == 3)
                {
                    tempGrid.SetValue(row, column, 1);
                }
                else 
                {
                    tempGrid.SetValue(row, column, 0);
                }
            }
        }
    }
    grid = tempGrid;
}
