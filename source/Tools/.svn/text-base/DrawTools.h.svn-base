#pragma once

void Draw_shape(int x, int y, uint16* buffer, uint16 color)
{
  buffer += y * SCREEN_WIDTH + x;
  for(int i = 0; i < shape_height; ++i) {
    uint16* line = buffer + (SCREEN_WIDTH * i);
    for(int j = 0; j < shape_width; ++j) {
      *line++ = color;
    }
  }
}