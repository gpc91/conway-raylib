// https://code.visualstudio.com/docs/cpp/customize-default-settings-cpp
#include "raylib.h"

int main(void)
{          
    const int scrW = 640;
    const int scrH = 360;
    
    char grid[scrW][scrH];
    char gridBuffer[scrW][scrH];
    
    // randomize (soup) the grid.
    for (int _y = 0; _y < scrH; _y++)
    {
        for (int _x = 0; _x < scrW; _x++)
        {
            grid[_x][_y] = GetRandomValue(0, 1);            
            gridBuffer[_x][_y] = grid[_x][_y];
        }
    }
    
    InitWindow(scrW, scrH, "Conway's Game of Life - code by George Corkery");    
        
    SetTargetFPS(60);
    
    float time_elapsed = 0;
    float time_interval = 0.1f;
    bool trigger_draw = false;
    
    int sum = 0;        
    while (!WindowShouldClose())
    {       
        
        // ======== ======== ======== UPDATE BEGIN ======== ======== ======== 
        if (time_elapsed >= time_interval)
        {
            time_elapsed = 0;
            trigger_draw = true;
                
            for (int _y = 0; _y < scrH; _y++)
            {
                for (int _x = 0; _x < scrW; _x++)
                {
                    sum = 0;
                                    
                    if (_x >= 1)
                    {
                        sum += grid[_x-1][_y];
                        if (_y >= 1)
                        {
                            sum += grid[_x-1][_y-1];                        
                            if (_y < scrH-1)
                            {
                                sum += grid[_x-1][_y+1];
                            }
                        }
                    }
                    
                    if (_x < scrW-1)
                    {
                        sum += grid[_x+1][_y];
                        if (_y >= 1)
                        {
                            sum += grid[_x+1][_y-1];
                            if (_y < scrH-1)
                            {
                                sum += grid[_x+1][_y+1];
                            }
                        }
                    }
                    
                    if (_y >= 1)
                    {
                        sum += grid[_x][_y-1];
                        if (_y < scrH-1)
                        {
                            sum += grid[_x][_y+1];
                        }
                    }
                    
                    if (sum < 2)
                    {
                        gridBuffer[_x][_y] = 0;
                    }
                    
                    if (sum > 3)
                    {
                        gridBuffer[_x][_y] = 0;
                    }
                    
                    if (sum == 3)
                    {
                        gridBuffer[_x][_y] = 1;
                    }                
                    
                }
            }       
        }
        else
        {
                time_elapsed += GetFrameTime();
        }
        
        // ======== ======== ======== INPUT CATCH ======== ======== ========         
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            grid[GetMouseX()][GetMouseY()] = 1;
            gridBuffer[GetMouseX()][GetMouseY()] = 1;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            grid[GetMouseX()][GetMouseY()] = 0;
            gridBuffer[GetMouseX()][GetMouseY()] = 0;
        }
       
        if (GetMouseWheelMove() > 0)
        {
            time_interval += 0.1f;
        } 
        else if (GetMouseWheelMove() < 0)
        {
            time_interval -= 0.1f;
        }

        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            if (IsKeyPressed(KEY_S))
            {
                // generate soup
                for (int _y = 0; _y < scrH; _y++)
                {
                    for (int _x = 0; _x < scrW; _x++)
                    {
                        grid[_x][_y] = GetRandomValue(0, 1);
                        gridBuffer[_x][_y] = grid[_x][_y];
                    }
                }
            }
        }
        
        
        // ======== ======== ======== UPDATE END ======== ======== ========         
        
        // ======== ======== ======== DRAW BEGIN ======== ======== ======== 
        BeginDrawing();
            ClearBackground(BLACK);  

            DrawText(TextFormat("%i", trigger_draw), 4, 124, 24, WHITE);
            for (int _y = 0; _y < scrH; _y++)
            {
                for (int _x = 0; _x < scrW; _x++)
                {
                    grid[_x][_y] = gridBuffer[_x][_y];
                    if (grid[_x][_y])
                    {
                        DrawPixel(_x, _y, WHITE); 
                    }
                    else
                    {
                        DrawPixel(_x, _y, BLACK); 
                    }                       
                }
            }
            DrawFPS(4, 4);
            
            //DrawText(TextFormat("%f", time_elapsed), 100, 100, 48, WHITE);
            DrawText(TextFormat("%i, %i", GetMouseX(), GetMouseY()), 4, 24, 24, WHITE);
            DrawText(TextFormat("time_interval: %f", time_interval), 4, 48, 24, WHITE);
            DrawText(TextFormat("%f", GetMouseWheelMove()), 4, 100, 24, WHITE);
            
            
        EndDrawing();
        // ======== ======== ======== DRAW END ======== ======== ======== 
    }  
    
    CloseWindow();
    
    return 0;
}
