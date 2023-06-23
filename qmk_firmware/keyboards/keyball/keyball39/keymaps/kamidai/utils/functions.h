// 自前の絶対数を返す関数。 Functions that return absolute numbers.
int16_t my_abs(int16_t num) {
  if (num < 0) {
    num = -num;
  }
  return num;
}

// 自前の符号を返す関数。 Function to return the sign.
// int16_t mmouse_move_y_sign(int16_t num) {
//   if (num < 0) {
//     return -1;
//   }
//   return 1;
// }