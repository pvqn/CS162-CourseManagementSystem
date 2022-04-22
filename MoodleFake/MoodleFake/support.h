#pragma once
#include "struct.h"

void remove_dir(char* path);
void reset_cache();
bool is_dir(const char* path);
void copyFile_(string inDir, string outDir);
void copyDir_(const char* inputDir, string outDir);
void Pull();
void Push();