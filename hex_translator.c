#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hex_to_int(const char *buffer) {
  if ((buffer[0] < '0' || buffer[0] > 'F') ||
      (buffer[0] > '9' && buffer[0] < 'A')) {
    fprintf(stderr, "Error: Invalid hexadecimal character encountered.\n");
    return -1;
  }
  if ((buffer[1] < '0' || buffer[1] > 'F') ||
      (buffer[1] > '9' && buffer[1] < 'A')) {
    fprintf(stderr, "Error: Invalid hexadecimal character encountered.\n");
    return -1;
  }

  int r = 0;
  int num1 = (int)buffer[0];
  int num2 = (int)buffer[1];

  if (num1 <= (int)'F' && num1 >= 'A') {
    r += (num1 - (int)'A' + 10) * 16;
  } else {
    r += (num1 - (int)'0') * 16;
  }

  if (num2 <= (int)'F' && num2 >= 'A') {
    r += (num2 - (int)'A' + 10);
  } else {
    r += (num2 - (int)'0');
  }

  return r;
}

const char *type_names[7] = {"int16_t", "Float",   "uint32_t", "int32_t",
                             "int8_t",  "uint8_t", "uint16_t"};
const int type_sizes[7] = {2, 4, 4, 4, 1, 1, 2};

int index_of(const char *val) {
  for (int i = 0; i < 7; i++) {
    if (strcmp(type_names[i], val) == 0) {
      return i;
    }
  }
  return -1;
}

int main(int argc, char *argv[]) {
  int num_bytes = atoi(argv[1]) - 1;

  char buffer[num_bytes * 3 + 2];
  memset(buffer, 0, sizeof(buffer));
  fgets(buffer, sizeof(buffer), stdin);

  size_t s = strlen(buffer);
  uint8_t data[num_bytes];
  memset(data, 0, sizeof(data));
  int c = 0;
  for (size_t i = 0; i + 1 < s && c < num_bytes; i += 3) {
    if (buffer[i] == '\n' || buffer[i] == '\0')
      break;
    data[c] = (uint8_t)hex_to_int(buffer + i);
    c++;
  }
  size_t offset = sizeof(data) - 4;
  if (argc <= 3 && strcmp(argv[2], "Float") == 0) {
    float f;
    memcpy(&f, &data[offset], sizeof(float));
    printf("[float: %f]\n", f);
    return 0;
  } else if (argc <= 3 && strcmp(argv[2], "int32_t") == 0) {
    int32_t f;
    memcpy(&f, &data[offset], sizeof(int32_t));
    printf("[int32_t: %d]\n", f);
    return 0;
  } else if (argc <= 3) {
    uint32_t f;
    memcpy(&f, &data[offset], sizeof(uint32_t));
    printf("[uint32_t: %d]\n", f);
    return 0;
  }

  int bytes_used = 0;
  for (int i = 2; i < argc; i++) {
    int ind = index_of(argv[i]);
    if (ind == -1) {
      fprintf(stderr, "Error: Invalid or unknown data type '%s'\n", argv[i]);
      continue;
    }
    int16_t i16;
    uint16_t u16;
    float f;
    uint32_t u32;
    int32_t i32;
    int8_t i8;
    uint8_t ui8;
    switch (ind) {
    case 0: // int16_t
      memcpy(&i16, data + bytes_used, sizeof(int16_t));
      printf("[int16: %d] ", (int)i16);
      bytes_used += sizeof(int16_t);
      break;
    case 1: // Float
      memcpy(&f, data + bytes_used, sizeof(float));
      printf("[float: %.2f] ", f);
      bytes_used += sizeof(float);
      break;
    case 2: // uint32_t
      memcpy(&u32, data + bytes_used, sizeof(uint32_t));
      printf("[uint32: %u] ", u32);
      bytes_used += sizeof(uint32_t);
      break;
    case 3: // int32_t
      memcpy(&i32, data + bytes_used, sizeof(int32_t));
      printf("[int32: %d] ", (int)i32);
      bytes_used += sizeof(int32_t);
      break;
    case 4: // int8_t
      memcpy(&i8, data + bytes_used, sizeof(int8_t));
      printf("[int8: %d] ", (int)i8);
      bytes_used += sizeof(int8_t);
      break;
    case 5: // uint8_t
      memcpy(&ui8, data + bytes_used, sizeof(uint8_t));
      printf("[uint8: %u] ", (unsigned int)ui8);
      bytes_used += sizeof(uint8_t);
      break;
    case 6: // uint16_t
      memcpy(&u16, data + bytes_used, sizeof(uint16_t));
      printf("[uint16: %u] ", (unsigned int)u16);
      bytes_used += sizeof(uint16_t);
      break;
    }
  }
  printf("\n");

  return 0;
}
