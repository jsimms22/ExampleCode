// example following along with: https://www.youtube.com/watch?v=ZNttI_WswMU

// Followed this guide to install lua for use with mingw64 toolchain: https://gist.github.com/Shoozza/ef71ff78b9b04b77b8fc06076f53e3fe
// Note: I had to downgrade to luarocks 3.9.2 to install luasocket + luaposix: https://github.com/lunarmodules/luasocket/issues/429#issuecomment-2140885957

#include <iostream>
#include <coroutine>
#include "../simple_logger.hpp"

