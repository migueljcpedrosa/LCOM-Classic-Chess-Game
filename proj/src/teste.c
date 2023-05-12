int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  uint32_t color1 = color;

  //uint32_t border_size = (modeInfo.XResolution - (8 * 100))  / 2;

  //ainda nao testei isto do border_size, por isso comentei e substitui por x e y
  for (int w = 0; w < 8; w++) {
    for (int h = 0; h < 8; h++) {
      // draw square
      if((w+h) % 2 == 0)
        color1 = 0xeeeed2;
      else
        color1 = 0x769656;
      for (int i = 0; i < 100; i++) {
        vg_draw_hline(x /*border_size*/ + (w * 100), (y /*border_size*/ + i) + (h * 100), 100, color1);
      }
    };
  }

  return 0;
}
