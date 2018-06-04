//
// EdbCrypt C++ implementation
//
// CC0 - PUBLIC DOMAIN
// This work is free of known copyright restrictions.
// http://creativecommons.org/publicdomain/zero/1.0/
//

#pragma once

#ifndef __EdbCrypt__
#define __EdbCrypt__

#include <stdint.h>
#include <cstddef>
#include <vector>
#include <QByteArray>

class EdbCrypt {

public:
  EdbCrypt(const QByteArray& key);
  QByteArray Encrypt(const QByteArray& src) const;
  QByteArray Decrypt(const QByteArray& src) const;

private:
  std::vector<char> Encrypt(const std::vector<char> &src) const;
  std::vector<char> Decrypt(const std::vector<char> &src) const;
  void SetKey(const char *key, size_t byte_length);
  void EncryptBlock(uint32_t *left, uint32_t *right) const;
  void DecryptBlock(uint32_t *left, uint32_t *right) const;
  uint32_t Feistel(uint32_t value) const;

private:
  uint32_t pary_[18];
  uint32_t sbox_[4][256];
};

#endif /* defined(__EdbCrypt__) */
