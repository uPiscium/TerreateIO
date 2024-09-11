#include "../../includes/formats/buffer.hpp"

#include <iostream>

namespace TerreateIO::Core {
using namespace TerreateIO::Defines;

Str const BASE64::sTable =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

ReadBuffer::~ReadBuffer() {
  if (mBuffer != nullptr) {
    delete[] mBuffer;
  }
}

void ReadBuffer::SetCursor(Size const &offset) {
  if (mBuffer + offset > mBuffer + mSize) {
    throw Exception::BufferException("Buffer out of bounds");
  } else {
    mCursor = mBuffer + offset;
  }
}

Str ReadBuffer::Fetch(Size const &size) {
  Str result;
  if (mCursor + size > mBuffer + mSize) {
    Str temp;
    temp += EOB;
    return temp;
  } else {
    result = Str(mCursor, mCursor + size);
  }
  return result;
}

Str ReadBuffer::Read(Size const &size) {
  Str result;
  if (mCursor + size > mBuffer + mSize) {
    Str temp;
    temp += EOB;
    return temp;
  } else {
    result = Str(mCursor, mCursor + size);
    mCursor += size;
  }
  return result;
}

void ReadBuffer::Skip(Size const &size) {
  if (mCursor + size > mBuffer + mSize) {
    throw Exception::BufferException("Buffer out of bounds");
  } else {
    mCursor += size;
  }
}

void ReadBuffer::SkipWhitespace() {
  while (mCursor < mBuffer + mSize &&
         (*mCursor == ' ' || *mCursor == '\t' || *mCursor == '\n' ||
          *mCursor == '\r' || *mCursor == '\f' || *mCursor == '\v')) {
    ++mCursor;
  }
}

ReadBuffer &ReadBuffer::operator=(ReadBuffer const &buffer) {
  if (this != &buffer) {
    if (mBuffer != nullptr) {
      delete[] mBuffer;
    }
    mBuffer = new Byte[buffer.mSize];
    mCursor = mBuffer;
    mSize = buffer.mSize;
    std::memcpy(mBuffer, buffer.mBuffer, buffer.mSize);
  }
  return *this;
}

WriteBuffer &WriteBuffer::operator=(WriteBuffer const &buffer) {
  if (this != &buffer) {
    mStream.str(buffer.mStream.str());
  }
  return *this;
}

Str BASE64::Encode(Byte const *data, Size const &size) {
  Int container = 0;
  Str result = "";

  for (Size i = 0; i < size / 3; ++i) {
    for (Byte j = 0; j < 3; ++j) {
      container += data[i * 3 + j];
      container <<= 8;
    }

    std::cout << std::hex << container << std::endl;

    for (Byte j = 0; j < 4; ++j) {
      result += sTable[(container >> 26) & 0x3F];
      /* std::cout << std::hex << ((container >> 26) & 0x3F) << std::endl; */
      container <<= 6;
    }
  }

  switch (size % 3) {
  case 1:
    result += sTable[data[size - 1] >> 2];
    result += sTable[(data[size - 1] & 0x03) << 4];
    result += "==";
    break;
  case 2:
    result += sTable[data[size - 2] >> 2];
    result += sTable[((data[size - 2] & 0x03) << 4) + (data[size - 1] >> 4)];
    result += sTable[(data[size - 1] & 0x0F) << 2];
    result += "=";
    break;
  default:
    break;
  };

  return result;
}

Str BASE64::Decode(Byte const *data, Size const &size) {
  Int container = 0;
  Str result = "";
  if (size % 4 != 0) {
    throw Exception::BufferException("Invalid BASE64 string");
  }

  for (Size i = 0; i < size; i += 4) {
    if (data[i] == '=' || data[i + 1] == '=') {
      break;
    }

    if (data[i + 2] == '=') {
      Size idx1 = sTable.find(data[i]);
      Size idx2 = sTable.find(data[i + 1]);
      if (idx1 == Str::npos || idx2 == Str::npos) {
        break;
      }

      result += static_cast<Byte>(((idx1 & 0x3F) << 2) | ((idx2 & 0x30) >> 4));
    } else if (data[i + 3] == '=') {
      Size idx1 = sTable.find(data[i]);
      Size idx2 = sTable.find(data[i + 1]);
      Size idx3 = sTable.find(data[i + 2]);
      if (idx1 == Str::npos || idx2 == Str::npos || idx3 == Str::npos) {
        break;
      }

      result += static_cast<char>(((idx1 & 0x3F) << 2) | ((idx2 & 0x30) >> 4));
      result += static_cast<char>(((idx2 & 0x0F) << 4) | ((idx3 & 0x3C) >> 2));
    } else {
      Size idx1 = sTable.find(data[i]);
      Size idx2 = sTable.find(data[i + 1]);
      Size idx3 = sTable.find(data[i + 2]);
      Size idx4 = sTable.find(data[i + 3]);
      if (idx1 == Str::npos || idx2 == Str::npos || idx3 == Str::npos ||
          idx4 == Str::npos) {
        break;
      }

      result += static_cast<char>(((idx1 & 0x3F) << 2) | ((idx2 & 0x30) >> 4));
      result += static_cast<char>(((idx2 & 0x0F) << 4) | ((idx3 & 0x3C) >> 2));
      result += static_cast<char>(((idx3 & 0x03) << 6) | (idx4 & 0x3F));
    }
  }

  for (Size i = 0; i < size / 4; ++i) {
    for (Byte j = 0; j < 4; ++j) {
      if (data[i * 4 + j] != '=') {
        Size idx = sTable.find(data[i * 4 + j]);
        if (idx == Str::npos) {
          break;
        }

        container += (idx & 0x3F);
      }
      container <<= 6;
    }
    container <<= 2;
    std::cout << std::hex << container << std::endl;

    for (Byte j = 0; j < 3; ++j) {
      result += ((container & 0xFF0000) >> 16);
      std::cout << std::hex << ((container & 0xFF0000) >> 16) << std::endl;
      container <<= 8;
    }
  }

  return result;
}
} // namespace TerreateIO::Core
