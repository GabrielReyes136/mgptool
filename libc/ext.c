
uint * __memset(uint *dst,uint token,uint len)

{
  uint *_seek;
  uint diff;
  uint inf;
  
  _seek = dst;
  diff = len;
  if (0xf < len) {
    diff = (uint)dst & 3;
    if (diff != 0) {
      for (; diff < 4; diff = diff + 1) {
        *(char *)_seek = (char)token;
        len = len - 1;
        _seek = (uint *)((int)_seek + 1);
      }
    }
    token = token & 0xff;
    inf = token;
    if (token != 0) {
      inf = token | token << 8;
      inf = inf | inf << 0x10;
    }
    diff = len & 7;
    for (len = len >> 3; len != 0; len = len - 1) {
      *_seek = inf;
      _seek[1] = inf;
      _seek = _seek + 2;
    }
    if (3 < diff) {
      *_seek = inf;
      diff = diff - 4;
      _seek = _seek + 1;
    }
  }
  for (; diff != 0; diff = diff - 1) {
    *(char *)_seek = (char)token;
    _seek = (uint *)((int)_seek + 1);
  }
  return dst;
}
