#pragma once

#include <cassert>
#include <limits>
#include <cstdint>
#include <cmath>

int GetCStringLength(const char* pStr);

bool FindSubStringNaively(const char* pStr, const char* pSub);
bool FindSubStringAutomata(const char* pStr, const char* pSub);
bool FindSubStringRabinKarp(const char* pStr, const char* pSub);
bool FindSubStringKMP(const char* pStr, const char* pSub);
bool FindSubStringBoyerMoore(const char* pStr, const char* pSub);